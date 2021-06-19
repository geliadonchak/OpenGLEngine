#pragma once

#ifndef OPENGLENGINE_ECS_WINDOW_HPP
#define OPENGLENGINE_ECS_WINDOW_HPP

#include <SFML/Window/Window.hpp>
#include <utility>

#include "WindowSettings.hpp"
#include "InputManager.hpp"

namespace ECS {

class Window {
  public:
    Window(const WindowSettings &windowSettings, InputManager inputManager) : inputManager(std::move(inputManager)) {
        window.create(windowSettings.getVideoMode(),
                      windowSettings.getTitle(),
                      windowSettings.getStyle(),
                      windowSettings.getContextSettings());
    }

    explicit Window(const WindowSettings &windowSettings) {
        window.create(windowSettings.getVideoMode(),
                      windowSettings.getTitle(),
                      windowSettings.getStyle(),
                      windowSettings.getContextSettings());
    }

    Window() {
        WindowSettings windowSettings;
        window.create(windowSettings.getVideoMode(),
                      windowSettings.getTitle(),
                      windowSettings.getStyle(),
                      windowSettings.getContextSettings());
    }

    void processEvents() {
        sf::Event window_event{};
        while (isActive() && window.pollEvent(window_event)) {
            inputManager.processEvent(window_event);
        }
    }

    InputManager &getInputManager() {
        return inputManager;
    }

    void display() {
        window.display();
    }

    void close() {
        window.close();
    }

    bool isActive() const {
        return active;
    }

    void setActive(bool active_) {
        active = active_;
    }

  private:
    sf::Window window;
    InputManager inputManager{};

    bool active = true;
};

}

#endif  // OPENGLENGINE_ECS_WINDOW_HPP