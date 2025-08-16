#version 330 core
layout (location = 0) in vec3 aPos;
uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;
out vec3 fragColor;

void main() {
    gl_Position =projection*view*vec4(aPos, 1.0);
    fragColor = vec3(aPos.z > 0 ? 1.0 : 0.0, 0.0, 1.0);
}
