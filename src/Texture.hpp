#pragma once

#ifndef OPENGLENGINE_TEXTURE_HPP
#define OPENGLENGINE_TEXTURE_HPP

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

            glBindTexture(GL_TEXTURE_2D, texture_id);
            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            stbi_image_free(data);
            return;
        }

        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    };

    void bind(int texture_block = -1) const {
        if (texture_block != -1) {
            glActiveTexture(GL_TEXTURE0 + texture_block);
        }

        glBindTexture(GL_TEXTURE_2D, texture_id);
    };

    unsigned int get_texture_id() const {
        return texture_id;
    };

    float get_rows_number() const {
        return rows_number;
    };

    Texture set_rows_number(float num) {
        rows_number = num;

        return *this;
    };

 private:
    unsigned int texture_id = -1;
    float rows_number = 1.f;
};

#endif  // OPENGLENGINE_TEXTURE_HPP
