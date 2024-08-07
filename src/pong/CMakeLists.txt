add_executable(pong core.cpp core.hpp callbacks.cpp callbacks.hpp
                    scene/scene.hpp scene/playground.cpp)

set_target_properties(
  pong
  PROPERTIES CMAKE_C_STANDARD 17
             CMAKE_CXX_STANDARD 17
             CMAKE_C_STANDARD_REQUIRED True
             CMAKE_CXX_STANDARD_REQUIRED True)

target_include_directories(pong PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(pong PRIVATE glad glfw)
