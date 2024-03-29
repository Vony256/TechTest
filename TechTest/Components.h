#include <string>
#include <functional>
#include <vector>

struct SizeComponent {
    int width;
    int height;
};

struct PositionComponent {
    float x;
    float y;
};

struct VelocityComponent {
    float xSpeed;
    float ySpeed;
};

struct NameComponent {
    std::string name;
};

struct GravityComponent {
    float gravityScale;
};

struct LambdaComponent {
    std::function<void()> action;
};

struct TagComponent {
    std::vector<std::string> taglist;
};

struct TextComponent {
    std::string text;
};

struct SelectableComponent {
    bool selected;
};

struct UIComponent {
    enum class Type {
        Button,
        SomethingElse,
    };

    Type uiType;
    bool isEnabled;
    bool isVisible;
};