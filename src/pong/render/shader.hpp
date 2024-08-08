#pragma once

#include <glad/glad.h>

class Shader {
  GLuint id;
  const char *const vertex_src;
  const char *const fragment_src;

public:
  Shader(const char *const vertex_src, const char *const fragment_src)
      : vertex_src(vertex_src), fragment_src(fragment_src) {};

  bool init();

  void clean() { glDeleteProgram(id); }
  operator GLuint() const { return id; }
};
