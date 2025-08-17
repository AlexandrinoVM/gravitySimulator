#ifndef VBO_H
#define VBO_H
#include <GL/glew.h>
#include <vector>
#include "../glm/glm.hpp"
class VBO{
    public:
    VBO(std::vector<float>&data);
    VBO(std::vector<glm::vec3> &data);
    VBO(float *data,size_t size);
    void bindBuffer(unsigned int TYPE);
    void loadData(unsigned int TYPE,unsigned int sizeVertices,float verticesData[],unsigned int TYPEDRAW);
    void loadData(unsigned int TYPE,unsigned int sizeVertices,int verticesData[],unsigned int TYPEDRAW);
    void unbind();
    private:
    unsigned int vbo;
    unsigned int qtd;

};

#endif
