#pragma ones

#ifndef OPENGLENGINE_MESH_HPP
#define OPENGLENGINE_MESH_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include "VertexArrayObject.hpp"
#include "VertexBufferObject.hpp"
#include "utils/Shader.hpp"

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texture_coords;
    glm::vec3 tangent;
    glm::vec3 bitangent;
};

struct Text {
    unsigned int id;
    std::string type;
    std::string path;
};

class Mesh {
 public:
    std::vector<Vertex> vertices{};
    std::vector<unsigned int> indices{};
    std::vector<Text> textures;
    unsigned int VAO{};

    Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, std::vector<Text>& textures) {
        this->vertices = vertices;
        this->indices = indices;
        this->textures = textures;

        setup_mesh();
    }

    void draw(Shader &shader) {
        unsigned int diffuse_n = 1;
        unsigned int specular_n = 1;
        unsigned int normal_n = 1;
        unsigned int height_n = 1;

        for (unsigned int i = 0; i < textures.size(); i++) {
            glActiveTexture(GL_TEXTURE0 + i);

            std::string number;
            std::string name = textures[i].type;

            if (name == "texture_diffuse") {
                number = std::to_string(diffuse_n++);
            } else if (name == "texture_specular") {
                number = std::to_string(specular_n++);
            } else if (name == "texture_normal") {
                number = std::to_string(normal_n++);
            }
            else if (name == "texture_height") {
                number = std::to_string(height_n++);
            }

            glUniform1i(glGetUniformLocation(shader.get_shader_id(), (name + number).c_str()), i);
            glBindTexture(GL_TEXTURE_2D, textures[i].id);

            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
            glBindVertexArray(0);

            glActiveTexture(GL_TEXTURE0);
        }
    }

 private:
    unsigned int VBO{}, EBO{};

    void setup_mesh() {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) nullptr);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, normal));

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, texture_coords));

        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, tangent));

        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, bitangent));

        glBindVertexArray(0);
    };
};

#endif // OPENGLENGINE_MESH_HPP
