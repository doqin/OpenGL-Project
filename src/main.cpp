// OpenGL headers
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Image loading library
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

// OpenGL math library
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <shader.hpp>
#include <iostream>

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void processInput(GLFWwindow* window);

int main() {
  // Set the function to flip the image vertically
  stbi_set_flip_vertically_on_load(true);

  glfwInit(); // Initialize GLFW
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // Configure GLFW to use OpenGL version 3.X
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // Configure GLFW to use OpenGL version X.3
  glfwWindowHint(
      GLFW_OPENGL_PROFILE,
      GLFW_OPENGL_CORE_PROFILE); // Configure GLFW to use Core Profile

  #ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // For Macos to work
  #endif
  
  // Create GLFW window
  GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL Project", NULL, NULL);
  if (window == NULL) {
    std::cout << "Failed to create GLFW window\n";
    glfwTerminate();
    return -1;
  }
  // Get OpenGL context
  glfwMakeContextCurrent(window);
  // Frame buffer callback
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // Initialize GLAD
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD\n";
  }

  glEnable(GL_DEPTH_TEST);

  // Create shader program
  Shader glShader("../src/shaders/shader.vert", "../src/shaders/shader.frag");

  // Triangle's vertices
  float vertices[] = {
    // positions                      // texture coords
    // Back side
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
    // Front side
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    // Left side
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    // Right side
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    // Bottom side
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    // Top side
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
  };

  // 
  // Texture
  //

  unsigned int texture;
  glGenTextures(1, &texture);
  // Bind the texture
  glBindTexture(GL_TEXTURE_2D, texture);
  // Set the texture wrapping parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  // Set texture filtering
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR); // nearest neighbor interpolation
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // linear interpolation
  // Load image
  int width, height, nrChannels;
  unsigned char* data = stbi_load("../asset/textures/kotori_pfp.png", &width, &height, &nrChannels, 0);
  
  if (data) {
    std::cout << "Texture loaded successfully: " << width << "x" << height << " with " << nrChannels << " channels\n";
    // Generate texture
    // Parameters:
    // 1. The texture target, GL_TEXTURE_2D is a 2D texture, any texture bound to this target will be a 2D texture
    // 2. The mipmap level, 0 is the base level
    // 3. The internal format of the texture, the number of color components in the texture
    // 4. The width of the texture
    // 5. The height of the texture
    // 6. The border of the texture (must be 0 as of OpenGL 3.0)
    // 7. The format of the pixel data
    // 8. The data type of the pixel data
    // 9. The image data
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    // Generate mipmaps
    glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    std::cout << "ERROR::TEXTURE::FAILED_TO_LOAD\n";
  }
  // Free the image data
  stbi_image_free(data);

  unsigned int VAO, VBO;
  // Generate 1 of the VAO
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);
  // Generate 1 of the VBO
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);

  // Copy the vertices to the buffer
  // GL_STATIC_DRAW means the data is set once and used many times
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  // Copy the indices to the buffer

  // Position attribute

  // Tell OpenGL how to interpret the vertex data
  // First parameter is the location of the vertex attribute in the vertex shader (layout (location = 0))
  // Second parameter is the size of the vertex attribute (vec3 has 3 values x, y, z so it is 3)
  // Third parameter is the type of the data (vec* in GLSL consists of floats)
  // Fourth parameter is whether the data should be normalized
  // Fifth parameter is the stride of the data, the space between consecutive vertex attributes 
  // (can use 0 to let OpenGL determine the stride)
  // Sixth parameter is the offset of the data
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
  // Enable the vertex attribute with location 0, the vertex attribute is disabled by default
  glEnableVertexAttribArray(0);

  /* Unused
  // Color attribute
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
  */

  // Texture attribute
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(2);

  // Coordinate systems

  // View matrix
  glm::mat4 view = glm::mat4(1.0f);
  view = glm::translate(view, glm::vec3(0.0f, 0.0f, -8.0f)); // Moves the scene backward (moving the camera away)

  // Projection matrix
  glm::mat4 projection;
  projection = glm::perspective(glm::radians(45.0f), (float) SCR_WIDTH / SCR_HEIGHT, 0.1f, 100.0f);

  // Set uniforms
  glShader.use();
  glShader.setMat4("view", view);
  glShader.setMat4("projection", projection);

  // Instances of cube
  glm::vec3 cubePositions[10];
  for (unsigned int i = 0; i < 10; i++) {
    cubePositions[i].x = (float) (rand() % 1000) / 100.0f - 5.0f;
    cubePositions[i].y = (float) (rand() % 1000) / 100.0f - 5.0f;
    cubePositions[i].z = (float) (rand() % 1000) / 100.0f - 5.0f;
  }

  // 
  // Render loop
  //

  while(!glfwWindowShouldClose(window)) {
    // Input
    processInput(window);

    //
    // Render commands
    //

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    // Specify what to clear
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Bind the texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    // Use the shader program
    glShader.use();
    glShader.setInt("ourTexture", 0);

    // Bind VAO to use the vertex data
    glBindVertexArray(VAO);

    for (unsigned int i = 0; i < 10; i++) {
      // Model matrix
      glm::mat4 model = glm::mat4(1.0f);
      model = glm::translate(model, cubePositions[i]);
      model = glm::rotate(model, (float)glfwGetTime() * glm::radians(55.0f) + i * glm::radians(45.0f), glm::vec3(1.0f, 0.3f, 0.5f));
      glShader.setMat4("model", model);

      // Draw the triangle
      glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    // Check and call events and swap buffers
    glfwPollEvents();
    glfwSwapBuffers(window);
  }
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);

  glfwTerminate();
  return 0;
}

// Updates viewport when window resizes

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}
