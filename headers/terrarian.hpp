#ifndef TERRARIAN_H
#define TERRARIAN_H

#include <vector>
#include "../headers/VAO.hpp"
#include "../headers/VBO.hpp"
#include "../headers/EBO.hpp"
#include "../headers/SHADER.hpp" 
#include <iostream>
#include "../utils/sphereData.hpp"
#include <math.h>
#include  <map>
class terrarian {
public:
    void Draw(shader &Shader,glm::mat4 view,glm::mat4 projection);
    void close(){delete(vao);delete(ebo);delete(vbo);};
    void getSpData(std::map<int,sp::sphereData> &data){datasp = data;SetupData();}; 
    void setuPbuffers();
private:
    void setupYGrid();
    std::map<int,sp::sphereData> datasp;
    void SetupData();
    VAO *vao;
    VBO *vbo;
    EBO *ebo;
    std::vector<glm::vec3> vertices;
    std::vector<unsigned int> indices;
    std::vector<float> yGridDeclines;
};

#endif

