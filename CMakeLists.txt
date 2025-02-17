cmake_minimum_required(VERSION 3.15)
project(
OpenGL-Project VERSION 1.0
DESCRIPTION "Personal project for learning OpenGL"
LANGUAGES C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(LIBRARIES_DIR ${PROJECT_SOURCE_DIR}/lib)

add_executable( ${PROJECT_NAME}
  src/main.cpp
  src/glad.c
  src/shaders/vertexShader.glsl
  src/shaders/fragmentShader.glsl
  src/readFile.cpp
)

target_include_directories(${PROJECT_NAME}
  PRIVATE ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME}
  PRIVATE ${LIBRARIES_DIR}/libglfw.3.dylib
)

if(APPLE AND CMAKE_BUILD_TYPE STREQUAL "Release")
  set_target_properties(${PROJECT_NAME}
    PROPERTIES MACOSX_BUNDLE TRUE)
endif()

# Compiler warning
if(MSVC)
  target_compile_options(${PROJECT_NAME} PRIVATE
    /W4>)
else()
  target_compile_options(${PROJECT_NAME} PRIVATE
    -Wall -Wextra -Wpedantic>)
endif()


# Installation rules
install(TARGETS ${PROJECT_NAME}
  BUNDLE DESTINATION build
  RUNTIME DESTINATION bin
)

