#pragma once

#ifndef OPENGLENGINE_ECS_INPUT_EVENT_HPP
#define OPENGLENGINE_ECS_INPUT_EVENT_HPP

#include <SFML/Window/Event.hpp>

namespace ECS {

    class InputEvent {
    public:
        explicit InputEvent(sf::Event event) : eventType(event.type) {
            switch (getEventType()) {
                case sf::Event::KeyPressed:
                    for (int keysIter = sf::Keyboard::Key::A; keysIter != sf::Keyboard::Key::KeyCount; ++keysIter) {
                        auto key = static_cast<sf::Keyboard::Key>(keysIter);
                        if (sf::Keyboard::isKeyPressed(key)) {
                            pressedKey = key;
                            break;
                        }
                    }
                    break;
                case sf::Event::MouseMoved:
                    mousePosition.first = event.mouseMove.x;
                    mousePosition.second = event.mouseMove.y;
                    break;
                default:
                    break;
            }
        }

        sf::Event::EventType getEventType() const {
            return eventType;
        }

        sf::Keyboard::Key getPressedKey() const {
            return pressedKey;
        }

        std::pair<float, float> getMousePosition() const {
            return mousePosition;
        }

    private:
        sf::Event::EventType eventType;
        std::pair<float, float> mousePosition;
        sf::Keyboard::Key pressedKey;
    };

}

#endif  // OPENGLENGINE_ECS_INPUT_EVENT_HPP