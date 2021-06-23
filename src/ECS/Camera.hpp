#pragma once

#ifndef OPENGLENGINE_ECS_CAMERA_HPP
#define OPENGLENGINE_ECS_CAMERA_HPP

#include <limits>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Math/Matrix.hpp"

namespace ECS {

class Camera {
  public:
    Camera() : cameraPosition(3), cameraFront(3), cameraUp(3) {
        cameraPosition = Vector{0.0, 0.0, 3.0};
        cameraFront = Vector{0.0, 0.0, -1.0};
        cameraUp = Vector{0.0, 1.0, 0.0};
    }

    Matrix getViewMatrix() {
        return Matrix::look_at(cameraPosition, cameraPosition + cameraFront, cameraUp);
    }

    Matrix getViewMatrixWithoutTranslation() {
        Matrix result = Matrix::look_at(cameraPosition, cameraPosition + cameraFront, cameraUp);
        result[3][0] = 0;
        result[3][1] = 0;
        result[3][2] = 0;
        result[3][3] = 1;

        return result;
    }

    Matrix getProjectionMatrix() {
        return Matrix::perspective(45.0f, 800.0f / 600.0f, 0.1f, 100.0f);
    }

    void onKeyboardInput(sf::Keyboard::Key key) {
        Vector crossResult(Vector::cross_product(cameraFront, cameraUp));
        switch (key) {
            case sf::Keyboard::S:
            case sf::Keyboard::W:cameraPosition += cameraFront * speed * (key == sf::Keyboard::S ? -1.f : 1.f);
                break;
            case sf::Keyboard::A:
            case sf::Keyboard::D:
                cameraPosition += crossResult.normalize() * speed * (key == sf::Keyboard::A ? -1.f : 1.f);
                break;
            case sf::Keyboard::Q:
            case sf::Keyboard::E:rotate(key == sf::Keyboard::Q ? -1 : 1);
                break;
            default:break;
        }
    }

    void onMouseInput(float xPos, float yPos) {
        if (std::numeric_limits<float>::infinity() == lastX) {
            lastX = xPos;
            lastY = yPos;
        }

        float xOffset = xPos - lastX;
        float yOffset = lastY - yPos;
        lastX = xPos;
        lastY = yPos;

        xOffset *= speed;
        yOffset *= speed;

        yaw += xOffset;
        pitch += yOffset;

        if (pitch > 89.0f) {
            pitch = 89.0f;
        }

        if (pitch < -89.0f) {
            pitch = -89.0f;
        }

        Vector front(3);
        front[0] = static_cast<float>(cos(glm::radians(yawCorrection + yaw)) * cos(glm::radians(pitch)));
        front[1] = static_cast<float>(sin(glm::radians(pitch)));
        front[2] = static_cast<float>(sin(glm::radians(yawCorrection + yaw)) * cos(glm::radians(pitch)));
        cameraFront = front.normalize();
    }

    void rotate(int direction) {
        yawCorrection += (float) direction * rotationSpeed;

        Vector front(3);
        front[0] = static_cast<float>(cos(glm::radians(yawCorrection + yaw)) * cos(glm::radians(pitch)));
        front[1] = static_cast<float>(sin(glm::radians(pitch)));
        front[2] = static_cast<float>(sin(glm::radians(yawCorrection + yaw)) * cos(glm::radians(pitch)));
        cameraFront = front.normalize();
    }

    const Vector &getCameraPosition() const {
        return cameraPosition;
    }
    const Vector &getCameraFront() const {
        return cameraFront;
    }
    const Vector &getCameraUp() const {
        return cameraUp;
    }

  private:
    Vector cameraPosition{};
    Vector cameraFront{};
    Vector cameraUp{};

    float speed = 0.2;

    float rotationSpeed = 1.0;
    float yawCorrection = 0.0;

    float yaw = -90.0;
    float pitch = 0.0;

    float lastX = std::numeric_limits<float>::infinity();
    float lastY = std::numeric_limits<float>::infinity();
};

}

#endif  // OPENGLENGINE_ECS_CAMERA_HPP
