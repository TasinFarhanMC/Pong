#include "scene.hpp"
#include <core.hpp>

#include <iostream>

static void update(float delta_t) { std::cout << 1.0f / delta_t << std::endl; }

namespace scene {
const Type PLAYGROUND{core::nop, core::null, update, core::null, core::null};
}
