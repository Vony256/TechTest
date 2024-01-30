#include <string>
#include <functional>

struct PrimitiveComponent {
    int width;
    int height;
};

struct PositionComponent {
    float x;
    float y;
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

struct TagComponent { //yet to be implemented
    std::vector<std::string> tags;
    //TagComponent tagcomp{ {"tag1", "tag2", "tag3"} };
};