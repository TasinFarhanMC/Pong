#include "scene.hpp"
#include <callbacks.hpp>
#include <core.hpp>

#include <iostream>

static void update(float delta_t) {}
static void update_gl() {}

namespace scene {
const Type PLAYGROUND{core::nop, core::null, update, update_gl, core::null};
}
