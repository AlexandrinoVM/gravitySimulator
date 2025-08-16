#ifndef CAMERA_HPP
#define CAMERA_HPP
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/gtc/type_ptr.hpp"
#include "../glm/gtc/matrix_transform.hpp"

enum class CameraMove { Forward, Backward, Left, Right, Up, Down };

class Camera{
public:
    // --- Construtores ---
    Camera(
        const glm::vec3& position = {0.0f, 0.0f, 3.0f},
        const glm::vec3& worldUp  = {0.0f, 1.0f, 0.0f},
        float yawDeg   = -90.0f,
        float pitchDeg =   0.0f,
        float fovDeg   =  60.0f,
        float aspect   =  16.0f/9.0f,
        float nearZ    =   0.1f,
        float farZ     = 1000.0f
    );

    // --- Getters principais ---
    glm::mat4 getViewMatrix() const;
    glm::mat4 getProjectionMatrix() const;
    glm::mat4 getViewProjectionMatrix() const;

    // --- Controles de input ---
    // dt: delta time em segundos; speed: unidades/seg
    void processKeyboard(CameraMove dir, float dt, float speed = 3.0f);
    // dx, dy: deslocamento do mouse em pixels (ou unidades brutas)
    void processMouse(float dx, float dy, bool constrainPitch = true, float sensitivity = 0.1f);
    // yoffset: rolagem do scroll (positivo aproxima)
    void processScroll(float yoffset);

    // --- Utilidades/Config ---
    void setAspect(float aspect);
    void setPerspective(float fovDeg, float aspect, float nearZ, float farZ);
    void lookAt(const glm::vec3& target); // redefine yaw/pitch olhando para 'target'

    // --- Acesso ao estado ---
    const glm::vec3& getPosition() const { return m_position; }
    const glm::vec3& getFront()    const { return m_front; }
    const glm::vec3& getUp()       const { return m_up; }
    const glm::vec3& getRight()    const { return m_right; }
    float getYaw()   const { return m_yaw; }
    float getPitch() const { return m_pitch; }
    float getFov()   const { return m_fovDeg; }

    void setPosition(const glm::vec3& p) { m_position = p; }
    void setYawPitch(float yawDeg, float pitchDeg, bool constrainPitch = true);

private:
    // Estado básico
    glm::vec3 m_position;
    glm::vec3 m_worldUp;

    // Orientação (em graus)
    float m_yaw;   // esquerda/direita
    float m_pitch; // cima/baixo

    // Vetores derivados
    glm::vec3 m_front;
    glm::vec3 m_right;
    glm::vec3 m_up;

    // Projeção
    float m_fovDeg;
    float m_aspect;
    float m_nearZ;
    float m_farZ;

    void updateVectors(); // recalcula front/right/up a partir de yaw/pitch};
};

#endif
