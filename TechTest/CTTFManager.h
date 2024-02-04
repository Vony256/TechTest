#pragma once

#include <string>
#include <map>
#include <SDL.h>
#include <SDL_ttf.h>
#include "CWindow.h"

class CTTFManager {
    private:
        static CTTFManager* instance;

        // Map to store character textures
        std::map<char, SDL_Texture*> charTextures;

        // Map to store fonts
        std::map<std::string, TTF_Font*> fonts;

        // Private constructor for Singleton
        CTTFManager();

        // Private method to render a character
        SDL_Texture* renderChar(char c, TTF_Font* font);

        // Delete copy constructor and assignment operator
        CTTFManager(const CTTFManager&) = delete;
        CTTFManager& operator=(const CTTFManager&) = delete;

    public:
        ~CTTFManager();

        // Public method to get the instance
        static CTTFManager* getInstance();
        static void DestroyInstance();

        // Method to get the texture for a character
        SDL_Texture* getCharTexture(char c, TTF_Font* font);

        // destroy character cache
        void destroyCharCache();

        // Method to get a font
        TTF_Font* getFont(const std::string& fontName);

        // Method to load a font
        bool loadFont(const std::string& fontName, const std::string& filePath, int fontSize);

        // renderText method
        void renderText(const std::string& text, int x, int y, float scale, const std::string& fontName);
};