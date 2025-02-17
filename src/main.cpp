#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <readFile.hpp>
#include <iostream>

const std::string vertexShaderSource = readFile("shaders/vertexShader.glsl");
const std::string fragmentShaderSource = readFile("shaders/fragmentShader.glsl");

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

  // 
  // Creating the vertex shader
  //

  // 1. Create a vertex shader
  unsigned int vertexShader;
  vertexShader = glCreateShader(GL_VERTEX_SHADER);

  // 2. Attach the shader source code to the shader object and compile the shader
  const char* vertexShaderSourceCStr = vertexShaderSource.c_str();
  glShaderSource(vertexShader, 1, &vertexShaderSourceCStr, NULL);
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
  // Creating the fragment shader
  // 

  // Same 3 steps as the vertex shader
  unsigned int fragmentShader;
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  const char* fragmentShaderSourceCStr = fragmentShaderSource.c_str();
  glShaderSource(fragmentShader, 1, &fragmentShaderSourceCStr, NULL);
  glCompileShader(fragmentShader);

  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
              << infoLog << std::endl;
  }

  //
  // Creating the shader program
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
  
  // Set OpenGL's viewport
  glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

  // Triangle's vertices
  float vertices[] = {
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.0f, 0.5f, 0.0f
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

  // Tell OpenGL how to interpret the vertex data
  // First parameter is the location of the vertex attribute in the vertex shader (layout (location = 0))
  // Second parameter is the size of the vertex attribute (vec3 has 3 values x, y, z so it is 3)
  // Third parameter is the type of the data (vec* in GLSL consists of floats)
  // Fourth parameter is whether the data should be normalized
  // Fifth parameter is the stride of the data, the space between consecutive vertex attributes 
  // (can use 0 to let OpenGL determine the stride)
  // Sixth parameter is the offset of the data
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  // Enable the vertex attribute with location 0, the vertex attribute is disabled by default
  glEnableVertexAttribArray(0);


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

    // Draw the triangle
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // Check and call events and swap buffers
    glfwPollEvents();
    glfwSwapBuffers(window);

  }
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteProgram(shaderProgram);

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
