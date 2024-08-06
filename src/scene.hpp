#pragma once

struct Scene_t {
  void (*init)();
  void (*render)();
  void (*update)(float delta_t);
  void (*clean)();
};

namespace Scene {
extern const Scene_t playground;
} // namespace Scene
