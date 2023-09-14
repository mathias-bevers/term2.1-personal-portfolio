#include "game.hpp"

namespace personal_portfolio {
    Game::Game() {
        LOG(INFO) << "Setting up game...";

        window.create(sf::VideoMode(1600, 1000), "Game");

        LOG(INFO) << "Setup complete!";
    }

    void Game::start() {
        LOG(INFO) << "Starting game...";

        circle.setRadius(100.0f);
        circle.setFillColor(sf::Color::Green);

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
            }

            window.clear();
            update();
            window.display();
        }
    }

    void Game::update() {
        window.draw(circle);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window.close();
        }
    }
    
    Game::~Game() {
        LOG(INFO) << "Terminating game";
    }
}