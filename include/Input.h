#ifndef __INPUT__
#define __INPUT__

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

#include <memory>

class Input {
    public:
        // get a pointer to the window the input class must listen to
        // instead of passing it each frame in argument in the update() method
        /**
         * @param window the window to bind the inputs
         */
        Input(sf::RenderWindow &window);
        ~Input();

        // update all keys / buttons listeners
        void update();


        // getters
        /** return a bool either a specific key/button is downed, pressed, or released
         * @param   sf::Keyboard::Key   target key
         * @return  bool                key state
         */
        bool isKeyDown(sf::Keyboard::Key key) const; // key is down
        bool isKeyUp(sf::Keyboard::Key key) const; // key is released
        bool isKeyPress(sf::Keyboard::Key key) const; // key is pressed
        bool isMouseButtonDown(sf::Mouse::Button key) const; // mouse button down
        bool isMouseButtonUp(sf::Mouse::Button key) const; // mouse button released
        bool isMouseButtonPressed(sf::Mouse::Button btn) const; // mouse button pressed


        /** return the state of a key (true/false)
         * @param   sf::Keyboard::Key   target key
         * @return  bool                key state
         */
        bool getKey(sf::Keyboard::Key key) const;

        /** return the state of a mouse button (true/false)
         * @param   sf::Mouse::Button   target button
         * @return  bool                button state
         */
        bool getMouseButton(sf::Mouse::Button btn) const;


    private:
        /** called by update() method to treat a specific event
         * @param   sf::Event   event
         */
        void eventTreatment(sf::Event event);

        // keyboard keys (true = down, false = up)
        bool m_keys[sf::Keyboard::KeyCount];
        bool m_pressed_keys[sf::Keyboard::KeyCount];
        // mouse buttons (true = down, false = up)
        bool m_mouseButtons[sf::Mouse::ButtonCount];
        bool m_mouseButtons_pressed[sf::Mouse::ButtonCount];


        // pointer to the window
        sf::RenderWindow &m_window;
};

#endif // input