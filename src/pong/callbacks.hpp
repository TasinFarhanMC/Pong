#pragma once

#include <def.hpp>
#include <glfw/glfw3.h>

namespace callback {
namespace key {
enum class State : u8 { Down, Up, Press, Release };

void fun(GLFWwindow *window, int key, int scancode, int action, int mods);
bool get_state(State state, int key);
} // namespace key

void vidmode(GLFWwindow *window, int w, int h);

} // namespace callback
