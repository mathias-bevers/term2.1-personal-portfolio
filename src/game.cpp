#include "game.h"
#include "player.h"
#include "scenes/gameScene.h"
#include "tools/easylogging++.h"
#include "tools/settings.h"

namespace personal_portfolio {
    Game* Game::instance;

    Game::Game()
    {
        LOG(INFO) << "Setting up game instance...";

        if (Game::instance != nullptr) {
            LOG(WARNING) << "Trying to instantiate a second game instance, destroying...";
            return;
        }

        Game::instance = this;

        window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HIGHT), "Game");
        scene_manager = new SceneManager();

        LOG(INFO) << "Setup complete!";
    }

    void Game::start()
    {
        LOG(INFO) << "Starting game...";

        scene_manager->load_scene("StartScene");

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

    void Game::update()
    {
        scene_manager->get_active_scene().update();

        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            return;
        }

        close();
    }

    void Game::render() { scene_manager->get_active_scene().render(window); }

    SceneManager& Game::get_scene_manager() const { return *scene_manager; }

    const sf::RenderWindow& Game::get_window() const { return window; }

    void Game::close()
    {
        LOG(INFO) << "Closing game...";

        if (&window != nullptr) {
            window.close();
        }
    }

    Game::~Game()
    {
        LOG(INFO) << "Terminating game instance";
        Game::instance = nullptr;
    }
}