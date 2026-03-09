// Class for working with sprite-based shapes
#pragma once
#ifndef VMI_GAME_SPRITE_SHAPE_H
#define VMI_GAME_SPRITE_SHAPE_H

#include <map>
#include <string>
#include "Graphics.hpp"

#include "BoundingBox.hpp"
#include "Shape.hpp"

namespace vmi
{

    class SpriteShape : public Shape
    {
    public:
        SpriteShape() : Shape(), sprite(nullptr), texture(nullptr) {}
        SpriteShape(std::string filename);
        SpriteShape(const SpriteShape &other);
        SpriteShape &operator=(const SpriteShape &rtSide);
        ~SpriteShape() {
            if (sprite != nullptr)
            {
                delete sprite;
            }
        }

        // set the texture rectangle (which part of texture to show)
        void setTextureRectangle(Vector2d ul, Vector2d lr)
        {
            sf::IntRect rect({(int)ul.getX(), (int)ul.getY()},
                             {(int)(lr.getX() - ul.getX()), (int)(lr.getY() - ul.getY())});

            sprite->setTextureRect(rect);
        }

        // draw the sprite
        void draw(sf::RenderTarget &target, sf::RenderStates states) const
        {
#ifndef ZYBOOKS
            if (sprite != nullptr)
            {
                target.draw(*sprite, states);
            }
#endif
        }

        // get a bounding box around the shape
        const BoundingBox getBounds() const
        {
            // get SFML's representation of the bounds
            if (sprite == nullptr)
            {
                return BoundingBox();
            }
            else
            {
                sf::FloatRect box = sprite->getLocalBounds();

                // turn it into our bounding box
                return BoundingBox(Vector2d(box.position.x, box.position.y),
                                   Vector2d(box.position.x + box.size.x,
                                            box.position.y + box.size.y));
            }
        }

    private:
        sf::Sprite *sprite;   // SFML sprite
        sf::Texture *texture; // texture to use for sprite

        // map of all textures, indexed by filename
        static inline std::map<std::string, sf::Texture *> textures;
    };

    // Constructor
    // Input: filename = name of texture file
    inline SpriteShape::SpriteShape(std::string filename) : Shape(), sprite(nullptr)
    {
        // look to see if texture has already been loaded
        auto it = textures.find(filename);
        if (it != textures.end())
        {
            // texture was already loaded, so just re-use it
            texture = it->second;
        }
        else
        {
            // need to load texture and store it in map
            texture = new sf::Texture();
            if (texture->loadFromFile(filename))
            {
                // add it to the map
                textures.insert(std::pair<std::string, sf::Texture *>(filename, texture));
            }
            else
            {
                // couldn't load texture file, so un-do everything
                delete texture;
                texture = nullptr;
            }
        }

        // now initialize the SFML Sprite
        if (texture != nullptr)
        {
            // create a new sprite
            sprite = new sf::Sprite(*texture);
        }
    }

    // Copy constructor
    inline SpriteShape::SpriteShape(const SpriteShape &other) : sprite(nullptr)
    {
        texture = other.texture;

        // set the texture for my sprite
        if (texture != nullptr)
        {
            sprite = new sf::Sprite(*texture);
        }
    }

    // Assignment operator
    inline SpriteShape &SpriteShape::operator=(const SpriteShape &rtSide)
    {
        // make sure this isn't me
        if (this != &rtSide)
        {
            // copy his texture
            texture = rtSide.texture;

            // set the texture for my sprite
            if (texture != nullptr)
            {
                sprite->setTexture(*texture);
            }
        }

        return *this;
    }

} // namespace vmi

#endif