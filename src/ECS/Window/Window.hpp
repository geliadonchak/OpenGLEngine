#pragma once

#ifndef OPENGLENGINE_ECS_WINDOW_HPP
#define OPENGLENGINE_ECS_WINDOW_HPP

#include <SFML/Window/Window.hpp>
#include <utility>

#include "WindowSettings.hpp"
#include "../InputSystem/InputManager.hpp"

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
        sf::Event windowEvent{};
        while (isActive() && window.pollEvent(windowEvent)) {
            inputManager.processEvent(windowEvent);
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