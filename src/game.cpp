

#include "game.hpp"
#include "tools/easylogging++.h"

namespace personal_portfolio {
    Game* Game::instance;

    Game::Game() : player("test.png") {
        LOG(INFO) << "Setting up game instance...";

        if (Game::instance != nullptr) {
            LOG(WARNING) << "Trying to instantiate a second game instance, destroying...";
            return;
        }

        Game::instance = this;
        window.create(sf::VideoMode(1600, 1000), "Game");

        LOG(INFO) << "Setup complete!";
    }

    void Game::start() {
        LOG(INFO) << "Starting game...";

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    close();
                }
            }

            window.clear();
            update();
            window.display();
        }
    }

    void Game::update() {
        player.update();
        window.draw(player.getSprite());

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            close();
        }
    }

    sf::RenderWindow& Game::getWindow() {
        return window;
    }

    void Game::close() {
        LOG(INFO) << "Closing game...";

        if (&window != nullptr) {
            window.close();
        }
    }

    Game::~Game() {
        Game::instance = nullptr;
        LOG(INFO) << "Terminating game instance";
    }
}