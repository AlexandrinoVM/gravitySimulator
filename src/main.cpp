#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <iostream>
#include "../headers/VBO.hpp"
#include "../headers/SHADER.hpp"
#include "../headers/VAO.hpp"
#include <filesystem>
#include "../headers/CAMERA.hpp"
#include "../glm/glm.hpp"
#include "../glm/gtc/type_ptr.hpp"
#include "../headers/terrarian.hpp"
#include "../headers/sphere.hpp"

float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
};


int main() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Erro ao inicializar SDL: " << SDL_GetError() << "\n";
        return 1;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_Window* window = SDL_CreateWindow("SDL + OpenGL",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          800, 600,
                                          SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

    if (!window) {
        std::cerr << "Erro ao criar janela: " << SDL_GetError() << "\n";
        SDL_Quit();
        return 1;
    }

    SDL_GLContext context = SDL_GL_CreateContext(window);
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "error initing GLEW\n";
        return 1;
    }
    Camera camera({0.0f, 0.0f, 3.0f}); 


    shader shad;
    shader spshad;
    shad.Loadshader("./shaders/s.vert","./shaders/s.frag");
    spshad.Loadshader("./shaders/spheres/sp.vert","./shaders/spheres/sp.frag");
    
    sphere sp;
    sp.Createsphere(10,36,18,{0.0f,10.0f,-1.0f});
    sp.Createsphere(5,16,8,{20.0f,10.0f,-1.0f});
    float lastTime = SDL_GetTicks() / 1000.0f;

    terrarian terr;
    terr.getSpData(sp.getData());

    bool running = true;
    SDL_Event event;
    while (running) {

        float currentTime = SDL_GetTicks() / 1000.0f;
        float deltaTime = currentTime - lastTime;
        lastTime = currentTime;
        
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = false;
        }
        if (event.type == SDL_MOUSEMOTION) {
            camera.processMouse(event.motion.xrel, -event.motion.yrel);
        }
        if (event.type == SDL_MOUSEWHEEL) {
            camera.processScroll(event.wheel.y);
        }
        if (event.type == SDL_WINDOWEVENT &&
            event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
            camera.setAspect((float)event.window.data1 / event.window.data2);
            glViewport(0, 0, event.window.data1, event.window.data2);
        }

        const Uint8* state = SDL_GetKeyboardState(NULL);
        if (state[SDL_SCANCODE_W]) camera.processKeyboard(CameraMove::Forward, deltaTime);
        if (state[SDL_SCANCODE_S]) camera.processKeyboard(CameraMove::Backward, deltaTime);
        if (state[SDL_SCANCODE_A]) camera.processKeyboard(CameraMove::Left, deltaTime);
        if (state[SDL_SCANCODE_D]) camera.processKeyboard(CameraMove::Right, deltaTime);
        if (state[SDL_SCANCODE_SPACE]) camera.processKeyboard(CameraMove::Up, deltaTime);
        if (state[SDL_SCANCODE_LCTRL]) camera.processKeyboard(CameraMove::Down, deltaTime);


        glm::mat4 view = camera.getViewMatrix();
        glm::mat4 projection = camera.getProjectionMatrix(); 
        //glUniformMatrix4fv(glGetUniformLocation(shad.getID(),"projection"),1,GL_FALSE,glm::value_ptr(projection));
        //glUniformMatrix4fv(glGetUniformLocation(shad.getID(),"view"),1,GL_FALSE,glm::value_ptr(view));
        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shad.useProgram();
        terr.Draw(shad,view,projection);
        shad.stop();
        spshad.useProgram();
        sp.Draw(spshad,view,projection);
        //vao.bindVAO();
        //glDrawArrays(GL_TRIANGLES,0,3);
        spshad.stop();
        SDL_GL_SwapWindow(window);
    }
    sp.close();
    terr.close();
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}


