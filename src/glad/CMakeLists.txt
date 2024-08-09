add_library(glad STATIC glad.c
                        "${CMAKE_CURRENT_SOURCE_DIR}/headers/glad/glad.h")

find_package(OpenGL REQUIRED)

target_link_libraries(glad PUBLIC OpenGL::GL)
target_include_directories(glad PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/headers")
