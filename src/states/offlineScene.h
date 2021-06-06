#pragma once
#include "gameScene.h"

using namespace Blah;

namespace chessScene
{
    class OfflineScene: public GameScene {
    public:
        OfflineScene();
        virtual void update();
        virtual void startup();
        virtual void dispose();
    };

}