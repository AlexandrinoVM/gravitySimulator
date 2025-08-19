#ifndef VAO_HPP
#define VAO_HPP
#include <GL/glew.h>
class VAO{
public:
    VAO();
    VAO(unsigned int &vao);
    void bindVAO();
    void unbidVAO();
    unsigned int getVAO(){return vao;};
    void VAOatribs(int location,int quantPos,int stride,int offset);
    void VAOatribs(int location,int quantPos,int stride,int offset,int type);
    
private:
    unsigned int vao;
};
#endif
