#include "core.hpp"
#include <callbacks.hpp>
#include <scene/scene.hpp>

#include <glad/glad.h>

#include <atomic>
#include <chrono>
#include <iostream>
#include <mutex>
#include <shared_mutex>
#include <thread>

namespace core {
static std::shared_mutex scene_mutex;
static const scene::Type *cur_scene = &scene::PLAYGROUND;
static std::mutex delta_mutex;
static float delta_t = 0.0f;
static std::atomic<bool> running = true;

static bool init();
static void update();

GLFWwindow *window = nullptr;
} // namespace core

int main() {
  using namespace core;

  if (!init()) {
    return -1;
  }

  std::thread update_thread(update);
  while (running.load(std::memory_order_acquire)) {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    scene_mutex.lock_shared();
    cur_scene->render();
    scene_mutex.unlock_shared();
    glfwSwapBuffers(window);

    static auto start_t = std::chrono::steady_clock::now();
    static auto end_t = start_t;
    static float diff_t = 0.0f;

    if (diff_t > core::TICK_RATE_NANO) {
      glfwPollEvents();
      cur_scene->update_gl();

      if (callback::key::get_state(callback::key::State::Press, GLFW_KEY_F11)) {
        GLFWmonitor *mon = (glfwGetWindowMonitor(window) == nullptr)
                               ? glfwGetPrimaryMonitor()
                               : nullptr;

        glfwSetWindowMonitor(window, mon, 0, 0, 100, 100, GLFW_DONT_CARE);
      }

      diff_t -= core::TICK_RATE_NANO;
    }

    end_t = std::chrono::steady_clock::now();
    auto delta_nano = (end_t - start_t).count();
    diff_t += delta_nano;
    std::lock_guard<std::mutex> lock(delta_mutex);
    delta_t = delta_nano / 1000000000.0f;
    start_t = end_t;
  }
  update_thread.join();

  for (const auto s : scene::REFS) {
    s->clean();
  }

  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}

namespace core {
bool init() {
  if (!glfwInit()) {
    std::cerr << "Unable to init glfw" << std::endl;
    return false;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window = glfwCreateWindow(100, 100, "Pong", nullptr, nullptr);
  if (!window) {
    std::cerr << "Unable to create window" << std::endl;
    glfwTerminate();
    return false;
  }
  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
    std::cerr << "Unable to init glad" << std::endl;
    glfwDestroyWindow(window);
    glfwTerminate();
    return false;
  }

  glfwSetWindowCloseCallback(window,
                             reinterpret_cast<GLFWwindowclosefun>(close));
  glfwSetKeyCallback(window, callback::key::fun);

  for (const auto s : scene::REFS) {
    if (!s->init()) {
      glfwDestroyWindow(window);
      glfwTerminate();
      return false;
    }
  }

  return true;
}

void update() {
  auto start_t = std::chrono::steady_clock::now();
  auto end_t = start_t;
  float diff_t = 0.0f;

  while (running.load(std::memory_order_acquire)) {
    if (diff_t > core::TICK_RATE_NANO) {
      std::shared_lock<std::shared_mutex> lock1(scene_mutex);
      std::lock_guard<std::mutex> lock2(delta_mutex);
      cur_scene->update(delta_t);
      diff_t -= core::TICK_RATE_NANO;
    }

    end_t = std::chrono::steady_clock::now();
    diff_t += (end_t - start_t).count();
    start_t = end_t;
  }
}

void set_scene(scene::Type *s) {
  std::lock_guard<std::shared_mutex> lock(scene_mutex);
  cur_scene = s;
}

void close() { running.store(false, std::memory_order_release); }
void null() {}
bool nop() { return true; }
} // namespace core
