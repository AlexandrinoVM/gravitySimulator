#ifndef SHADER_HPP
#define SHADER_HPP

#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <map>
#include <string.h>
#include <sstream>
#include "../glm/glm.hpp"
#include "../glm/gtc/type_ptr.hpp"
class shader{
public:
    void Loadshader(const std::string &vert,const std::string &frag);
    void useProgram(){glUseProgram(ID);};
    int getID(){return ID;};
    void stop();
    void setMat4(glm::mat4 &value,const std::string &name,int program);
   // void setBool(const std::string &nameProgram,const std::string &name,bool value);
    //void setFloat(const std::string &nameProgram,const std::string &name,float value);
    //void setint(const std::string &nameProgram,const std::string &name,int value);
    //void setMat4(const std::string &nameProgram,const std::string &name, glm::mat4 data);
    //void setVec3(const std::string &nameProgram,const std::string &name, glm::vec3 data);
    //void setVec4(const std::string &nameProgram,const std::string &name, glm::vec4 data);
private:
    std::string loadSource(const std::string &VertexPath);
    void crateProgram(const unsigned int vert,const unsigned int frag);
    unsigned int shader;
    int ID;
};


#endif

