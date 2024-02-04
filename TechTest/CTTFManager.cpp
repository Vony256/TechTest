#include "CTTFManager.h"

CTTFManager* CTTFManager::instance = nullptr;

CTTFManager::CTTFManager() {
}

CTTFManager::~CTTFManager() {
    destroyCharCache();

    for (const std::pair<const std::string, TTF_Font*>& fontPair : fonts) {
        TTF_CloseFont(fontPair.second);
    }
    fonts.clear();
}

void CTTFManager::destroyCharCache() {
    for (const std::pair<const char, SDL_Texture*>& texturePair : charTextures) {
        SDL_DestroyTexture(texturePair.second);
    }
    charTextures.clear();
}

CTTFManager* CTTFManager::getInstance() {
    if (instance == nullptr) {
        instance = new CTTFManager();
    }
    return instance;
}

void CTTFManager::DestroyInstance() {
    delete instance;
    instance = nullptr;
}


void CTTFManager::renderText(const std::string& text, int x, int y, float scale, const std::string& fontName) {
    TTF_Font* font = getFont(fontName);
    if (!font) {
        SDL_Log("Font not found: %s", fontName.c_str());
        return;
    }

    int currentPositionX = x;
    for (char character : text) {
        SDL_Texture* characterTexture = getCharTexture(character, font);
        if (characterTexture == nullptr) {
            continue; // Skip if texture is not available
        }

        int textureWidth = 0;
        int textureHeight = 0;
        SDL_QueryTexture(characterTexture, NULL, NULL, &textureWidth, &textureHeight);

        // Apply scaling to texture dimensions
        SDL_Rect sourceRect = { 0, 0, textureWidth, textureHeight };
        SDL_Rect destinationRect = { currentPositionX, y, static_cast<int>(textureWidth * scale), static_cast<int>(textureHeight * scale) };

        SDL_RenderCopy(CWindow::windowControl.GetRenderer(), characterTexture, &sourceRect, &destinationRect);

        // Update the x position for the next character, considering the scaled width
        currentPositionX += static_cast<int>(textureWidth * scale);
    }
}

bool CTTFManager::loadFont(const std::string& fontName, const std::string& filePath, int fontSize) {
    TTF_Font* font = TTF_OpenFont(filePath.c_str(), fontSize);
    if (font == nullptr) {
        SDL_Log("Failed to load font: %s", TTF_GetError());
        return false;
    }
    fonts[fontName] = font;
    return true;
}

TTF_Font* CTTFManager::getFont(const std::string& fontName) {
    std::map<std::string, TTF_Font*>::iterator it = fonts.find(fontName);
    if (it != fonts.end()) {
        return it->second;
    }
    return nullptr;
}

SDL_Texture* CTTFManager::renderChar(char character, TTF_Font* font) {
    // Convert the character to a string for rendering
    std::string charStr(1, character);

    // Set text color, you can modify this as needed
    SDL_Color textColor = { 255, 255, 255, 255 }; // White color

    // Create a surface from the font and character
    //SDL_Surface* surface = TTF_RenderText_Solid(font, charStr.c_str(), textColor); //without anti aliasing
    SDL_Surface* surface = TTF_RenderText_Blended(font, charStr.c_str(), textColor);
    if (surface == nullptr) {
        SDL_Log("Unable to create surface from font: %s", TTF_GetError());
        return nullptr;
    }

    // Create a texture from the surface
    SDL_Texture* texture = SDL_CreateTextureFromSurface(CWindow::windowControl.GetRenderer(), surface);
    if (texture == nullptr) {
        SDL_Log("Unable to create texture from surface: %s", SDL_GetError());
    }

    // Free the surface
    SDL_FreeSurface(surface);

    return texture;
}

SDL_Texture* CTTFManager::getCharTexture(char character, TTF_Font* font) {
    std::map<char, SDL_Texture*>::iterator it = charTextures.find(character);

    if (it != charTextures.end()) {
        // Character texture is cached
        return it->second;
    }
    else {
        // Character texture is not cached, render and store it
        SDL_Texture* texture = renderChar(character, font);
        charTextures[character] = texture;
        return texture;
    }
}