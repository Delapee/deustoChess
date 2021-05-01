#include "sprite.h"

namespace chessSprite
{
    Sprite::Sprite(string name, char color, int x, int y, const string& texturePath)
    {
        this->name = name;
        this->color = color;
        this->x = x;
        this->y = y;
        this->texture = Texture::create(texturePath);
        this->state = IDLE;
        this->touched = false;
    }

    Sprite::Sprite(const Sprite& copy)
    {
        this->name = copy.name;
        this->color = copy.color;
        this->x = copy.x;
        this->y = copy.y;
        this->texture = copy.texture;
        this->state = copy.state;
        this->touched = copy.touched;
    }

    Sprite::~Sprite()
    {
        
    }

    const string Sprite::getName()
    {
        return this->name;
    }

    const char Sprite::getColor()
    {
        return this->color;
    }

    int Sprite::getX() {
        return this->x;
    }

    void Sprite::setX(int x) {
        this->x = x;
    }

    int Sprite::getY() {
        return this->y;
    }

    void Sprite::setY(int y) {
        this->y = y;
    }

    const TextureRef Sprite::getTexture()
    {
        return this->texture;
    }

    State Sprite::getState()
    {
        return this->state;
    }

    void Sprite::setState(State state)
    {
        this->state = state;
    }

    bool Sprite::getTouched()
    {
        return this->touched;
    }

    void Sprite::setTouched(bool touched)
    {
        this->touched = touched;
    }
}
