#pragma once

#include <SFML/Window.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Matrix.hpp"

class Camera {
public:
    Camera() : camera_position(3), camera_front(3), camera_up(3) {
        camera_position = Vector{0.0, 0.0, 3.0};
        camera_front = Vector{0.0, 0.0, -1.0};
        camera_up = Vector{0.0, 1.0, 0.0};
    }

    Matrix get_view_matrix() {
        return Matrix::look_at(camera_position, camera_position + camera_front, camera_up);
    }

    Matrix get_projection_matrix() {
        return Matrix::perspective(45.0f, 800.0f / 600.0f, 0.1f, 100.0f);
    }

    void keyboard_input() {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            camera_position += camera_front * speed;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            Vector crossResult(Vector::cross_product(camera_front, camera_up));
            camera_position -= crossResult.normalize() * speed;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            Vector crossResult(Vector::cross_product(camera_front, camera_up));
            camera_position += crossResult.normalize() * speed;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            camera_position -= camera_front * speed;
        }
    }

    void mouse_input(sf::Window& window, float x_pos, float y_pos) {
        if (firstMouse) {
            lastX = x_pos;
            lastY = y_pos;
            firstMouse = false;
        }

        float x_offset = x_pos - lastX;
        float y_offset = lastY - y_pos;
        lastX = x_pos;
        lastY = y_pos;

        x_offset *= speed;
        y_offset *= speed;

        yaw += x_offset;
        pitch += y_offset;

        // make sure that when pitch is out of bounds, screen doesn't get flipped
        if (pitch > 89.0f) {
            pitch = 89.0f;
        }

        if (pitch < -89.0f) {
            pitch = -89.0f;
        }

        Vector front(3);
        front[0] = static_cast<float>(cos(glm::radians(yaw)) * cos(glm::radians(pitch)));
        front[1] = static_cast<float>(sin(glm::radians(pitch)));
        front[2] = static_cast<float>(sin(glm::radians(yaw)) * cos(glm::radians(pitch)));
        camera_front = front.normalize();
    }

private:
    Vector camera_position;
    Vector camera_front;
    Vector camera_up;

    float speed = 0.2;

    float yaw = -90.0;
    float pitch = 0.0;
    bool firstMouse = true;

    float lastX;
    float lastY;
};

