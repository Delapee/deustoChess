#include "sprite.h"

namespace chessSprite
{

    Sprite::~Sprite()
    {
        
    }

    TextureRef Sprite::getTexture()
    {
        return this->texture;
    }

    int Sprite::getX() 
    {
        return this->x;
    }

    void Sprite::setX(int x) 
    {
        this->x = x;
    }

    int Sprite::getY() 
    {
        return this->y;
    }

    void Sprite::setY(int y) 
    {
        this->y = y;
    }
    void Sprite::draw(Batch* batch)
    {
        batch->tex(this->texture, Vec2(this->x, this->y));
    }
}
