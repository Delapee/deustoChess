#pragma once

#include "blah.h"
#include <iostream>
#include <string>
#include "sprite.h"

using namespace Blah;


namespace chessSprite
{
    class Piece:public Sprite {
    private:
        TextureRef texture;
        int x, y;
        static bool hover;
        bool grabbed;

    public:
        Piece(const String& texturePath, int x, int y);
        void draw(Batch *batch) override;
        bool getHover();
        void setHover();
        bool isGrabbed();
        void setGrabbed(bool Grabbed);
    };
}
