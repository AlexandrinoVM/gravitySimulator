#include "../headers/terrarian.hpp"

//terrarian::terrarian(){
 //SetupData();
//}
void terrarian::SetupData(){
    float init = -100.0f;
    float end = 100.0f;
    float collSize = 2.0f;
    unsigned int indice = 0;
    //z axis 380  360
    //       400  400
    for(int x =init;x< end; x+=collSize){
        for(int z =init;z<end;z+=collSize){


            glm::vec3 v1(x, 0.0f, z);
            glm::vec3 v2(x+collSize, 0.0f, z);
            glm::vec3 v3(x+collSize, 0.0f, z+collSize);
            glm::vec3 v4(x, 0, z+collSize);

            vertices.push_back(v1);
            vertices.push_back(v2);
            vertices.push_back(v3);
            vertices.push_back(v4);

            indices.push_back(indice);
            indices.push_back(indice+1);
            indices.push_back(indice+2);
            indices.push_back(indice+2);
            indices.push_back(indice+3);
            indices.push_back(indice);
            indice+=4;


        }
    }
    for(const auto &map : datasp){
        for(auto &v : vertices){
            double dx = v.x - map.second.positions.x;
            double dz = v.z - map.second.positions.z;
            double dist = sqrt(dx*dx + dz*dz);

            if (dist <= map.second.raio) {
                v.y = -4.0f * (1.0f - dist / map.second.raio);
            }
            
        }

    }


    setuPbuffers();
}

void terrarian::update(std::map<int,sp::sphereData> &data){
    for(auto &map : datasp){
        for(auto &dt : data){
            if(map.second.positions != dt.second.currPos){
                for(auto &v : vertices){
                    double dx = v.x - map.second.positions.x;
                    double dz = v.z - map.second.positions.z;
                    double dist = sqrt(dx*dx + dz*dz);

                    if (dist <= map.second.raio) {
                        v.y = -4.0f * (1.0f - dist / map.second.raio);
                    }
                }
                map.second.positions = dt.second.currPos;
                setuPbuffers();
            }
        } 
    }
}
void terrarian::setupYGrid(){

}

void terrarian::setuPbuffers(){
    vao = new VAO();
    vao->bindVAO();
    vbo = new VBO(vertices);
    vao->VAOatribs(0,3,sizeof(glm::vec3),0);
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
