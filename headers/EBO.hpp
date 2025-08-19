#ifndef EBO_HPP
#define EBO_HPP
#include <GL/glew.h>
#include <vector>


class EBO{
    public:
    EBO();
    EBO(unsigned int &ebo);
    EBO(unsigned  *indices,int count);
    void setData(std::vector<unsigned int>indices);
    void bindEBO();
    void bindEBO(unsigned int ebo);
    void unbidEBO();
    void destroyEBO();
    unsigned int getEBO(){return ebo;};
    void EBOatribs(int location,int quantPos,int stride,int offset);
    private:
    unsigned int ebo;
};


#endif
