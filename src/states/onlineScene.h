#pragma once
#include "gameScene.h"
#include "../utility/sconector.h"
#include <thread>

using namespace Blah;

namespace chessScene
{
    class OnlineScene : public GameScene {
    public:
        Sconector* sc;
        bool listening, needUpdate;
        char mo[5];
        OnlineScene();
        virtual void update();
        virtual void startup();
        virtual void dispose();
    };

}