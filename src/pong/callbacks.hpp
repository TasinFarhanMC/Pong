#pragma once
#include <glfw/glfw3.h>

#include <cstdint>

namespace callback {
namespace key {
enum class State : std::uint8_t { Down, Up, Press, Release };

void fun(GLFWwindow *window, int key, int scancode, int action, int mods);
bool get_state(State state, int key);
} // namespace key

void vidmode(GLFWwindow *window, int w, int h);

} // namespace callback
