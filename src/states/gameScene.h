#pragma once

#include "blah.h"
#include "../game/gamemodes.h"
#include "../utility/piece.h"
#include <string>

using namespace Blah;

namespace chessScene
{
    class GameScene {
    protected:
        Batch batch;
        TextureRef background;
        play::Game a;
        std::unordered_map<std::string, String> pieces;
        std::vector<chessSprite::Piece*> board;
        chessSprite::Piece* selec;
        
    public:
        GameScene();
        play::Game* getGame();
        void getScreenResolution(int& width, int& height);
        void loadPieces();
        void loadPoisitions();
        std::string getMouseBox();
        void render();

        virtual void update() = 0;
        virtual void startup() = 0;
        virtual void dispose() = 0;
    };

}