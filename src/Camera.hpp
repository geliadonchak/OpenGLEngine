#pragma once

#ifndef OPENGLENGINE_CAMERA_HPP
#define OPENGLENGINE_CAMERA_HPP

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

    Matrix get_view_matrix_without_translation() {
        Matrix result = Matrix::look_at(camera_position, camera_position + camera_front, camera_up);
        result[3][0] = 0;
        result[3][1] = 0;
        result[3][2] = 0;
        result[3][3] = 1;

        return result;
    }

    Matrix get_projection_matrix() {
        return Matrix::perspective(45.0f, 800.0f / 600.0f, 0.1f, 100.0f);
    }

    void keyboard_input(sf::Keyboard::Key key) {
        Vector crossResult(Vector::cross_product(camera_front, camera_up));
        switch (key) {
            case sf::Keyboard::S:
            case sf::Keyboard::W:
                camera_position += camera_front * speed * (key == sf::Keyboard::S ? -1.f : 1.f);
                break;
            case sf::Keyboard::A:
            case sf::Keyboard::D:
                camera_position += crossResult.normalize() * speed * (key == sf::Keyboard::A ? -1.f : 1.f);
                break;
            default:
                break;
        }
    }

    void mouse_input(float x_pos, float y_pos) {
        if (firstMouse) {
            last_x = x_pos;
            last_y = y_pos;
            firstMouse = false;
        }

        float x_offset = x_pos - last_x;
        float y_offset = last_y - y_pos;
        last_x = x_pos;
        last_y = y_pos;

        x_offset *= speed;
        y_offset *= speed;

        yaw += x_offset;
        pitch += y_offset;

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

    const Vector &get_camera_position() const {
        return camera_position;
    }

    const Vector &get_camera_front() const {
        return camera_front;
    }

    const Vector &get_camera_up() const {
        return camera_up;
    }

 private:
    Vector camera_position;
    Vector camera_front;
    Vector camera_up;

    float speed = 0.2;

    float yaw = -90.0;
    float pitch = 0.0;
    bool firstMouse = true;

    float last_x;
    float last_y;
};

#endif  // OPENGLENGINE_CAMERA_HPP
