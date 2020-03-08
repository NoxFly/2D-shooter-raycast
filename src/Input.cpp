#include "Input.h"

Input::Input(sf::RenderWindow &window): m_window(window) {
    // init to false all the keys state
    for(auto i=0; i < sf::Keyboard::KeyCount; i++) {
        m_keys[i] = false;
        m_pressed_keys[i] = false;
    }

    // init to false all the buttons state
    for(auto i=0; i < sf::Mouse::ButtonCount; i++) {
        m_mouseButtons[i] = false;
        m_mouseButtons_pressed[i] = false;
    }
}

Input::~Input() {

}

void Input::update() {
    for(auto i=0; i < sf::Keyboard::KeyCount; i++)
        m_pressed_keys[i] = false;
    for(auto i=0; i < sf::Mouse::ButtonCount; i++)
        m_mouseButtons_pressed[i] = false;


    sf::Event event;
    // pops each event and treat them
    while(m_window.pollEvent(event)) {
        eventTreatment(event);
    }
}

void Input::eventTreatment(sf::Event event) {
    switch(event.type) {
        // close window by X
        case sf::Event::Closed: m_window.close(); break;

        // keyboard's key pressed
        case sf::Event::KeyPressed:
            m_pressed_keys[event.key.code] = false;
            m_keys[event.key.code] = true;
            break;

        // keyboard's key released
        case sf::Event::KeyReleased:
            if(m_keys[event.key.code]) m_pressed_keys[event.key.code] = true;
            m_keys[event.key.code] = false;
            break;

        // mouse's button pressed
        case sf::Event::MouseButtonPressed:
            m_mouseButtons_pressed[event.mouseButton.button] = false;
            m_mouseButtons[event.mouseButton.button] = true;
            break;

        // mouse's button released
        case sf::Event::MouseButtonReleased:
            if(m_mouseButtons[event.mouseButton.button]) m_mouseButtons_pressed[event.mouseButton.button] = true;
            m_mouseButtons[event.mouseButton.button] = false;
            break;

        // untreated cases
        default: break;
    }

}

// getters

bool Input::getKey(sf::Keyboard::Key key) const {
    return m_keys[key];
}

bool Input::getMouseButton(sf::Mouse::Button btn) const {
    return m_mouseButtons[btn];
}

bool Input::isKeyDown(sf::Keyboard::Key key) const {
    return m_keys[key];
}

bool Input::isKeyUp(sf::Keyboard::Key key) const {
    return !m_keys[key];
}

bool Input::isKeyPress(sf::Keyboard::Key key) const {
    return m_pressed_keys[key];
}

bool Input::isMouseButtonDown(sf::Mouse::Button btn) const {
    return m_mouseButtons[btn];
}

bool Input::isMouseButtonUp(sf::Mouse::Button btn) const {
    return !m_mouseButtons[btn];
}

bool Input::isMouseButtonPressed(sf::Mouse::Button btn) const {
    return m_mouseButtons_pressed[btn];
}