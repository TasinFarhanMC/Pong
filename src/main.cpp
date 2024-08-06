#include "main.hpp"
#include <chrono>
#include <glad/glad.h>
#include <iostream>
#include <scene.hpp>
#include <thread>

namespace Main {
GLFWwindow *window = nullptr;
const float tick_t = 1.0f / 30.0f;
} // namespace Main

static const Scene_t *scene = &Scene::playground;
static void update();
static bool running = true;

int main() {
  using namespace Main;

  if (!glfwInit()) {
    std::cerr << "Unable to init glfw" << std::endl;
    return -1;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window = glfwCreateWindow(100, 100, "Pong", nullptr, nullptr);
  if (!window) {
    std::cerr << "Unable to create window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
    std::cerr << "Unable to init glad" << std::endl;
    glfwDestroyWindow(window);
    glfwTerminate();
    return -1;
  }
  glfwSetWindowCloseCallback(window,
                             reinterpret_cast<GLFWwindowclosefun>(close));

  Scene::playground.init();

  std::thread update_thread(update);
  while (running) {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    scene->render();
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  update_thread.join();

  Scene::playground.clean();

  glfwDestroyWindow(window);
  glfwTerminate();
}

void update() {
  while (running) {
    static auto start_t = std::chrono::steady_clock::now();
    static auto end_t = start_t;
    static float diff_t = 0.0f;

    if (diff_t > 1.0f / 30.0f) {
      scene->update(diff_t);
      diff_t -= 1.0f / 30.0f;
    }

    end_t = std::chrono::steady_clock::now();
    diff_t += std::chrono::duration<float>(end_t - start_t).count();
    start_t = end_t;
  }
}

void Main::close() { running = false; }
