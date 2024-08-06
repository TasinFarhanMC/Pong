#include <scene.hpp>

static void init() {}
static void render() {}
static void update(float delta_t) {}
static void clean() {}

namespace Scene {
const Scene_t playground{init, render, update, clean};
}
