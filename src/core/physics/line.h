#ifndef LINE_H
#define LINE_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/System/Vector2.hpp>

#include "physicsObject.h"

namespace personal_portfolio {
    class Line : public PhysicsObject {
      private:
        sf::Vertex line_vertices[2];
        sf::Vertex normal_vertices[2];

        sf::Vector2f start;
        sf::Vector2f end;
        float magnitude;

      public:
        Line(int start_x, int start_y, int end_x, int end_y, GameObject* parent = nullptr);
        Line(sf::Vector2f start, sf::Vector2f end, GameObject* parent = nullptr);

        const sf::Vector2f get_normal() const;
        const sf::Vector2f get_center() const;
        const sf::Vector2f get_difference() const;
        const float get_magnitude() const;

        const sf::Vector2f get_start() const;
        const sf::Vector2f get_end() const;
        
        void render(sf::RenderWindow& window);

        ~Line();
    };
}
#endif