#pragma once

#include "Shader.hpp"
#include "../LightSource.hpp"

#ifndef OPENGLENGINE_LIGHTNING_SHADER_FILLET_HPP
#define OPENGLENGINE_LIGHTNING_SHADER_FILLET_HPP

struct LightningShaderFiller {
    static void fill_light_shader(Shader &light_shader, LightSource &light_source) {
        if (light_source.get_direction().size() != 0) {
            light_shader.set_vec3("light.direction", light_source.get_direction());
        }
        if (light_source.get_ambient().size() != 0) {
            light_shader.set_vec3("light.ambient", light_source.get_ambient());
        }
        if (light_source.get_diffuse().size() != 0) {
            light_shader.set_vec3("light.diffuse", light_source.get_diffuse());
        }
        if (light_source.get_specular().size() != 0) {
            light_shader.set_vec3("light.specular", light_source.get_specular());
        }
        if (light_source.get_position().size() != 0) {
            light_shader.set_vec3("light.position", light_source.get_position());
        }

        if (light_source.get_constant() != std::numeric_limits<float>::min()) {
            light_shader.set_float("light.constant", light_source.get_constant());
        }
        if (light_source.get_linear() != std::numeric_limits<float>::min()) {
            light_shader.set_float("light.linear", light_source.get_linear());
        }
        if (light_source.get_quadratic() != std::numeric_limits<float>::min()) {
            light_shader.set_float("light.quadratic", light_source.get_quadratic());
        }
        if (light_source.get_cut_off() != std::numeric_limits<float>::min()) {
            light_shader.set_float("light.cutOff", light_source.get_cut_off());
        }
        if (light_source.get_outer_cut_off() != std::numeric_limits<float>::min()) {
            light_shader.set_float("light.outerCutOff", light_source.get_outer_cut_off());
        }
    }
};

#endif //OPENGLENGINE_LIGHTNING_SHADER_FILLET_HPP