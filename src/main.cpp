#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <shader.hpp>
#include <iostream>

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void processInput(GLFWwindow* window);

int main() {

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

  // Create shader program
  Shader glShader("../src/shaders/shader.vert", "../src/shaders/shader.frag");

  // Triangle's vertices
  float vertices[] = {
    // positions                  // colors
    -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
    0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom right
    0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f // top
  };



  // Generate Vertex Array Object
  unsigned int VAO;
  glGenVertexArrays(1, &VAO);

  glBindVertexArray(VAO);

  // 
  // Preparing for the Vertex shader
  //

  // 1. Create memory on GPU where to store the vertex data

  // Generate Vertex Buffer Object
  unsigned int VBO;
  // Generate 1 of the VBO
  glGenBuffers(1, &VBO);

  // 2. Configure how OpenGL should interpret the memory

  // Bind buffer of Array Buffer type, the buffer type of a vertex buffer Object
  // is GL_ARRAY_BUFFER
  glBindBuffer(GL_ARRAY_BUFFER, VBO);


  // 3. Specify how to send the data to the graphics card

  // Copies the previously defined vertex data into the bound buffer's memory
  // which is VBO currently
  // GL_STATIC_DRAW means the data is set once and used many times
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // Position attribute

  // Tell OpenGL how to interpret the vertex data
  // First parameter is the location of the vertex attribute in the vertex shader (layout (location = 0))
  // Second parameter is the size of the vertex attribute (vec3 has 3 values x, y, z so it is 3)
  // Third parameter is the type of the data (vec* in GLSL consists of floats)
  // Fourth parameter is whether the data should be normalized
  // Fifth parameter is the stride of the data, the space between consecutive vertex attributes 
  // (can use 0 to let OpenGL determine the stride)
  // Sixth parameter is the offset of the data
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
  // Enable the vertex attribute with location 0, the vertex attribute is disabled by default
  glEnableVertexAttribArray(0);

  // Color attribute
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  // Set OpenGL's viewport
  glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

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
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the triangle

    // Activate the shader program
    glShader.use();
    // Render the triangle
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

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
