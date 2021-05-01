#pragma once

#include "blah.h"
#include <iostream>
#include <string>
using namespace Blah;
using namespace std;

namespace chessSprite 
{
    class Sprite {
        private:
            enum State {
                IDLE, CHOOSING
            };

            const string name;
            const char color;
            int x, y;
            const TextureRef texture;
            State state;
            bool touched;

        public:
            Sprite(string name, char color, int x, int y, const string& texturePath);
            Sprite(const Sprite& copy);
            ~Sprite();

            const string getName();
            const char getColor();
            int getX();
            void setX(int x);
            int getY();
            void setY(int y);
            const TextureRef getTexture();
            State getState();
            void setState(State state);
            bool getTouched();
            void setTouched(bool touched);
    };
}

