#include "gameObject.hpp"

namespace personal_portfolio {
    GameObject::GameObject() : GameObject::GameObject(sf::Vector2f(0, 0), sf::Vector2f(1, 1)) { }
    GameObject::GameObject(sf::Vector2f size) : GameObject::GameObject(sf::Vector2f(0, 0), size) { }
    GameObject::GameObject(sf::Vector2f position, sf::Vector2f size) { }
    GameObject::~GameObject() = default;
}