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
#include "../../Math/Vector.hpp"
#include "../Utils/Mesh.hpp"
#include "../../Shader.hpp"
#include "Texture.hpp"

class Model {
 public:
    std::vector<Texture> textures_loaded;
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
            meshes.push_back(processMesh(mesh, scene));
        }

        for (unsigned int i = 0; i < node->mNumChildren; i++) {
            process_node(node->mChildren[i], scene);
        }
    }

    Mesh processMesh(aiMesh *mesh, const aiScene *scene) {
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices{};
        std::vector<Texture> textures;

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

        std::vector<Texture> diffuseMaps = load_material_textures(material, aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

        std::vector<Texture> specularMaps = load_material_textures(material, aiTextureType_SPECULAR, "texture_specular");
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

        std::vector<Texture> normalMaps = load_material_textures(material, aiTextureType_HEIGHT, "texture_normal");
        textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());

        std::vector<Texture> heightMaps = load_material_textures(material, aiTextureType_AMBIENT, "texture_height");
        textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

        return Mesh(vertices, indices, textures);
    }

    std::vector<Texture> load_material_textures(aiMaterial *mat, aiTextureType type, const std::string& type_name) {
        std::vector<Texture> textures;
        for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
            aiString str;
            mat->GetTexture(type, i, &str);

            bool skip = false;
            for (auto & j : textures_loaded) {
                if (std::strcmp(j.getPath().data(), str.C_Str()) == 0) {
                    textures.push_back(j);
                    skip = true;
                    break;
                }
            }

            if (!skip) {
                std::string filename = directory + '/' + str.C_Str();
                Texture texture;
                texture.loadTexture({filename});
                texture.setPath(str.C_Str());
                texture.setType(type_name);

                textures.push_back(texture);
                textures_loaded.push_back(texture);
            }
        }
        return textures;
    }
};

#endif // OPENGLENGINE_MODEL_HPP
