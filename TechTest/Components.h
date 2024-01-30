#include <string>

struct PrimitiveComponent {
    int width;
    int height;
};

struct TranslateComponent {
    int x;
    int y;
};

struct NameComponent {
    std::string name;
};