#pragma once

#include <limits>

#include "Shader.hpp"
#include "../LightSource.hpp"

#ifndef OPENGLENGINE_LIGHTNING_SHADER_FILLET_HPP
#define OPENGLENGINE_LIGHTNING_SHADER_FILLET_HPP

struct LightningShaderFiller {
    static void fill_light_shader(Shader &light_shader, LightSource &light_source) {
        switch (light_source.get_type()) {
            case LightSource::DIRECTIONAL: {
                light_shader.set_vec3("dirLight.direction", light_source.get_direction());
                light_shader.set_vec3("dirLight.ambient", light_source.get_ambient());
                light_shader.set_vec3("dirLight.diffuse", light_source.get_diffuse());
                light_shader.set_vec3("dirLight.specular", light_source.get_specular());
                break;
            }
            case LightSource::POINT: {
                std::string index = "pointLights[" + std::to_string(light_source.get_point_index()) + "]";
                light_shader.set_float(index + ".constant", light_source.get_constant());
                light_shader.set_float(index + ".linear", light_source.get_linear());
                light_shader.set_float(index + ".quadratic", light_source.get_quadratic());
                light_shader.set_vec3(index + ".position", light_source.get_position());
                light_shader.set_vec3(index + ".ambient", light_source.get_ambient());
                light_shader.set_vec3(index + ".diffuse", light_source.get_diffuse());
                light_shader.set_vec3(index + ".specular", light_source.get_specular());
                break;
            }
            case LightSource::SPOT: {
                light_shader.set_float("spotLight.cutOff", light_source.get_cut_off());
                light_shader.set_float("spotLight.outerCutOff", light_source.get_outer_cut_off());
                light_shader.set_float("spotLight.constant", light_source.get_constant());
                light_shader.set_float("spotLight.linear", light_source.get_linear());
                light_shader.set_float("spotLight.quadratic", light_source.get_quadratic());
                light_shader.set_vec3("spotLight.position", light_source.get_position());
                light_shader.set_vec3("spotLight.direction", light_source.get_direction());
                light_shader.set_vec3("spotLight.ambient", light_source.get_ambient());
                light_shader.set_vec3("spotLight.diffuse", light_source.get_diffuse());
                light_shader.set_vec3("spotLight.specular", light_source.get_specular());
                break;
            }
        }
    }

    static void fill_default_values(Shader &light_shader, int points) {
        float invalidFloat = std::numeric_limits<float>::min();
        light_shader.set_float("invalidFloat", invalidFloat);
        light_shader.set_vec3("result", {0.0f, 0.0f, 0.0f});

        light_shader.set_vec3("dirLight.direction", {invalidFloat, invalidFloat, invalidFloat});
        light_shader.set_vec3("dirLight.ambient", {invalidFloat, invalidFloat, invalidFloat});
        light_shader.set_vec3("dirLight.diffuse", {invalidFloat, invalidFloat, invalidFloat});
        light_shader.set_vec3("dirLight.specular", {invalidFloat, invalidFloat, invalidFloat});

        for (int i = 0; i < points; i++) {
            std::string index = "pointLights[" + std::to_string(i) + "]";

            light_shader.set_float(index + ".constant", invalidFloat);
            light_shader.set_float(index + ".linear", invalidFloat);
            light_shader.set_float(index + ".quadratic", invalidFloat);
            light_shader.set_vec3(index + ".position", {invalidFloat, invalidFloat, invalidFloat});
            light_shader.set_vec3(index + ".ambient", {invalidFloat, invalidFloat, invalidFloat});
            light_shader.set_vec3(index + ".diffuse", {invalidFloat, invalidFloat, invalidFloat});
            light_shader.set_vec3(index + ".specular", {invalidFloat, invalidFloat, invalidFloat});
        }

        light_shader.set_float("spotLight.cutOff", invalidFloat);
        light_shader.set_float("spotLight.outerCutOff", invalidFloat);
        light_shader.set_float("spotLight.constant", invalidFloat);
        light_shader.set_float("spotLight.linear", invalidFloat);
        light_shader.set_float("spotLight.quadratic", invalidFloat);
        light_shader.set_vec3("spotLight.position", {invalidFloat, invalidFloat, invalidFloat});
        light_shader.set_vec3("spotLight.direction", {invalidFloat, invalidFloat, invalidFloat});
        light_shader.set_vec3("spotLight.ambient", {invalidFloat, invalidFloat, invalidFloat});
        light_shader.set_vec3("spotLight.diffuse", {invalidFloat, invalidFloat, invalidFloat});
        light_shader.set_vec3("spotLight.specular", {invalidFloat, invalidFloat, invalidFloat});
    }
};

#endif  // OPENGLENGINE_LIGHTNING_SHADER_FILLET_HPP
