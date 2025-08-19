#include "../headers/EBO.hpp"


EBO::EBO(){
    glGenBuffers(1,&ebo);
}

EBO::EBO(unsigned int &ebos){
    glGenBuffers(1,&ebos);
    ebo = ebos;
}
EBO::EBO(unsigned int *indices,int count){
    glGenBuffers(1,&ebo);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count *sizeof(indices),indices,GL_STATIC_DRAW);

}

void EBO::setData(std::vector<unsigned int>indices){

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),indices.data(),GL_STATIC_DRAW);

}

void EBO::bindEBO(){
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo);
}


void EBO::unbidEBO(){
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
}
