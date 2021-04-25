#pragma once

#ifndef OPENGLENGINE_MATERIAL_HPP
#define OPENGLENGINE_MATERIAL_HPP

class Material {
 public:
    Material(int _diffuse, int _specular, float _shininess) :
        diffuse(_diffuse), specular(_specular), shininess(_shininess) {};

    int get_diffuse() const {
        return diffuse;
    };

    int get_specular() const {
        return specular;
    };

    float get_shininess() const {
        return shininess;
    };

 private:
    int diffuse = 0;
    int specular = 0;
    float shininess = 0.f;
};

#endif //OPENGLENGINE_MATERIAL_HPP