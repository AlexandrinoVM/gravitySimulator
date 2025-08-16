#include "../headers/CAMERA.hpp"
#include <algorithm>
#include <cmath>

static inline float radians(float deg) { return glm::radians(deg); }

Camera::Camera(const glm::vec3& position,
               const glm::vec3& worldUp,
               float yawDeg,
               float pitchDeg,
               float fovDeg,
               float aspect,
               float nearZ,
               float farZ)
: m_position(position),
  m_worldUp(worldUp),
  m_yaw(yawDeg),
  m_pitch(pitchDeg),
  m_front(0.0f, 0.0f, -1.0f),
  m_right(1.0f, 0.0f, 0.0f),
  m_up(0.0f, 1.0f, 0.0f),
  m_fovDeg(fovDeg),
  m_aspect(aspect),
  m_nearZ(nearZ),
  m_farZ(farZ)
{
    updateVectors();
}

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(m_position, m_position + m_front, m_up);
}

glm::mat4 Camera::getProjectionMatrix() const {
    return glm::perspective(radians(m_fovDeg), m_aspect, m_nearZ, m_farZ);
}

glm::mat4 Camera::getViewProjectionMatrix() const {
    return getProjectionMatrix() * getViewMatrix();
}

void Camera::processKeyboard(CameraMove dir, float dt, float speed) {
    const float velocity = speed * dt;
    switch (dir) {
        case CameraMove::Forward:  m_position += m_front  * velocity; break;
        case CameraMove::Backward: m_position -= m_front  * velocity; break;
        case CameraMove::Left:     m_position -= m_right  * velocity; break;
        case CameraMove::Right:    m_position += m_right  * velocity; break;
        case CameraMove::Up:       m_position += m_up     * velocity; break;
        case CameraMove::Down:     m_position -= m_up     * velocity; break;
    }
}

void Camera::processMouse(float dx, float dy, bool constrainPitch, float sensitivity) {
    m_yaw   += dx * sensitivity;
    m_pitch += dy * sensitivity;

    if (constrainPitch) {
        m_pitch = std::clamp(m_pitch, -89.9f, 89.9f);
    }
    updateVectors();
}

void Camera::processScroll(float yoffset) {
    m_fovDeg -= yoffset;
    m_fovDeg = std::clamp(m_fovDeg, 1.0f, 90.0f);
}

void Camera::setAspect(float aspect) {
    m_aspect = std::max(0.0001f, aspect);
}

void Camera::setPerspective(float fovDeg, float aspect, float nearZ, float farZ) {
    m_fovDeg = fovDeg;
    m_aspect = aspect;
    m_nearZ  = nearZ;
    m_farZ   = farZ;
}

void Camera::lookAt(const glm::vec3& target) {
    glm::vec3 dir = glm::normalize(target - m_position);
    m_pitch = glm::degrees(asinf(dir.y));
    m_yaw   = glm::degrees(atan2f(dir.z, dir.x));
    m_yaw   = 90.0f - m_yaw; 
    updateVectors();
}

void Camera::setYawPitch(float yawDeg, float pitchDeg, bool constrain) {
    m_yaw = yawDeg;
    m_pitch = pitchDeg;
    if (constrain) m_pitch = std::clamp(m_pitch, -89.9f, 89.9f);
    updateVectors();
}

void Camera::updateVectors() {
    const float cy = cosf(radians(m_yaw));
    const float sy = sinf(radians(m_yaw));
    const float cp = cosf(radians(m_pitch));
    const float sp = sinf(radians(m_pitch));

    glm::vec3 front;
    front.x =  cy * cp;
    front.y =  sp;
    front.z =  sy * cp;
    m_front = glm::normalize(front);

    m_right = glm::normalize(glm::cross(m_front, m_worldUp));
    m_up    = glm::normalize(glm::cross(m_right, m_front));
}
