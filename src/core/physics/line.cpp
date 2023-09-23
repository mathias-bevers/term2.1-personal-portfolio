#include <cmath>

#include "line.h"

namespace personal_portfolio {
    Line::Line(int start_x, int start_y, int end_x, int end_y, GameObject* parent) :
        Line::Line(sf::Vector2f(start_x, start_y), sf::Vector2f(end_x, end_y), parent)
    {
    }

    Line::Line(sf::Vector2f start, sf::Vector2f end, GameObject* parent) : PhysicsObject(parent)
    {
        this->start = start;
        this->end = end;

        sf::Color line_color(0, 252, 60);
        line_vertices[0].position = get_start();
        line_vertices[0].color = line_color;
        line_vertices[1].position = get_end();
        line_vertices[1].color = line_color;

        sf::Color normal_color(255, 3, 195);
        normal_vertices[0].color = normal_color;
        normal_vertices[0].position = get_center();
        normal_vertices[1].color = normal_color;
        normal_vertices[1].position = get_center() + (get_normal() * 50.0f);
    }

    const sf::Vector2f Line::get_center() const
    {
        return sf::Vector2f((get_start().x + get_end().x) * 0.5f, (get_start().y + get_end().y) * 0.5f);
    }

    const sf::Vector2f Line::get_normal() const
    {
        sf::Vector2f normal(-(get_end().y - get_start().y), get_end().x - get_start().x);
        const float magnitude = std::sqrt((normal.x * normal.x) + (normal.y * normal.y));
        float scalar = 1;

        if (magnitude > 0) {
            scalar = 1.0f / magnitude;
        }

        normal *= scalar;

        return normal;
    }

    const sf::Vector2f Line::get_start() const
    {
        if (get_parent() != nullptr) {
            auto parent_pos = get_parent()->get_position();
            auto relative_pos = start + parent_pos;
            return relative_pos;
        }
        else {
            return start;
        }
    }

    const sf::Vector2f Line::get_end() const
    {
        if (get_parent() != nullptr) {
            auto parent_pos = get_parent()->get_position();
            auto relative_pos = end + parent_pos;
            return relative_pos;
        }
        else {
            return end;
        }
    }

    void Line::render(sf::RenderWindow& window)
    {
        // line_vertices[0].position = get_start();
        // line_vertices[1].position = get_end();
        // normal_vertices[0].position = get_center();
        // normal_vertices[1].position = get_center() + (get_normal() * 50.0f);

        window.draw(line_vertices, 2, sf::Lines);
        window.draw(normal_vertices, 2, sf::Lines);
    }

    Line::~Line() = default;
}