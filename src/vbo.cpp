#include "../headers/VBO.hpp"


VBO::VBO(float *data,size_t size){
    glGenBuffers(1,&vbo);

    glBindBuffer(GL_ARRAY_BUFFER,vbo);

    glBufferData(GL_ARRAY_BUFFER,size,data,GL_STATIC_DRAW);
}
VBO::VBO(std::vector<glm::vec3> &data){
    glGenBuffers(1,&vbo);

    glBindBuffer(GL_ARRAY_BUFFER,vbo);

    glBufferData(GL_ARRAY_BUFFER,data.size()*sizeof(glm::vec3),data.data(),GL_STATIC_DRAW);
}


VBO::VBO(std::vector<float> &data){
    glGenBuffers(1,&vbo);

    glBindBuffer(GL_ARRAY_BUFFER,vbo);

    glBufferData(GL_ARRAY_BUFFER,data.size()*sizeof(float),data.data(),GL_STATIC_DRAW);
}

void VBO::bindBuffer(unsigned int TYPE){
    glBindBuffer(TYPE,vbo);
}

void VBO::loadData(unsigned int TYPE,unsigned int sizeVertices,float verticesData[],unsigned int TYPEDRAW){
    glBufferData(TYPE,sizeVertices,verticesData,TYPEDRAW);
}


void VBO::unbind(){
    glBindBuffer(GL_ARRAY_BUFFER,0);
}
