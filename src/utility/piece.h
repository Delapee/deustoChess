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
        static bool hover;
        bool grabbed;
        std::string pos;

    public:
        Piece(const String& texturePath, std::string pos);
        void draw(Batch *batch, char c);
        void drawMouse(Batch* batch);
        std::string getPos();
        void setPos(std::string pos);
        bool getHover();
        void static setHover(bool bo);
        bool isGrabbed();
        void setGrabbed(bool grabbed);
    };
}
