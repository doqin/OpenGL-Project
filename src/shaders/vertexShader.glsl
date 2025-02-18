#version 330 core
layout (location = 0) in vec3 aPos;

out vec4 vertexColor; // specifies a color output

void main() {
  gl_Position = vec4(aPos.xyz, 1.0);
  vertexColor = vec4(0.5, 0.0, 0.0, 1.0); // set the output variable to a dark-red color
}
