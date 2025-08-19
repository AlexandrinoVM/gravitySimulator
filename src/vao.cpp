#include "../headers/VAO.hpp"

VAO::VAO(){
    glGenVertexArrays(1,&vao);

    glBindVertexArray(vao);
}



void VAO::bindVAO(){
    glBindVertexArray(vao);
}
VAO::VAO(unsigned int &vaos){
    glGenVertexArrays(1,&vaos);
    vao = vaos;
    glBindVertexArray(vao);
}

void VAO::unbidVAO(){
    glBindVertexArray(0);
}


void VAO::VAOatribs(int location,int quantPos,int stride,int offset){
        glVertexAttribPointer(location, quantPos, GL_FLOAT, GL_FALSE, stride, (void*)(offset * sizeof(float)));
        glEnableVertexAttribArray(location); 
}

