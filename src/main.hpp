#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace Main {
extern GLFWwindow *window;
extern const float tick_t;

void close();
} // namespace Main
