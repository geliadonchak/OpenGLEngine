#pragma once

#ifndef OPENGLENGINE_MAIN_CPP
#define OPENGLENGINE_MAIN_CPP

#include <iostream>
#include <GL/glew.h>
#include <SFML/Window.hpp>

#include "../external/stb/stb_image.h"
#include "utils/ShaderLoader.hpp"
#include "Camera.hpp"
#include "utils/Shader.hpp"
#include "Texture.hpp"
#include "Material.hpp"
#include "LightSource.hpp"
#include "utils/LightningShaderFiller.hpp"

int main() {
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.majorVersion = 4;
    settings.minorVersion = 3;
    settings.attributeFlags = sf::ContextSettings::Core;

    sf::Window window(sf::VideoMode(1200, 900, 32), "First Window",
                      sf::Style::Titlebar | sf::Style::Close, settings);

    glewExperimental = GL_TRUE;

    if (GLEW_OK != glewInit()) {
        std::cout << "Error:: glew not init =(" << std::endl;
        return -1;
    }

    Vector light_pos{0.57f, 0.57f, 0.57f};

    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);
    glDepthRange(0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    std::string s1 = "../resources/shaders/directional_lighting.vs";
    std::string s2 = "../resources/shaders/directional_lighting.fs";
//    std::string s1 = "../resources/shaders/point_lighting.vs";
//    std::string s2 = "../resources/shaders/point_lighting.fs";
//    std::string s1 = "../resources/shaders/spot_lighting.vs";
//    std::string s2 = "../resources/shaders/spot_lighting.fs";
    std::string s3 = "../resources/shaders/light_cube.vs";
    std::string s4 = "../resources/shaders/light_cube.fs";

    Shader lighting_shader(s1, s2);
    Shader light_cube_shader(s3, s4);

    Camera camera;

    float vertices[] = {
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
            0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

            -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

            0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,

            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
            0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
    };

    Vector cube_positions[] = {
            Vector{0.0f, 0.0f, 0.0f},
            Vector{2.0f, 5.0f, -15.0f},
            Vector{-1.5f, -2.2f, -2.5f},
            Vector{-3.8f, -2.0f, -12.3f},
            Vector{2.4f, -0.4f, -3.5f},
            Vector{-1.7f, 3.0f, -7.5f},
            Vector{1.3f, -2.0f, -2.5f},
            Vector{1.5f, 2.0f, -2.5f},
            Vector{1.5f, 0.2f, -1.5f},
            Vector{-1.3f, 1.0f, -1.5f}
    };

    unsigned int VBO, cube_VAO;
    glGenVertexArrays(1, &cube_VAO);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindVertexArray(cube_VAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    unsigned int light_cube_VAO;
    glGenVertexArrays(1, &light_cube_VAO);
    glBindVertexArray(light_cube_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) nullptr);
    glEnableVertexAttribArray(0);

    Texture("../resources/images/sad_cat.jpg").bind();


    lighting_shader.use();
    Material material(0, 1, 32.0f);
    lighting_shader.set_int("material.diffuse", material.get_diffuse());
    lighting_shader.set_int("material.specular", material.get_specular());
    lighting_shader.set_float("material.shininess", material.get_shininess());

    bool is_go = true;
    while (is_go) {
        sf::Event window_event{};
        while (window.pollEvent(window_event)) {
            switch (window_event.type) {
                case sf::Event::Closed:
                    is_go = false;
                    break;
                case sf::Event::KeyPressed:
                    camera.keyboard_input();
                    break;
                case sf::Event::MouseMoved:
                    camera.mouse_input(window, (float) window_event.mouseMove.x, (float) window_event.mouseMove.y);
                    break;
                default:
                    break;
            }
        }

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        lighting_shader.use();

        LightSource dir_light(LightSource::DIRECTIONAL);
        dir_light.get_light_source()
                ->set_direction({-0.2f, -1.0f, -0.3f})
                ->set_ambient({0.2f, 0.2f, 0.2f})
                ->set_diffuse({0.5f, 0.5f, 0.5f})
                ->set_specular({1.0f, 1.0f, 1.0f});
        LightningShaderFiller::fill_light_shader(lighting_shader, dir_light);

//        LightSource point_light(LightSource::POINT);
//        point_light.get_light_source()
//            ->set_position(light_pos)
//            ->set_ambient({0.2f, 0.2f, 0.2f})
//            ->set_diffuse({1.0f, 1.0f, 1.0f})
//            ->set_specular({1.0f, 1.0f, 1.0f})
//            ->set_constant(1.0f)
//            ->set_linear(0.09f)
//            ->set_quadratic(0.032f);
//        LightningShaderFiller::fill_light_shader(lighting_shader, point_light);

//        LightSource spot_light(LightSource::SPOT);
//        spot_light.get_light_source()
//            ->set_position(light_pos)
//            ->set_direction(camera.get_camera_front())
//            ->set_cut_off(glm::cos(glm::radians(15.0f)))
//            ->set_outer_cut_off(glm::cos(glm::radians(23.0f)))
//            ->set_ambient({0.1f, 0.1f, 0.1f})
//            ->set_diffuse({0.8f, 0.8f, 0.8f})
//            ->set_specular({1.0f, 1.0f, 1.0f})
//            ->set_constant(1.0f)
//            ->set_linear(0.09f)
//            ->set_quadratic(0.032f);
//        LightningShaderFiller::fill_light_shader(lighting_shader, spot_light);

        Matrix model = Matrix::identity_matrix(4);
        Matrix view(camera.get_view_matrix());
        Matrix projection(camera.get_projection_matrix());

        lighting_shader.set_mat4("projection", projection);
        lighting_shader.set_mat4("view", view);
        lighting_shader.set_mat4("model", model);

        glBindVertexArray(cube_VAO);
        for (unsigned int i = 0; i < 10; i++) {
            model = Matrix::transform(cube_positions[i]).transposed();
            float angle = 20.0f * (float) i;

            model *= Matrix::rotate(glm::radians(angle), glm::radians(angle * i), glm::radians(angle - 10 + 2 * i));

            lighting_shader.set_mat4("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        //
//        glBindVertexArray(cube_VAO);
//        glDrawArrays(GL_TRIANGLES, 0, 36);
//
//        light_cube_shader.use();
//        light_cube_shader.set_mat4("projection", projection);
//        light_cube_shader.set_mat4("view", view);
//        model = Matrix::transform(light_pos).transposed();
//
//        for (int i = 0; i < 3; ++i) {
//            model[i][i] = 0.2f;
//        }
//        model[3][3] = 1;
//        light_cube_shader.set_mat4("model", model);
//
//        glBindVertexArray(light_cube_VAO);
//        glDrawArrays(GL_TRIANGLES, 0, 36);

        window.display();
    }

    glDeleteVertexArrays(1, &cube_VAO);
    glDeleteVertexArrays(1, &light_cube_VAO);
    glDeleteBuffers(1, &VBO);

    window.close();
    return 0;
}

#endif // OPENGLENGINE_MAIN_CPP