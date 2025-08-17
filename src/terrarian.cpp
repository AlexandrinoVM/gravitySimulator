#include "../headers/terrarian.hpp"

//terrarian::terrarian(){
 //SetupData();
//}
void terrarian::SetupData(){
    float init = -400.0f;
    float end = 400.0f;
    float collSize = 2.0f;
    float initCel = init;
    float endCel = initCel += collSize;
    unsigned int indice = 0;
    bool negativex= false;
    bool negativey =false;
    //z axis 380  360
    //       400  400
    for(int x =init;x< end; x+=collSize){
        for(int z =init;z<end;z+=collSize){
            float targetx;
            float targey;
            float ysize =0;
           double dx = x - datasp.positions.x;
            double dz = z - datasp.positions.z;
            double dist = sqrt(dx*dx + dz*dz);

            if (dist <= datasp.raio) {
                ysize = -5.0f;    
            }

          
std::cout << "datasp.positions: " << datasp.positions.x << ", " << datasp.positions.z << "\n";

            targetx = abs((x-collSize)- datasp.raio);
            targey = abs((z-collSize)- datasp.raio);

            vertices.push_back(x);vertices.push_back(ysize);vertices.push_back(z);
            vertices.push_back(x+collSize);vertices.push_back(ysize);vertices.push_back(z);
            vertices.push_back(x+collSize);vertices.push_back(ysize);vertices.push_back(z+collSize);
            vertices.push_back(x);vertices.push_back(ysize);vertices.push_back(z+collSize);



            indices.push_back(indice);
            indices.push_back(indice+1);
            indices.push_back(indice+2);
            indices.push_back(indice+2);
            indices.push_back(indice+3);
            indices.push_back(indice);
            indice+=4;

        }
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
