#pragma once

#ifndef OPENGLENGINE_ECS_INPUT_MANAGER_HPP
#define OPENGLENGINE_ECS_INPUT_MANAGER_HPP

#include <map>
#include <SFML/Window/Event.hpp>
#include <functional>
#include "InputEvent.hpp"

namespace ECS {

    typedef std::function<void(InputEvent)> EventListener;

    class InputManager {
    public:
        void processEvent(sf::Event event) {
            InputEvent inputEvent(event);
            if (eventListeners.find(event.type) != eventListeners.end()) {
                for (auto & listener : eventListeners.at(event.type)) {
                    listener(inputEvent);
                }
            }
        }

        void addEventListener(sf::Event::EventType eventType, const EventListener &listener) {
            if (eventListeners.find(eventType) == eventListeners.end()) {
                eventListeners.insert({eventType, {listener}});
            }

            eventListeners.at(eventType).push_back(listener);
        }

        void clearEvents() {
            eventListeners.clear();
        }

    private:
        std::map<sf::Event::EventType, std::vector<EventListener>> eventListeners;
    };

}

#endif  // OPENGLENGINE_ECS_INPUT_MANAGER_HPP