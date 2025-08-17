#ifndef CAMERA_HPP
#define CAMERA_HPP
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/gtc/type_ptr.hpp"
#include "../glm/gtc/matrix_transform.hpp"

enum class CameraMove { Forward, Backward, Left, Right, Up, Down };

class Camera{
public:
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

    glm::mat4 getViewMatrix() const;
    glm::mat4 getProjectionMatrix() const;
    glm::mat4 getViewProjectionMatrix() const;

    void processKeyboard(CameraMove dir, float dt, float speed = 3.0f);
    void processMouse(float dx, float dy, bool constrainPitch = true, float sensitivity = 0.1f);
    void processScroll(float yoffset);

    void setAspect(float aspect);
    void setPerspective(float fovDeg, float aspect, float nearZ, float farZ);
    void lookAt(const glm::vec3& target); 

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
    glm::vec3 m_position;
    glm::vec3 m_worldUp;

    float m_yaw;  
    float m_pitch; 

    glm::vec3 m_front;
    glm::vec3 m_right;
    glm::vec3 m_up;

    float m_fovDeg;
    float m_aspect;
    float m_nearZ;
    float m_farZ;

    void updateVectors(); 
};

#endif
