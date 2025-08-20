#ifndef SPHERE_H
#define SPHERE_H
#include <GL/glew.h>
#include <vector>
#include <SDL2/SDL.h>
#include "../glm/glm.hpp"
#include <math.h>
#include <map>
#include "../headers/SHADER.hpp"
#include "../headers/VAO.hpp"
#include "../headers/EBO.hpp"
#include "../headers/VBO.hpp"
#include "../utils/sphereData.hpp"

struct bufferMeshi{
    VAO vao;
    VBO vbo;
    EBO ebo;
    bufferMeshi(){};
      bufferMeshi(std::vector<glm::vec3> &vertices, std::vector<unsigned int> &indices)
        : vao(), vbo(), ebo()
    {
        vao.bindVAO();
        vbo.vboSetData(vertices);
        vao.VAOatribs(0, 3, sizeof(glm::vec3), 0); 
        ebo.bindEBO();
        ebo.setData(indices);
        vao.unbidVAO();
    }
};

class sphere{
public:
    void Createsphere(float raio,unsigned int stacks,unsigned int sectors,glm::vec3 position){
        r = raio;
        spdta.raio = r;
        spdta.positions =position;
        spdta.sectors = sectors;
        spdta.stacks = stacks;
        spdta.currPos = position;
        spheres[iterator] = spdta;
        stack = stacks;
        sector = sectors;
        
        iterator++;
        setup();
    };
    static constexpr double pi  =3.14159265359;
    void Draw(shader &s,glm::mat4 view,glm::mat4 projection);
    void close();
    std::map<int,sp::sphereData>&getData(){return spheres;};
private:
    glm::vec3 objPosition ={0.0f,10.0f,-1.0f};
    sp::sphereData spdta;
    unsigned int iterator =0;
    std::map<int,sp::sphereData> spheres;
    VAO *vao;
    EBO *ebo;
    VBO *vbo;
    std::map<int,bufferMeshi> buffes;
    std::map<int,int> indicessize;
    void setup();
    float r;
    unsigned int stack,sector;

    std::vector<glm::vec3> vertices;
    std::vector<unsigned int> indices;

};


#endif


