#ifndef VBO_H
#define VBO_H
#include <GL/glew.h>
#include <vector>
class VBO{
    public:
    VBO(std::vector<float>&data);
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
