// Text that can be drawn to a window
#pragma once
#ifndef VMI_GAME_TEXT_H
#define VMI_GAME_TEXT_H

#include "Graphics.hpp"
#include <string>
#include <cstdlib>

#include "Vector2d.hpp"
#include "Color.hpp"

namespace vmi {

#ifndef ZYBOOKS
    static inline sf::Font* defaultFont = new sf::Font("./VMIGameEngine/resource/sansation.ttf");
#else
    static inline sf::Font* defaultFont;
#endif

class Text
{
public:
    Text() : shape(*defaultFont, ""), text(""), 
        position(Vector2d()), characterSize(30), fillColor(Color::White), 
        outlineColor(Color::Transparent) {
    }

    Text(std::string _text, Vector2d _position) : shape(*defaultFont, _text), text(_text), position(_position) {

    }
    ~Text() {}

    // draw the text
    void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        sf::Transform transform;
        transform.translate(sf::Vector2f((float)position.getX(), (float) position.getY()));
        states.transform = transform;
        target.draw(shape, states);
    }

    // setters
    void setText(std::string newText) {
        text = newText;
        shape.setString(text);
    }
    void setCharacterSize(unsigned int newSize) {
        characterSize = newSize;
        shape.setCharacterSize(characterSize);
    }
    void setPosition(const Vector2d newPosition) { position = newPosition; }
    void setFill(const Color newColor) {
        fillColor = newColor;
        shape.setFillColor(sf::Color(static_cast<std::uint32_t>(fillColor)));
    }
    void setOutline(const Color newColor) {
        outlineColor = newColor;
        shape.setOutlineColor(sf::Color(static_cast<std::uint32_t>(outlineColor)));
    }

private:
    std::string text;               // text that is displayed
    unsigned int characterSize;     // size of characters
    Vector2d position;              // location in window
    Color fillColor;                // color used to fill the text
    Color outlineColor;             // color used to outline the text

    sf::Text shape;                 // SFML shape


};

} // namespace vmi

#endif // TEXT_H