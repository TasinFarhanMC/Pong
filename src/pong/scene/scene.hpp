#pragma once
#define GLFW_INCLUDE_NONE

namespace scene {
struct Type {
  bool (*init)();
  void (*render)();
  void (*update)(float delta_t);
  void (*update_gl)();
  void (*clean)();
};

extern const Type PLAYGROUND;
inline const Type *REFS[] = {&PLAYGROUND};
} // namespace scene
