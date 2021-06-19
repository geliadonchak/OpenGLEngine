#ifndef OPENGLENGINE_MAIN_CPP
#define OPENGLENGINE_MAIN_CPP

#include <iostream>
//#include <GL/glew.h>
//#include <SFML/Window.hpp>
#include "../external/stb/stb_image.h"
#include "utils/ShaderLoader.hpp"
#include "Camera.hpp"
#include "utils/Shader.hpp"

#include "ECS/InputManager.hpp"
#include "ECS/WindowSettings.hpp"
#include "ECS/Window.hpp"

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
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
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

    std::vector<std::string> faces {
            "../resources/skybox/right.jpg",
            "../resources/skybox/left.jpg",
            "../resources/skybox/top.jpg",
            "../resources/skybox/bottom.jpg",
            "../resources/skybox/front.jpg",
            "../resources/skybox/back.jpg"
    };
    unsigned int skybox_texture = load_skybox(faces);

    std::string s5 = "../resources/shaders/model.vs";
    std::string s6 = "../resources/shaders/model.fs";
    Shader model_shader(s5, s6);
    model_shader.use();
    stbi_set_flip_vertically_on_load(true);
    Model model_obj_backpack("../resources/models/backpack/backpack.obj");
    Model model_obj_mars("../resources/models/planet/planet.obj");
    Model model_obj_cyborg("../resources/models/cyborg/cyborg.obj");

    std::string s7 = "../resources/shaders/skybox.vs";
    std::string s8 = "../resources/shaders/skybox.fs";
    Shader skybox_shader(s7, s8);
    skybox_shader.use();
    skybox_shader.set_int("skybox", 0);

    ECS::Window window;
    window.getInputManager().addEventListener(sf::Event::Closed, [&window](ECS::InputEvent event) {
        window.setActive(false);
    });
    window.getInputManager().addEventListener(sf::Event::MouseMoved, [&camera](ECS::InputEvent event) {
        camera.mouse_input(event.getMousePosition().first, event.getMousePosition().second);
    });
    window.getInputManager().addEventListener(sf::Event::KeyPressed, [&camera](ECS::InputEvent event) {
        camera.keyboard_input(event.getPressedKey());
    });

    while (window.isActive()) {
        window.processEvents();

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
        Matrix view_skybox = camera.get_view_matrix_without_translation();
        skybox_shader.set_mat4("view", view_skybox);
        skybox_shader.set_mat4("projection", projection);

        skybox_VAO.bind_array();
        glBindTexture(GL_TEXTURE_CUBE_MAP, skybox_texture);
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
