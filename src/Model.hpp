#pragma ones

#ifndef OPENGLENGINE_MODEL_HPP
#define OPENGLENGINE_MODEL_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
#include "Vector.hpp"
#include "Mesh.hpp"
#include "utils/Shader.hpp"

unsigned int texture_from_file(const char *path, const std::string &directory, bool gamma = false);

class Model {
 public:
    std::vector<Text> textures_loaded;
    std::vector<Mesh> meshes;
    std::string directory;
    bool gamma_correction;

    explicit Model(std::string const &path, bool gamma = false) : gamma_correction(gamma) {
        load_model(path);
    }

    void draw(Shader &shader) {
        for (auto & mesh : meshes) {
            mesh.draw(shader);
        }
    }

 private:
    void load_model(std::string const &path) {
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
            std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
            return;
        }

        directory = path.substr(0, path.find_last_of('/'));

        process_node(scene->mRootNode, scene);
    }

    void process_node(aiNode *node, const aiScene *scene) {
        for (unsigned int i = 0; i < node->mNumMeshes; i++) {
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            meshes.push_back(process_mesh(mesh, scene));
        }

        for (unsigned int i = 0; i < node->mNumChildren; i++) {
            process_node(node->mChildren[i], scene);
        }
    }

    Mesh process_mesh(aiMesh *mesh, const aiScene *scene) {
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices{};
        std::vector<Text> textures;

        for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
            Vertex vertex;
            glm::vec3 vector;

            vector[0] = mesh->mVertices[i].x;
            vector[1] = mesh->mVertices[i].y;
            vector[2] = mesh->mVertices[i].z;
            vertex.position = vector;

            if (mesh->HasNormals()) {
                vector[0] = mesh->mNormals[i].x;
                vector[1] = mesh->mNormals[i].y;
                vector[2] = mesh->mNormals[i].z;
                vertex.normal = vector;
            }

            if (mesh->mTextureCoords[0]) {
                glm::vec2 vec;

                vec[0] = mesh->mTextureCoords[0][i].x;
                vec[1] = mesh->mTextureCoords[0][i].y;
                vertex.texture_coords = vec;

                vector[0] = mesh->mTangents[i].x;
                vector[1] = mesh->mTangents[i].y;
                vector[2] = mesh->mTangents[i].z;
                vertex.tangent = vector;

                vector[0] = mesh->mBitangents[i].x;
                vector[1] = mesh->mBitangents[i].y;
                vector[2] = mesh->mBitangents[i].z;
                vertex.bitangent = vector;
            } else {
                vertex.texture_coords = glm::vec2(0.0f, 0.0f);
            }

            vertices.push_back(vertex);
        }

        for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
            aiFace face = mesh->mFaces[i];

            for (unsigned int j = 0; j < face.mNumIndices; j++) {
                indices.push_back(face.mIndices[j]);
            }
        }

        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

        std::vector<Text> diffuse_maps = load_material_textures(material, aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuse_maps.begin(), diffuse_maps.end());

        std::vector<Text> specular_maps = load_material_textures(material, aiTextureType_SPECULAR, "texture_specular");
        textures.insert(textures.end(), specular_maps.begin(), specular_maps.end());

        std::vector<Text> normal_maps = load_material_textures(material, aiTextureType_HEIGHT, "texture_normal");
        textures.insert(textures.end(), normal_maps.begin(), normal_maps.end());

        std::vector<Text> height_maps = load_material_textures(material, aiTextureType_AMBIENT, "texture_height");
        textures.insert(textures.end(), height_maps.begin(), height_maps.end());

        return Mesh(vertices, indices, textures);
    }

    std::vector<Text> load_material_textures(aiMaterial *mat, aiTextureType type, const std::string& type_name) {
        std::vector<Text> textures;
        for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
            aiString str;
            mat->GetTexture(type, i, &str);

            bool skip = false;
            for (auto & j : textures_loaded) {
                if (std::strcmp(j.path.data(), str.C_Str()) == 0) {
                    textures.push_back(j);
                    skip = true;
                    break;
                }
            }

            if (!skip) {
                std::string filename = directory + '/' + str.C_Str();
                Text texture;
                texture.id = texture_from_file(str.C_Str(), this->directory);
                texture.type = type_name;
                texture.path = str.C_Str();
                textures.push_back(texture);
                textures_loaded.push_back(texture);
            }
        }
        return textures;
    }
};

unsigned int texture_from_file(const char *path, const std::string &directory, bool gamma) {
    std::string filename = (std::string)path;
    filename = directory + '/' + filename;

    unsigned int texture_ID;
    glGenTextures(1, &texture_ID);

    int width, height, nr_components;
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nr_components, 0);
    if (data) {
        GLenum format;
        if (nr_components == 1) {
            format = GL_RED;
        } else if (nr_components == 3) {
            format = GL_RGB;
        } else if (nr_components == 4) {
            format = GL_RGBA;
        }

        glBindTexture(GL_TEXTURE_2D, texture_ID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    } else {
        std::cout << "Texture failed to load at path (model): " << path << std::endl;
        stbi_image_free(data);
    }

    return texture_ID;
}

#endif // OPENGLENGINE_MODEL_HPP
