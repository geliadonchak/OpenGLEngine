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
#include "VertexArrayObject.hpp"
#include "VertexBufferObject.hpp"

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

    Vector light_pos{-0.8f, -0.8f, 0.6f};

    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);
    glDepthRange(0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    std::string s1 = "../resources/shaders/combined_light.vs";
    std::string s2 = "../resources/shaders/combined_light.fs";

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

    Vector cubes_positions[] = {
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

    Vector point_light_positions[] = {
            Vector{0.7f,  0.2f,  2.0f},
            Vector{2.3f, -3.3f, -4.0f},
            Vector{-4.0f,  2.0f, -12.0f},
            Vector{0.0f,  0.0f, -3.0f}
    };

    VertexArrayObject cube_VAO;
    VertexBufferObject VBO(vertices, sizeof(vertices));
    VertexArrayObject::link_vertex_attr(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) nullptr);
    VertexArrayObject::link_vertex_attr(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (3 * sizeof(float)));
    VertexArrayObject::link_vertex_attr(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (6 * sizeof(float)));

    VertexArrayObject light_cube_VAO;
    VertexArrayObject::link_vertex_attr(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) nullptr);
    VBO.bind_buffer();

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

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        lighting_shader.use();

        LightningShaderFiller::fill_default_values(lighting_shader, 4);

        LightSource dir_light(LightSource::DIRECTIONAL);
        dir_light.get_light_source()
                ->set_direction({-0.2f, -1.0f, -0.3f})
                ->set_ambient({0.05f, 0.05f, 0.05f})
                ->set_diffuse({0.5f, 0.5f, 0.5f})
                ->set_specular({0.5f, 0.5f, 0.5f});
        LightningShaderFiller::fill_light_shader(lighting_shader, dir_light);

        for (int i = 0; i < point_light_positions->size(); i++) {
            LightSource point_light(LightSource::POINT);
            point_light.get_light_source()
                ->set_point_index(i)
                ->set_position(point_light_positions[i])
                ->set_ambient({0.05f, 0.05f, 0.05f})
                ->set_diffuse({0.8f, 0.8f, 0.8f})
                ->set_specular({1.0f, 1.0f, 1.0f})
                ->set_constant(1.0f)
                ->set_linear(0.09f)
                ->set_quadratic(0.032f);
            LightningShaderFiller::fill_light_shader(lighting_shader, point_light);
        }

        LightSource spot_light(LightSource::SPOT);
        spot_light.get_light_source()
                ->set_position(camera.get_camera_position())
                ->set_direction(camera.get_camera_front())
                ->set_cut_off(glm::cos(glm::radians(15.0f)))
                ->set_outer_cut_off(glm::cos(glm::radians(23.0f)))
                ->set_ambient({0.0f, 0.0f, 0.0f})
                ->set_diffuse({2.0f, 2.0f, 2.0f})
                ->set_specular({1.0f, 1.0f, 1.0f})
                ->set_constant(1.0f)
                ->set_linear(0.09f)
                ->set_quadratic(0.032f);
        LightningShaderFiller::fill_light_shader(lighting_shader, spot_light);

        Matrix model = Matrix::identity_matrix(4);
        Matrix view(camera.get_view_matrix());
        Matrix projection(camera.get_projection_matrix());

        lighting_shader.set_mat4("projection", projection);
        lighting_shader.set_mat4("view", view);
        lighting_shader.set_mat4("model", model);

        cube_VAO.bind_array();
        for (unsigned int i = 0; i < 10; i++) {
            model = Matrix::transform(cubes_positions[i]).transposed();
            float angle = 20.0f * (float) i;

            model *= Matrix::rotate(glm::radians(angle), glm::radians(angle * (float) i),
                                    glm::radians(angle - (float) i));

            lighting_shader.set_mat4("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        light_cube_shader.use();
        light_cube_shader.set_mat4("projection", projection);
        light_cube_shader.set_mat4("view", view);

        for (const auto & point_light_position : point_light_positions) {
            model = Matrix::transform(point_light_position).transposed();

            model[3][3] = 1;
            for (int j = 0; j < 3; ++j) {
                model[j][j] = 0.2f;
            }

            light_cube_shader.set_mat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        window.display();
    }

    cube_VAO.delete_array();
    light_cube_VAO.delete_array();
    VBO.delete_buffer();

    window.close();
    return 0;
}

#endif  // OPENGLENGINE_MAIN_CPP
