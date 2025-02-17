#include <cstddef>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <readFile.hpp>
#include <iostream>

const char *vertexShaderSource = readFile("src/shaders/vertexShader.glsl").c_str();
const char *fragmentShaderSource = readFile("src/shaders/fragmentShader.glsl").c_str();

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void processInput(GLFWwindow* window);

int main() {
  glfwInit(); // Initialize GLFW
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // Configure GLFW to use OpenGL version 3.X
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // Configure GLFW to use OpenGL version X.3
  glfwWindowHint(
      GLFW_OPENGL_PROFILE,
      GLFW_OPENGL_CORE_PROFILE); // Configure GLFW to use Core Profile
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // For Macos to work
  
  // Create GLFW window
  GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Project", NULL, NULL);
  if (window == NULL) {
    std::cout << "Failed to create GLFW window\n";
    glfwTerminate();
    return -1;
  }
  // Get OpenGL context
  glfwMakeContextCurrent(window);

  // Initialize GLAD
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD\n";
    return -1;
  }
  
  // Set OpenGL's viewport
  glViewport(0, 0, 800, 600);
  
  // Frame buffer callback
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // Triangle's vertices
  float vertices[] = {
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.0f, 0.5f, 0.0f
  };

  // 
  // First process: Preparing for the Vertex shader
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

  // 
  // Second process: Creating the vertex shader
  //

  // 1. Create a vertex shader
  unsigned int vertexShader;
  vertexShader = glCreateShader(GL_VERTEX_SHADER);

  // 2. Attach the shader source code to the shader object and compile the shader
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);

  // 3. Check if the shader compilation was successful
  int success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
              << infoLog << std::endl;
  }

  // 
  // Third process: Creating the fragment shader
  // 

  // Same 3 steps as the vertex shader
  unsigned int fragmentShader;
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);

  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
              << infoLog << std::endl;
  }

  //
  // Fourth process: Creating the shader program
  // 
  unsigned int shaderProgram;
  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
              << infoLog << std::endl;
  }

  // Delete the shaders as they are linked to the shader program
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  // Use the shader program
  glUseProgram(shaderProgram);

  // 
  // Render loop
  //

  while(!glfwWindowShouldClose(window)) {
    // Input
    processInput(window);

    // Render commands
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    // Specify what to clear
    glClear(GL_COLOR_BUFFER_BIT);

    // Check and call events and swap buffers
    glfwPollEvents();
    glfwSwapBuffers(window);

  }
  glfwTerminate();
  return 0;
}

// Updates viewport when window resizes

void framebuffer_size_callback(int width, int height) {
  glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}
