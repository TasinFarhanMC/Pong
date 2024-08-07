#pragma once
#define GLFW_INCLUDE_NONE

#include <glfw/glfw3.h>

#include <cstdint>

namespace callback {
namespace key {
enum class State : std::uint8_t { Press, Release, Down, Up };

void fun(GLFWwindow* window, int key, int scancode, int action, int mods);
bool get_state(State state, int key);
}
} // namespace callback
