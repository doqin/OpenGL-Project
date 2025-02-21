cmake_minimum_required(VERSION 3.15)
project(
OpenGL-Project VERSION 1.0
DESCRIPTION "Personal project for learning OpenGL"
LANGUAGES C CXX)

if(WIN32)
  set(CMAKE_C_COMPILER gcc)
  set(CMAKE_CXX_COMPILER g++)
elseif(APPLE)
  set(CMAKE_C_COMPILER clang)
  set(CMAKE_CXX_COMPILER clang++)
endif()

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
  src/shaders/shader.cpp
  src/camera.cpp
)

target_include_directories(${PROJECT_NAME}
  PRIVATE ${PROJECT_SOURCE_DIR}/include
)

if (WIN32)
  target_link_libraries(${PROJECT_NAME}
    PRIVATE ${LIBRARIES_DIR}/glfw3dll.lib
  )
elseif()
  target_link_libraries(${PROJECT_NAME}
    PRIVATE ${LIBRARIES_DIR}/libglfw.3.dylib
  )
else()
  target_link_libraries(${PROJECT_NAME}
    PRIVATE ${LIBRARIES_DIR}/libglfw3.so
  )
endif()

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
    -Wall -Wextra -Wpedantic)
endif()

# Copy glfw3.dll to the output directory
if(WIN32)
  add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${LIBRARIES_DIR}/glfw3.dll
    $<TARGET_FILE_DIR:${PROJECT_NAME}>)
endif()


# Installation rules
install(TARGETS ${PROJECT_NAME}
  BUNDLE DESTINATION build
  RUNTIME DESTINATION bin
)

