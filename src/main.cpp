#ifndef OPENGLENGINE_MAIN_CPP
#define OPENGLENGINE_MAIN_CPP

#include <iostream>
#include <GL/glew.h>
#include <SFML/Window.hpp>
#include "../external/stb/stb_image.h"
#include "utils/ShaderLoader.hpp"
#include "Camera.hpp"
#include "utils/Shader.hpp"

#include "VertexArrayObject.hpp"
#include "VertexBufferObject.hpp"
#include "Mesh.hpp"
#include "Model.hpp"

unsigned int load_skybox(std::vector<std::string> faces) {
    unsigned int texture_ID;
    glGenTextures(1, &texture_ID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture_ID);

    int width, height, nr_channels;
    for (unsigned int i = 0; i < faces.size(); i++) {
        unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nr_channels, 0);
        if (data) {
            GLuint type = GL_RGB;
            if (nr_channels == 4) {
                type = GL_RGBA;
            }

            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, type, width, height, 0, type, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
            stbi_image_free(data);
        } else {
            std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return texture_ID;
}

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

    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);
    glDepthRange(0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    Camera camera;

    float skybox_vertices[] = {
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
        1.0f,  1.0f, -1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
        1.0f, -1.0f,  1.0f
    };

    VertexArrayObject skybox_VAO;
    VertexBufferObject skybox_VBO(skybox_vertices, sizeof(skybox_vertices));
    VertexArrayObject::link_vertex_attr(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)nullptr);
    skybox_VBO.bind_buffer();

    std::vector<std::string> faces1 {
            "../resources/skybox/right.jpg",
            "../resources/skybox/left.jpg",
            "../resources/skybox/top.jpg",
            "../resources/skybox/bottom.jpg",
            "../resources/skybox/front.jpg",
            "../resources/skybox/back.jpg"
    };
    std::vector<std::string> faces2 {
            "../resources/skybox/right2.png",
            "../resources/skybox/left2.png",
            "../resources/skybox/top2.png",
            "../resources/skybox/bottom2.png",
            "../resources/skybox/front2.png",
            "../resources/skybox/back2.png"
    };
    unsigned int skybox_texture1 = load_skybox(faces1);
    unsigned int skybox_texture2 = load_skybox(faces2);

    Shader model_shader("../resources/shaders/model.vs", "../resources/shaders/model.fs");
    model_shader.use();
    stbi_set_flip_vertically_on_load(true);
    Model model_obj_backpack("/home/gelia/Workspace/opengl/resources/models/backpack/backpack.obj");
    Model model_obj_mars("/home/gelia/Workspace/opengl/resources/models/planet/planet.obj");
    Model model_obj_cyborg("/home/gelia/Workspace/opengl/resources/models/cyborg/cyborg.obj");

    Shader skybox_shader("../resources/shaders/skybox.vs", "../resources/shaders/skybox.fs");
    skybox_shader.use();
    skybox_shader.set_int("skybox1", 0);
    skybox_shader.set_int("skybox2", 1);
    skybox_shader.set_float("blend", 0.0);

    bool is_go = true;
    float blend = -1.0f;
    float speed = 0.0005f;
    float direction = 1.0f;

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

        model_shader.use();
        Matrix projection(camera.get_projection_matrix());
        Matrix view(camera.get_view_matrix());
        model_shader.set_mat4("projection", projection);
        model_shader.set_mat4("view", view);

        Matrix model_backpack = Matrix::transform(Vector{0.0f, 0.0f, 0.0f}) * Matrix::scale(Vector{0.6f, 0.6f, 0.6f});
        model_shader.set_mat4("model", model_backpack);
        model_obj_backpack.draw(model_shader);

        Matrix model_mars = Matrix::transform(Vector{5.0f, 3.0f, 5.0f}) * Matrix::scale(Vector{0.9f, 0.9f, 0.9f});
        model_shader.set_mat4("model", model_mars);
        model_obj_mars.draw(model_shader);

        Matrix model_cyborg = Matrix::transform(Vector{-5.0f, -3.0f, 0.0f}) * Matrix::scale(Vector{0.9f, 0.9f, 0.9f});
        model_shader.set_mat4("model", model_cyborg);
        model_obj_cyborg.draw(model_shader);

        glDepthFunc(GL_LEQUAL);

        skybox_shader.use();

        if (0 < blend && blend < 1) {
            skybox_shader.set_float("blend", blend);
        }

        blend += direction * speed;
        if (abs(blend + 1) < 10e-5 || abs(blend - 2) < 10e-5) {
            direction = -direction;
        }

        Matrix view_skybox = camera.get_view_matrix_without_translation();
        skybox_shader.set_mat4("view", view_skybox);
        skybox_shader.set_mat4("projection", projection);

        skybox_VAO.bind_array();

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, skybox_texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_CUBE_MAP, skybox_texture2);

        glDrawArrays(GL_TRIANGLES, 0, 36);
        glDepthFunc(GL_LESS);

        window.display();
    }

    skybox_VAO.delete_array();
    skybox_VBO.delete_buffer();

    window.close();
    return 0;
}

#endif  // OPENGLENGINE_MAIN_CPP
