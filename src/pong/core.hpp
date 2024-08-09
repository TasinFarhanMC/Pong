#pragma once

#include <def.hpp>
#include <glfw/glfw3.h>
#include <scene/scene.hpp>

namespace core {
constexpr NanoSecond TICK_RATE(Second(1) / 40);
constexpr const char *TITLE = "Pong";

extern IVec2 screen_size;
extern GLFWwindow *window;
extern GLFWmonitor *monitor;

void set_scene(scene::Object *s);
void close();
void null();
bool nop();
} // namespace core
