#pragma once
#include "gameScene.h"
#include "../utility/modulo.h"
#include <thread>

using namespace Blah;

namespace chessScene
{
    class VsIaScene : public GameScene {
    public:
        moduloStockfish::Modulo modulo;
        bool listening, needUpdate;
        char mo[5];

    public:
        VsIaScene();
        virtual void update();
        virtual void startup();
        virtual void dispose();
    };

}