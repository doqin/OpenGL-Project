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

#include <camera.hpp>
#include <shader.hpp>
#include <iostream>

// Screen size
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// Mouse position
float lastX = (float) SCR_HEIGHT / 2;
float lastY = (float) SCR_WIDTH / 2;

// Stops mouse jumping
bool firstMouse = true;

// Delta time
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// Camera
Camera glCamera;

// Declarations
void framebuffer_size_callback(GLFWwindow*, int, int);
void mouse_callback(GLFWwindow*, double, double);
void scroll_callback(GLFWwindow*, double, double);
void processInput(GLFWwindow*);

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

  // Setup mouse input
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  glfwSetCursorPosCallback(window, mouse_callback);
  glfwSetScrollCallback(window, scroll_callback);

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
  std::cout << "\nSHADER: Creating Object shader program\n";
  Shader objShader("../src/shaders/shader.vert", "../src/shaders/shader.frag");
  std::cout << "\nSHADER: Creating Light shader program\n";
  Shader lightShader("../src/shaders/light_shader.vert", "../src/shaders/light_shader.frag");
  std::cout << "\nSHADER: Creating Light source program\n";
  Shader lightSource("../src/shaders/light_source.vert", "../src/shaders/light_source.frag");

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

  unsigned int VBO;
  // Generate 1 of the VBO
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  // Upload data to buffer
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  unsigned int VAO;
  // Generate 1 of the VAO
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);
  
  // Load attribute intepretation of previously bind VAO using vertex data from previously bind VBO
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
  // Enable the vertex attribute with location 0, the vertex attribute is disabled by default
  glEnableVertexAttribArray(0);
  // Texture attribute
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(2);

  unsigned int lightVAO;
  glGenVertexArrays(1, &lightVAO);
  glBindVertexArray(lightVAO);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  // Coordinate systems

  // View matrix
  glm::mat4 view = glCamera.GetViewMatrix();

  // Projection matrix
  glm::mat4 projection;
  projection = glm::perspective(glm::radians(glCamera.Zoom), (float) SCR_WIDTH / SCR_HEIGHT, 0.1f, 100.0f);

  // Set uniforms
  // Setup Object shader
  objShader.use();
  objShader.setMat4("projection", projection);
  // Instances of cube
  glm::vec3 cubePositions[10];
  for (unsigned int i = 0; i < 10; i++) {
    cubePositions[i].x = (float) (rand() % 1000) / 100.0f - 5.0f;
    cubePositions[i].y = (float) (rand() % 1000) / 100.0f - 5.0f;
    cubePositions[i].z = (float) (rand() % 1000) / 100.0f - 5.0f;
  }
  // Setup Light shader
  lightShader.use();
  lightShader.setMat4("projection", projection);
  lightShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
  lightShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
  glm::vec3 cubePos;
  cubePos.x = (float) (rand() % 1000) / 100.0f - 5.0f;
  cubePos.y = (float) (rand() % 1000) / 100.0f - 5.0f;
  cubePos.z = (float) (rand() % 1000) / 100.0f - 5.0f;
  glm::mat4 model = glm::mat4(1.0f);
  model = glm::translate(model, cubePos);
  lightShader.setMat4("model", model);
  // Setup Light source
  lightSource.use();
  lightSource.setMat4("projection", projection);
  glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
  model = glm::mat4(1.0f);
  model = glm::translate(model, lightPos);
  model = glm::scale(model, glm::vec3(0.2f));
  lightSource.setMat4("model", model);

  // 
  // Render loop
  //

  while(!glfwWindowShouldClose(window)) {

    // Update delta time
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    // Input
    processInput(window);

    //
    // Render commands
    //

    // Sky color
    glClearColor(0.53f, 0.80f, 0.8f, 0.92f);
    // Specify what to clear
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Bind the texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    // Render kako cubes
    glBindVertexArray(VAO);
    objShader.use();
    objShader.setInt("ourTexture", 0);
    view = glCamera.GetViewMatrix();
    objShader.setMat4("view", view);
    for (unsigned int i = 0; i < 10; i++) {
      // Model matrix
      glm::mat4 model = glm::mat4(1.0f);
      model = glm::translate(model, cubePositions[i]);
      model = glm::rotate(model, (float)glfwGetTime() * glm::radians(55.0f) + i * glm::radians(45.0f), glm::vec3(1.0f, 0.3f, 0.5f));
      objShader.setMat4("model", model);

      // Draw the cube
      glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    // Render light source
    lightSource.use();
    lightSource.setMat4("view", view);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    // Render light affected cube
    glBindVertexArray(lightVAO);
    lightShader.use();
    lightShader.setMat4("view", view);
    glDrawArrays(GL_TRIANGLES, 0, 36);

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

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
  if (firstMouse) {
    lastX = xpos;
    lastY = ypos;
    firstMouse = false;
  }

  float xoffset = xpos - lastX;
  float yoffset = lastY - ypos; // reversed since y-coordinates range from bottom to top
  lastX = xpos;
  lastY = ypos;

  glCamera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
  glCamera.ProcessMouseScroll(yoffset);
}

void processInput(GLFWwindow* window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
    glCamera.ProcessKeyboard(FORWARD, deltaTime);
  }
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
    glCamera.ProcessKeyboard(BACKWARD, deltaTime);
  }
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
    glCamera.ProcessKeyboard(LEFT, deltaTime);
  }
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
    glCamera.ProcessKeyboard(RIGHT, deltaTime);
  }
  if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
    glCamera.ProcessKeyboard(UP, deltaTime);
  }
  if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
    glCamera.ProcessKeyboard(DOWN, deltaTime);
  }
}
