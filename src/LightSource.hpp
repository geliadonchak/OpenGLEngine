#pragma once

#include <limits>

#ifndef OPENGLENGINE_LIGHT_SOURCE_HPP
#define OPENGLENGINE_LIGHT_SOURCE_HPP

class LightSource {
public:
    enum lightCasterType {
        DIRECTIONAL,
        POINT,
        SPOT,
    };

    explicit LightSource(lightCasterType _type) : type(_type) {}

    LightSource *getLightSource() {
        return this;
    }

    lightCasterType getYype() const {
        return type;
    };

    LightSource *set_direction(const Vector &_direction) {
        direction = _direction;
        return this;
    };

    Vector get_direction() const {
        return direction;
    };

    LightSource *set_ambient(const Vector &_ambient) {
        ambient = _ambient;
        return this;
    };

    Vector get_ambient() const {
        return ambient;
    };

    LightSource *set_diffuse(const Vector &_diffuse) {
        diffuse = _diffuse;
        return this;
    };

    Vector get_diffuse() const {
        return diffuse;
    };

    LightSource *set_specular(const Vector &_specular) {
        specular = _specular;
        return this;
    };

    Vector get_specular() const {
        return specular;
    };

    LightSource *set_position(const Vector &_position) {
        position = _position;
        return this;
    };

    Vector get_position() const {
        return position;
    };

    LightSource *set_constant(float _constant) {
        constant = _constant;
        return this;
    };

    float get_constant() const {
        return constant;
    };

    LightSource *set_linear(float _linear) {
        linear = _linear;
        return this;
    };

    float get_linear() const {
        return linear;
    };

    LightSource *set_quadratic(float _quadratic) {
        quadratic = _quadratic;
        return this;
    };

    float get_quadratic() const {
        return quadratic;
    };

    LightSource *set_cut_off(float _cut_off) {
        cut_off = _cut_off;
        return this;
    };

    float get_cut_off() const {
        return cut_off;
    };

    LightSource *set_outer_cut_off(float _outer_cut_off) {
        outer_cut_off = _outer_cut_off;
        return this;
    };

    float get_outer_cut_off() const {
        return outer_cut_off;
    };

    size_t get_point_index() const {
        return point_index;
    }

    LightSource *set_point_index(size_t _point_index) {
        point_index = _point_index;
        return this;
    }

private:
    lightCasterType type = DIRECTIONAL;

    size_t point_index = 0;

    Vector direction{};
    Vector ambient{};
    Vector diffuse{};
    Vector specular{};
    Vector position{};

    float constant = std::numeric_limits<float>::min();
    float linear = std::numeric_limits<float>::min();
    float quadratic = std::numeric_limits<float>::min();
    float cut_off = std::numeric_limits<float>::min();
    float outer_cut_off = std::numeric_limits<float>::min();
};

#endif  // OPENGLENGINE_LIGHT_SOURCE_HPP
