#ifndef SPHERE_H
#define SPHERE_H
#include <GL/glew.h>
#include <vector>
#include "../glm/glm.hpp"
#include <math.h>
#include "../headers/SHADER.hpp"
#include "../headers/VAO.hpp"
#include "../headers/EBO.hpp"
#include "../headers/VBO.hpp"

class sphere{
public:
    sphere(float r,unsigned int stack,unsigned int sector): r(r),stack(stack),sector(sector){
        setup();
    };
    static constexpr double pi  =3.14159265359;
    void Draw(shader &s,glm::mat4 view,glm::mat4 projection);
    void close();
private:
    VAO *vao;
    EBO *ebo;
    VBO *vbo;

    void setup();
    float r;
    unsigned int stack,sector;

    std::vector<glm::vec3> vertices;
    std::vector<unsigned int> indices;

};


#endif


