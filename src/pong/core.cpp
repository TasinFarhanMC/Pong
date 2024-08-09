#define GLFW_INCLUDE_NONE

#include "core.hpp"
#include <callbacks.hpp>
#include <scene/scene.hpp>

#include <glad/glad.h>

#include <chrono>
#include <iostream>
#include <thread>

namespace core {
static volatile bool running = true;
static SecondDecimal delta(0);
static const scene::Object *current_scene = &scene::PLAYGROUND;

IVec2 screen_size;
GLFWwindow *window;
GLFWmonitor *monitor;

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

  window = glfwCreateWindow(screen_size.x * 2 / 3, screen_size.y * 2 / 3, TITLE,
                            nullptr, nullptr);
  if (!window) {
    std::cerr << "Unable to create window" << std::endl;

    glfwTerminate();
    return false;
  }

  glfwMakeContextCurrent(window);
  if (!glad_load_gl_loader(
          reinterpret_cast<GladLoadProc>(glfwGetProcAddress))) {
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

  for (const auto scene : scene::REFERENCES) {
    if (!scene->init()) {
      goto EXIT_GLFW;
    }
  }

  return true;
}

static void render() {
  TimePoint<SteadyClock, NanoSecond> start = SteadyClock::now();
  TimePoint<SteadyClock, NanoSecond> end;
  NanoSecond accumilator(0);

  while (running) {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    current_scene->render();
    glfwSwapBuffers(window);

    if (accumilator > TICK_RATE) {
      glfwPollEvents();
      accumilator -= TICK_RATE;
    }

    end = SteadyClock::now();
    accumilator += end - start;
    delta = end - start;
    start = end;
  }
}

static void update() {
  TimePoint<SteadyClock, NanoSecond> start = SteadyClock::now();
  TimePoint<SteadyClock, NanoSecond> end;
  NanoSecond accumilator(0);

  while (running) {
    if (accumilator > TICK_RATE) {
      current_scene->update(delta);
      accumilator -= TICK_RATE;
    }

    end = SteadyClock::now();
    accumilator += end - start;
    start = end;
  }
}

void set_scene(scene::Object *scene) { current_scene = scene; }
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

  for (const auto scene : scene::REFERENCES) {
    scene->clean();
  }

  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}
