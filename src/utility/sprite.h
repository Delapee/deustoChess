#pragma once

#include "blah.h"
#include <iostream>
#include <string>
using namespace Blah;

namespace chessSprite 
{
    class Sprite {
        private:
            int x, y;
            
        protected:
            Sprite() = default;
            
        public:
            TextureRef texture;
            ~Sprite();
            TextureRef getTexture();
            int getX();
            void setX(int x);
            int getY();
            void setY(int y); 
            virtual void draw(Batch *batch);
            
    };


}

