#include "../headers/terrarian.hpp"

terrarian::terrarian(){
 SetupData();
}

void terrarian::SetupData(){
    float init = -100.0f;
    float end = 100.0f;
    float collSize = 10.0f;
    unsigned int indice = 0;
    //z axis 380  360
    //       400  400  
    for(int i =init;i<=end; i+=collSize){
        vertices.push_back(init);
        vertices.push_back(0.0f);
        vertices.push_back(i);

        vertices.push_back(end);
        vertices.push_back(0.0f);
        vertices.push_back(i);

        indices.push_back(indice);
        indices.push_back(indice+1);
        indice+=2;
    }
    //x axis
    for(int j =init;j<=end; j+=collSize){
        vertices.push_back(j);
        vertices.push_back(0);
        vertices.push_back(init);

        vertices.push_back(j);
        vertices.push_back(0);
        vertices.push_back(end);

        indices.push_back(indice);
        indices.push_back(indice+1);
        indice+=2;
    }
    std::cout << "Vertices count: " << vertices.size()/3 << "\n";
    std::cout << "Indices count: " << indices.size() << "\n";


    vao = new VAO();
    vao->bindVAO();
    vbo = new VBO(vertices);
    vao->VAOatribs(0,3,3*sizeof(float),0);
    ebo = new EBO();
    ebo->setData(indices);
    vao->unbidVAO();
    vbo->unbind();
}

void terrarian::Draw(shader &s,glm::mat4 view,glm::mat4 projection){ 
    vao->bindVAO();
    glUniformMatrix4fv(glGetUniformLocation(s.getID(),"projection"),1,GL_FALSE,glm::value_ptr(projection));
    glUniformMatrix4fv(glGetUniformLocation(s.getID(),"view"),1,GL_FALSE,glm::value_ptr(view));
    glDrawElements(GL_LINES,indices.size(),GL_UNSIGNED_INT,0);
    glBindVertexArray(0);
}
