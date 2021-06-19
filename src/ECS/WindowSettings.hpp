#pragma once

#ifndef OPENGLENGINE_ECS_WINDOW_setTINGS_HPP
#define OPENGLENGINE_ECS_WINDOW_setTINGS_HPP

#include <string>
#include <SFML/Window/Window.hpp>
#include <SFML/Config.hpp>

namespace ECS {

class WindowSettings {
  public:
    sf::VideoMode getVideoMode() const {
        return {width, height, modeBitsPerPixels};
    }

    sf::ContextSettings getContextSettings() const {
        sf::ContextSettings settings;
        settings.depthBits = contextDepthBits;
        settings.stencilBits = contextStencilBits;
        settings.majorVersion = contextMajorVersion;
        settings.minorVersion = contextMinorVersion;
        settings.attributeFlags = contextAttributeFlags;
        return settings;
    }

    const std::string &getTitle() const {
        return title;
    }

    void setTitle(const std::string &title_) {
        title = title_;
    }

    const sf::Uint32 &getStyle() const {
        return style;
    }

    void setStyle(const sf::Uint32 &style_) {
        style = style_;
    }

    void setWidth(sf::Uint32 width_) {
        WindowSettings::width = width_;
    }

    void setHeight(sf::Uint32 height_) {
        height = height_;
    }

    void setModeBitsPerPixels(sf::Uint32 mode_bits_per_pixels) {
        modeBitsPerPixels = mode_bits_per_pixels;
    }

    void setContextDepthBits(sf::Uint32 context_depth_bits) {
        contextDepthBits = context_depth_bits;
    }

    void setContextStencilBits(sf::Uint32 context_stencil_bits) {
        contextStencilBits = context_stencil_bits;
    }

    void setContextMajorVersion(sf::Uint32 context_major_version) {
        contextMajorVersion = context_major_version;
    }

    void setContextMinorVersion(sf::Uint32 context_minor_version) {
        contextMinorVersion = context_minor_version;
    }

    void setContextAttributeFlags(sf::Uint32 context_attribute_flags) {
        contextAttributeFlags = context_attribute_flags;
    }

  private:
    std::string title = "Window";
    sf::Uint32 style = sf::Style::Titlebar | sf::Style::Close;

    sf::Uint32 width = 1200;
    sf::Uint32 height = 900;
    sf::Uint32 modeBitsPerPixels = 32;

    sf::Uint32 contextDepthBits = 24;
    sf::Uint32 contextStencilBits = 8;
    sf::Uint32 contextMajorVersion = 4;
    sf::Uint32 contextMinorVersion = 3;
    sf::Uint32 contextAttributeFlags = sf::ContextSettings::Core;;
};

}

#endif  // OPENGLENGINE_ECS_WINDOW_setTINGS_HPP