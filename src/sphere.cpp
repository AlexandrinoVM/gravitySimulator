#include "../headers/sphere.hpp"




void sphere::setup(){
    int iterator =0;
    for(const auto &sp :spheres){
    float stackStep = pi / sp.second.stacks;
    float sectStep = pi * 2 / sp.second.sectors;
    float sectorAngle,stackAngle;
    for(int i =0;i<=sp.second.stacks;++i){
        stackAngle = i * stackStep;
        for(int j = 0;j<=sp.second.sectors;++j){
            glm::vec3 point;
            sectorAngle = j *sectStep;
            point.x = r * cos(sectorAngle) * sin(stackAngle);
            point.y = r *cos(stackAngle);
            point.z = r * sin(sectorAngle) * sin(stackAngle);
            vertices.push_back(point);
        }

    }

    for(int k =0;k<=sp.second.stacks -1;k++){
        for(int j =0;j<=sp.second.sectors -1;j++){
            int k1 = k * (sector+1) + j;
            int k2 = (k+1) * (sector+1) + j;
            indices.push_back(k1);
            indices.push_back(k2);
            indices.push_back(k1+1);


            indices.push_back(k1+1);
            indices.push_back(k2);
            indices.push_back(k2+1);
        }

    }
     
        buffes.emplace(iterator, bufferMeshi(vertices, indices));
        indicessize[iterator] = indices.size();
        indices.clear();
        vertices.clear();
        iterator++;
    //vao = new VAO();
    //vao->bindVAO();
    //vbo = new VBO(vertices);
    //vao->VAOatribs(0,3,3*sizeof(glm::vec3),0);
    //ebo = new EBO();
    //ebo->setData(indices);
    //vao->unbidVAO();
    }
}   
void sphere::Draw(shader &s,glm::mat4 view,glm::mat4 projection){ 
    //vao->bindVAO();
    int iterator =0;
    for(const auto &sp:spheres){
    buffes[iterator].vao.bindVAO();
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, sp.second.positions);


        glUniformMatrix4fv(glGetUniformLocation(s.getID(),"model"),1,GL_FALSE,glm::value_ptr(model));
        glUniformMatrix4fv(glGetUniformLocation(s.getID(),"projection"),1,GL_FALSE,glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(s.getID(),"view"),1,GL_FALSE,glm::value_ptr(view));
        glDrawElements(GL_LINES,indicessize[iterator],GL_UNSIGNED_INT,0);
        glBindVertexArray(0);
        iterator++;
    }
}



void sphere::close(){
    delete(vao);
    delete(ebo);
    delete(vbo);
}


