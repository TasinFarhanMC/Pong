#define GLFW_INCLUDE_NONE

#include "scene.hpp"
#include <callbacks.hpp>
#include <core.hpp>
#include <render/shader.hpp>

#include <glad/glad.h>

#include <iostream>

static GLuint vbo, vao;

static auto vert_src = R"(
  #version 330 core

  layout(location = 0) in vec4 a_pos;

  void main() {
    gl_Position = a_pos;
  }
)";

static auto frag_src = R"(
  #version 330 core
  
  out vec4 color;

  void main() {
    color = vec4(1.0f, 1.0f, 1.0f, 1.0f);
  }
)";

static Shader shader(vert_src, frag_src);

static bool init() {
  if (!shader.init()) {
    return false;
  }

  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);

  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6,
               (float[]){0.0f, 0.5f, 0.5f, -0.5f, -0.5f, -0.5f},
               GL_STATIC_DRAW);

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void *)0);
  glEnableVertexAttribArray(0);

  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  return true;
}

static void render() {
  glBindVertexArray(vao);
  glUseProgram(shader);
  glDrawArrays(GL_TRIANGLES, 0, 3);
  glUseProgram(0);
  glBindVertexArray(0);
}

static void update(SecondDecimal delta) {}

static void clean() {
  glDeleteVertexArrays(1, &vao);
  glDeleteBuffers(1, &vbo);
  shader.clean();
}

namespace scene {
const Object PLAYGROUND{init, render, update, clean};
}
