add_executable(
  pong
  core.cpp
  core.hpp
  callbacks.cpp
  callbacks.hpp
  scene/scene.hpp
  scene/playground.cpp
  render/shader.cpp
  render/shader.hpp)

set_target_properties(pong PROPERTIES CMAKE_CXX_STANDARD 20
                                      CMAKE_CXX_STANDARD_REQUIRED True)

target_include_directories(pong PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(pong PRIVATE glad glfw)
