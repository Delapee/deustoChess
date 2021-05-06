
#include "piece.h"
#include <blah.h>

namespace chessSprite
{

    Piece::Piece(const String& texturePath, int x, int y)
    {
        this->texture = Texture::create(texturePath);
        this->x = x;
        this->y = y;
    }

    void Piece::draw(Batch *batch)
    {
        batch->tex(this->texture, Vec2(this->x, this->y));
    }
}