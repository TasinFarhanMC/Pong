add_executable(pong main.cpp main.hpp callbacks.cpp callbacks.hpp scene.hpp
                    Scenes/playground.cpp)

set_target_properties(pong PROPERTIES CMAKE_C_STANDARD 17 CMAKE_CXX_STANDARD 17)
target_include_directories(pong PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(pong PRIVATE glad glfw)
