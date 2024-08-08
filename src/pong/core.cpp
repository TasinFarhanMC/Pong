#define GLFW_INCLUDE_NONE

#include "core.hpp"
#include <callbacks.hpp>
#include <scene/scene.hpp>

#include <glad/glad.h>

#include <chrono>
#include <iostream>
#include <thread>

namespace core {
namespace tm = std::chrono;

static bool running = true;
static float delta_t = 0.0f;

static const scene::Type *cur_scene = &scene::PLAYGROUND;
glm::ivec2 screen_size;
GLFWwindow *window = nullptr;
GLFWmonitor *monitor = nullptr;

static bool init() {
  if (!glfwInit()) {
    std::cerr << "Unable to init glfw" << std::endl;
    return false;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  monitor = glfwGetPrimaryMonitor();

  auto vid_mode = glfwGetVideoMode(monitor);
  screen_size.x = vid_mode->width;
  screen_size.y = vid_mode->height;

  window = glfwCreateWindow(screen_size.x * 2 / 3, screen_size.y * 2 / 3,
                            "Pong", nullptr, nullptr);
  if (!window) {
    std::cerr << "Unable to create window" << std::endl;

    glfwTerminate();
    return false;
  }

  glfwMakeContextCurrent(window);
  if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
    std::cerr << "Unable to init glad" << std::endl;

  EXIT_GLFW:
    glfwDestroyWindow(window);
    glfwTerminate();
    return false;
  }

  glfwSetWindowPos(window, screen_size.x / 6, screen_size.y / 6);

  glfwSetWindowCloseCallback(window,
                             reinterpret_cast<GLFWwindowclosefun>(close));
  glfwSetKeyCallback(window, callback::key::fun);
  glfwSetFramebufferSizeCallback(window, callback::vidmode);

  for (const auto s : scene::REFS) {
    if (!s->init()) {
      goto EXIT_GLFW;
    }
  }

  return true;
}

static void render() {
  auto start_t = tm::steady_clock::now();
  auto end_t = start_t;
  long acc_t = 0;

  while (running) {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    cur_scene->render();
    glfwSwapBuffers(window);

    if (acc_t > core::TICK_RATE_NANO) {
      glfwPollEvents();
      acc_t -= core::TICK_RATE_NANO;
    }

    end_t = tm::steady_clock::now();
    acc_t += (end_t - start_t).count();
    delta_t = tm::duration<float>(end_t - start_t).count();
    start_t = end_t;
  }
}

static void update() {
  auto start_t = tm::steady_clock::now();
  auto end_t = start_t;
  long acc_t = 0;

  while (running) {
    if (acc_t > core::TICK_RATE_NANO) {
      cur_scene->update(delta_t);
      acc_t -= core::TICK_RATE_NANO;
    }

    end_t = tm::steady_clock::now();
    acc_t += (end_t - start_t).count();
    start_t = end_t;
  }
}

void set_scene(scene::Type *s) { cur_scene = s; }
void close() { running = false; }
bool nop() { return true; }
void null() {}
} // namespace core

int main() {
  using namespace core;

  if (!init()) {
    return -1;
  }

  std::thread update_thread(update);
  render();
  update_thread.join();

  for (const auto s : scene::REFS) {
    s->clean();
  }

  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}
