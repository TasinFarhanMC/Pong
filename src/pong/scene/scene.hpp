#pragma once

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
