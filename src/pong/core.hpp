#pragma once
#define GLFW_INCLUDE_NONE

#include <scene/scene.hpp>

#include <glfw/glfw3.h>

#include <cstdint>

namespace core {
inline const float TICK_RATE = 1.0f / 30.0f;
inline const std::uint32_t TICK_RATE_NANO = TICK_RATE * 1000000000;

extern GLFWwindow *window;

void close();
void set_scene(scene::Type *s);
void null();
bool nop();
} // namespace core
