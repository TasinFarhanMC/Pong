#include "scene.hpp"
#include <callbacks.hpp>
#include <core.hpp>

#include <glad/glad.h>

#include <iostream>

static GLuint vbo, vao, shader;

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

static bool init() {
  GLuint vert = glCreateShader(GL_VERTEX_SHADER);
  GLuint frag = glCreateShader(GL_FRAGMENT_SHADER);

  glShaderSource(vert, 1, &vert_src, nullptr);
  glShaderSource(frag, 1, &frag_src, nullptr);

  glCompileShader(vert);
  GLint vertCompiled;
  glGetShaderiv(vert, GL_COMPILE_STATUS, &vertCompiled);
  if (!vertCompiled) {
    GLint length;
    glGetShaderiv(vert, GL_INFO_LOG_LENGTH, &length);
    char *log = new char[length];
    glGetShaderInfoLog(vert, length, &length, log);
    std::cerr << "Vertex shader compile error: " << log << std::endl;
    delete[] log;
  }

  glCompileShader(frag);
  GLint fragCompiled;
  glGetShaderiv(frag, GL_COMPILE_STATUS, &fragCompiled);
  if (!fragCompiled) {
    GLint length;
    glGetShaderiv(frag, GL_INFO_LOG_LENGTH, &length);
    char *log = new char[length];
    glGetShaderInfoLog(frag, length, &length, log);
    std::cerr << "Fragment shader compile error: " << log << std::endl;
    delete[] log;
  }

  shader = glCreateProgram();

  glAttachShader(shader, vert);
  glAttachShader(shader, frag);

  glLinkProgram(shader);
  GLint programLinked;
  glGetProgramiv(shader, GL_LINK_STATUS, &programLinked);
  if (!programLinked) {
    GLint length;
    glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &length);
    char *log = new char[length];
    glGetProgramInfoLog(shader, length, &length, log);
    std::cerr << "Program link error: " << log << std::endl;
    delete[] log;
  }

  // No need for glValidateProgram
  // glValidateProgram(shader);

  glDeleteShader(vert);
  glDeleteShader(frag);

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

static void update(float delta_t) {}

static void clean() {
  glDeleteVertexArrays(1, &vao);
  glDeleteBuffers(1, &vbo);
  glDeleteProgram(shader);
}

namespace scene {
const Type PLAYGROUND{init, render, update, core::null, clean};
}
