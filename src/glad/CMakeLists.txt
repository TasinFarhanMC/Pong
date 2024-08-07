add_library(glad STATIC glad.c "${CMAKE_SOURCE_DIR}/include/glad/glad/glad.h")

find_package(OpenGL REQUIRED)

target_link_libraries(glad PUBLIC OpenGL::GL)
target_include_directories(glad PUBLIC "${CMAKE_SOURCE_DIR}/include/glad")
