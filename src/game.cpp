#include "game.h"
#include "tools/easylogging++.h"

namespace personal_portfolio {
    Game* Game::instance;

    Game::Game() {
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

        game_objects.push_back(new Player("test.png"));

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    close();
                }
            }

            window.clear();
            update();
            render();
            window.display();
        }
    }

    void Game::update() {
        for (GameObject* game_object : game_objects) {
            game_object->update();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            close();
        }
    }

    void Game::render() {
        for (GameObject* game_object : game_objects) {
            game_object->render(window);
        }
    }

    sf::RenderWindow& Game::get_window() { return window; }

    void Game::close() {
        LOG(INFO) << "Closing game...";

        if (&window != nullptr) {
            window.close();
        }
    }

    Game::~Game() {
        LOG(INFO) << "Terminating game instance";
        Game::instance = nullptr;
    }
}