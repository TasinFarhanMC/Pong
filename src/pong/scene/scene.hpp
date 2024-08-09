#pragma once

#include <def.hpp>

namespace scene {
struct Object {
  Function<bool()> init;
  Function<void()> render;
  Function<void(SecondDecimal delta)> update;
  Function<void()> clean;
};

extern const Object PLAYGROUND;
inline const Object *REFERENCES[] = {&PLAYGROUND};
} // namespace scene
