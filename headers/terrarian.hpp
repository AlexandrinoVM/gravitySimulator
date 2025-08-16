#ifndef TERRARIAN_H
#define TERRARIAN_H

#include <vector>
#include "../headers/VAO.hpp"
#include "../headers/VBO.hpp"
#include "../headers/EBO.hpp"
#include "../headers/SHADER.hpp" 
#include <iostream>
class terrarian {
public:
    terrarian();
    void Draw(shader &Shader,glm::mat4 view,glm::mat4 projection);
    void close(){delete(vao);delete(ebo);delete(vbo);}
private:
    void SetupData();
    VAO *vao;
    VBO *vbo;
    EBO *ebo;
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
};

#endif

