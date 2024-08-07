#include "callbacks.hpp"

namespace callback {
namespace key {
static bool read[GLFW_KEY_LAST + 1] = {false};
static bool states[GLFW_KEY_LAST + 1] = {false};

void fun(GLFWwindow *window, const int key, const int scancode,
         const int action, const int mods) {
  switch (action) {
  case GLFW_RELEASE:
    states[key] = false;
    break;
  default:
    states[key] = true;
    break;
  }

  read[key] = false;
}

bool get_state(const State state, const int key) {
  switch (state) {
  case State::Press:
    if (states[key] && !read[key]) {
      read[key] = true;
      return true;
    } else {
      return states[key] && !read[key];
    }
  case State::Release:
    if (!states[key] && !read[key]) {
      read[key] = true;
      return true;
    } else {
      return !states[key] && !read[key];
    }
  case State::Down:
    return states[key];
  case State::Up:
    return !states[key];
  }
}
} // namespace key
} // namespace callback
