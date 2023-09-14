#include <SFML/Graphics.hpp>
#include <iostream>
#include <limits>

#include "src/tools/easylogging++.h"

INITIALIZE_EASYLOGGINGPP

int main(int argc, char* argv[]) {
    std::cout << "Mathias Bevers personal portfolio 1\n\n";
    LOG(INFO) << "My first info log using default logger";

    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    std::cout << "Press Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return 0;
}