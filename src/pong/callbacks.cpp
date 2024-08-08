#include "callbacks.hpp"
#include <core.hpp>

#include <algorithm>

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

    switch (key) {
    case GLFW_KEY_F11:
      glfwSetWindowMonitor(
          window,
          (glfwGetWindowMonitor(window) == nullptr) ? core::monitor : nullptr,
          0, 0, core::screen_size.x, core::screen_size.y, GLFW_DONT_CARE);
      break;
    }

    break;
  }

  read[key] = false;
}

bool get_state(const State state, const int key) {
  switch (state) {
  case State::Down:
    return states[key];
  case State::Up:
    return !states[key];
  case State::Press:
    if (states[key] && !read[key]) {
      read[key] = true;
      return true;
    } else {
      return states[key] && !read[key];
    }
  case State::Release:
    if (!(states[key] && read[key])) {
      read[key] = true;
      return true;
    } else {
      return !(states[key] && read[key]);
    }
  }
}
} // namespace key

void vidmode(GLFWwindow *window, const int w, const int h) {
  int ratio_max_factor = std::min(w / 16, h / 9);
  int max_w = ratio_max_factor * 16;
  int max_h = ratio_max_factor * 9;

  glViewport((w - max_w) / 2, (h - max_h) / 2, max_w, max_h);
}
} // namespace callback
