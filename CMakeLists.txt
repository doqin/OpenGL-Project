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
  main.cpp
  src/glad.c
  src/shader.cpp
  src/camera.cpp
)

target_include_directories(${PROJECT_NAME}
  PRIVATE ${PROJECT_SOURCE_DIR}/include
)

# Link libraries
if (WIN32)
  target_link_libraries(${PROJECT_NAME}
    PRIVATE ${LIBRARIES_DIR}/glfw3dll.lib
  )
elseif(APPLE)
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
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${PROJECT_SOURCE_DIR}/shaders
  $<TARGET_FILE_DIR:${PROJECT_NAME}>/shaders
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${PROJECT_SOURCE_DIR}/assets
  $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets
)


# Installation rules
install(TARGETS ${PROJECT_NAME}
  BUNDLE DESTINATION build
  RUNTIME DESTINATION bin
)

# Copy shaders and assets to the app bundle's Resources directory
if(APPLE)
  set(RESOURCE_DIR "${CMAKE_BINARY_DIR}/${PROJECT_NAME}.app/Contents/Resources")
  add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${RESOURCE_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${PROJECT_SOURCE_DIR}/shaders
    ${RESOURCE_DIR}/shaders
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${PROJECT_SOURCE_DIR}/assets
    ${RESOURCE_DIR}/assets
  )
endif()

# Include CPack to create a package

# Configure CPack
set(CPACK_PACKAGE_NAME "OpenGL-Project")
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_PACKAGE_DESCRIPTION "Personal project for learning OpenGL")
set(CPACK_PACKAGE_VENDOR "doquyen")
set(CPACK_PACKAGE_CONTACT "business.doqin@gmail.com")
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}")
set(CPACK_GENERATOR "ZIP")

# Specify files to include in package
if(WIN32)
  install(FILES "${LIBRARIES_DIR}/glfw3.dll" DESTINATION bin)
endif()
install(DIRECTORY "${PROJECT_SOURCE_DIR}/shaders" DESTINATION bin)
install(DIRECTORY "${PROJECT_SOURCE_DIR}/assets" DESTINATION bin)

# Create a README file
file(WRITE "${CMAKE_BINARY_DIR}/README.md" "## OpenGL Project\n\n## How to Run\n\n1. Extract the ZIP file.\n2. Ensure \`glfw3.dll\` is in the same directory as \`OpenGL-Project.exe\`.\n3. Run \`OpenGL-Project.exe\`.\n\n## Requirements\n\n- Windows OS\n- OpenGL 3.3 or higher")
install(FILES "${CMAKE_BINARY_DIR}/README.md" DESTINATION bin)

# Include CPack
include(CPack)

