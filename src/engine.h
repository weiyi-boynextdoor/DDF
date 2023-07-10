#pragma once

#include <memory>

namespace DDF {
struct Context;

class Engine {
public:
    Engine(Context& context);

    ~Engine();

    void init();

    void destroy();

    void update();

private:
    Context& context_;
};
} // namespace DDF