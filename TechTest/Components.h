#include <string>

struct PrimitiveComponent {
    int width;
    int height;
};

struct TranslateComponent {
    float x;
    float y;
};

struct NameComponent {
    std::string name;
};

struct GravityComponent {
    float gravityScale;
};