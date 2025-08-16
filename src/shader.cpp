#include "../headers/SHADER.hpp"
std::string shader::loadSource(const std::string &pathShader){
        std::string shaderCode;
        std::ifstream shdaderFile;

        shdaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        try{
            shdaderFile.open(pathShader);
            std::stringstream shaderStream;

            shaderStream << shdaderFile.rdbuf();

            shdaderFile.close();

            shaderCode = shaderStream.str();
            return shaderCode;

        }catch(std::ifstream::failure e){
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << '\n';
            return "";
        }
}

void shader::setMat4(glm::mat4 &value,const std::string &name,int program){
    glUniformMatrix4fv(glGetUniformLocation(program,name.c_str()),1,GL_FALSE,glm::value_ptr(value));
}

void shader::Loadshader(const std::string &vertfrag,const std::string &fragment){
    
    std::string vert = loadSource(vertfrag);
    std::string frag = loadSource(fragment);
    
    int sucess;
    char infolog[512];


    if (vert.empty() || frag.empty()) {
    std::cerr << "Shader source is empty!" << '\n';
    return;
    }
    const char *vertexShaderSource = vert.c_str();
    const char * fragmentShaderSource = frag.c_str();



    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader,1,&vertexShaderSource,NULL);
    glCompileShader(vertexShader);

    glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&sucess);
    if(!sucess){
        glGetShaderInfoLog(vertexShader,512,NULL,infolog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infolog << std::ends;
    }


    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader,GL_COMPILE_STATUS,&sucess);
    if(!sucess){
        glGetShaderInfoLog(fragmentShader,512,NULL,infolog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infolog << std::ends;
    }


    crateProgram(vertexShader,fragmentShader);
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);  
}

  
void shader::crateProgram(const unsigned int vert,const unsigned int frag){
    int sucess;
    char infolog[512];
    ID = glCreateProgram();

    glAttachShader(ID,vert);
    glAttachShader(ID,frag);
    glLinkProgram(ID);

    glGetShaderiv(ID,GL_LINK_STATUS,&sucess);
    if(!sucess){
        glGetShaderInfoLog(ID,512,NULL,infolog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infolog << '\n';
    }
}

