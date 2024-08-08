#include "shader.hpp"

#include <iostream>

bool shader_error(GLuint shader, const char *const info) {
  GLint compiled;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

  if (!compiled) {
    GLint length;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

    char *log = new char[length];
    glGetShaderInfoLog(shader, length, &length, log);
    std::cerr << info << log << std::endl;
    delete[] log;
  }

  return !compiled;
}

bool Shader::init() {
  GLuint vert = glCreateShader(GL_VERTEX_SHADER);
  GLuint frag = glCreateShader(GL_FRAGMENT_SHADER);

  glShaderSource(vert, 1, &vertex_src, nullptr);
  glShaderSource(frag, 1, &fragment_src, nullptr);

  glCompileShader(vert);
  if (shader_error(vert, "Vertex Shader Compilation Failed: ")) {
    return false;
  }

  glCompileShader(frag);
  if (shader_error(frag, "Fragment Shader Compilation Failed: ")) {
    glDeleteShader(vert);
    return false;
  }

  id = glCreateProgram();

  glAttachShader(id, vert);
  glAttachShader(id, frag);

  glLinkProgram(id);

  GLint linked;
  glGetProgramiv(id, GL_LINK_STATUS, &linked);
  if (!linked) {
    GLint length;
    glGetProgramiv(id, GL_INFO_LOG_LENGTH, &length);

    char *log = new char[length];
    glGetProgramInfoLog(id, length, &length, log);
    std::cerr << "Program Linking Failed: " << log << std::endl;
    delete[] log;

    glDeleteShader(vert);
    glDeleteShader(frag);

    return false;
  }

  glDeleteShader(vert);
  glDeleteShader(frag);

  return true;
}
