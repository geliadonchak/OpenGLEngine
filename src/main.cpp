#ifndef OPENGLENGINE_MAIN_CPP
#define OPENGLENGINE_MAIN_CPP

#include <iostream>
//#include <GL/glew.h>
//#include <SFML/Window.hpp>
#include "../external/stb/stb_image.h"
#include "Camera.hpp"
#include "Shader.hpp"

#include "ECS/InputSystem/InputManager.hpp"
#include "ECS/Window/Window.hpp"

#include "VertexArrayObject.hpp"
#include "VertexBufferObject.hpp"
#include "ECS/Utils/Mesh.hpp"
#include "ECS/Components/Model.hpp"
#include "ECS/Components/Texture.hpp"
#include "LightSource.hpp"
#include "Utils/LightningShaderFiller.hpp"
#include "Material.hpp"
#include "ECS/Components/SkyboxTexture.hpp"

int main() {
    ECS::Window window;

    glewExperimental = GL_TRUE;
    if (GLEW_OK != glewInit()) {
        std::cerr << "Error: glew not init =(" << std::endl;
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

    SkyboxTexture skybox_texture;
    skybox_texture.loadTexture(faces);

    Shader model_shader("../resources/shaders/model.vs", "../resources/shaders/model.fs");
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

    window.getInputManager().addEventListener(sf::Event::Closed, [&window](ECS::InputEvent event) {
        window.setActive(false);
    });
    window.getInputManager().addEventListener(sf::Event::MouseMoved, [&camera](ECS::InputEvent event) {
      camera.onMouseInput(event.getMousePosition().first, event.getMousePosition().second);
    });
    window.getInputManager().addEventListener(sf::Event::KeyPressed, [&camera](ECS::InputEvent event) {
      camera.onKeyboardInput(event.getPressedKey());
    });

    while (window.isActive()) {
        window.processEvents();

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        model_shader.use();
        Matrix projection(camera.getProjectionMatrix());
        Matrix view(camera.getViewMatrix());
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
        Matrix view_skybox = camera.getViewMatrixWithoutTranslation();
        skybox_shader.set_mat4("view", view_skybox);
        skybox_shader.set_mat4("projection", projection);

        skybox_VAO.bind_array();
        skybox_texture.bind();
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
