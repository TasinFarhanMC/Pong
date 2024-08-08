#pragma once
#include <scene/scene.hpp>

#include <glfw/glfw3.h>
#include <glm/ext/vector_int2.hpp>

#include <cstdint>

namespace core {
inline const float TICK_RATE = 1.0f / 40.0f;
inline const std::uint32_t TICK_RATE_NANO = 1000000000 / 40;

extern glm::ivec2 screen_size;
extern GLFWwindow *window;
extern GLFWmonitor *monitor;

void close();
void set_scene(scene::Type *s);
void null();
bool nop();
} // namespace core
