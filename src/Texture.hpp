#pragma once

#ifndef OPENGLENGINE_TEXTURE_HPP
#define OPENGLENGINE_TEXTURE_HPP

#include <functional>

class Texture {
 public:
    explicit Texture(char const* path) {
        glGenTextures(1, &texture_id);

        int width, height, nr_channels;
        unsigned char* data = stbi_load(path, &width, &height, &nr_channels, 0);
        if (data) {
            GLenum format;
            switch (nr_channels) {
                case 1:
                    format = GL_RED;
                    break;
                case 3:
                    format = GL_RGB;
                    break;
                case 4:
                    format = GL_RGBA;
                    break;
                default:
                    format = 0;
            }

            bind();
            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            generate_bitmap();
            stbi_image_free(data);
            return;
        }

    std::cout << " Texture failed to load at path (texture): " << path << std::endl;
        stbi_image_free(data);
    };

    explicit Texture(int width, int height, const std::function<std::vector<int>(int, int)> alg) {
        int pixel_index = 0;
        GLubyte pixels[width * height * 3];

        for (int i = 0; i < width; ++i) {
            for (int j = 0; j < height; ++j) {
                std::vector<int> pixel = alg(i, j);
                for (int k : pixel) {
                    pixels[pixel_index++] = k;
                }
            }
        }

        glGenTextures(1, &texture_id);
        bind();
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
        generate_bitmap();
    }

    void bind(int texture_block = -1) const {
        if (texture_block != -1) {
            glActiveTexture(GL_TEXTURE0 + texture_block);
        }

        glBindTexture(GL_TEXTURE_2D, texture_id);
    }

    unsigned int get_texture_id() const {
        return texture_id;
    }

    void set_texture_id(unsigned int tex_id) {
        texture_id = tex_id;
    }

    std::string get_texture_path() const {
        return path;
    }

    void set_texture_path(std::string& tex_path) {
        path = tex_path;
    }

 private:
    unsigned int texture_id = -1;
    std::string path{};

    static void generate_bitmap() {
        glGenerateMipmap(GL_TEXTURE_2D);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
};

#endif  // OPENGLENGINE_TEXTURE_HPP
