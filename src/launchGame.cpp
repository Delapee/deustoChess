#include "launchGame.h"
#include <blah.h>
#include "states/gameScene.h"
#include "states/offlineScene.h"
#include "states/onlineScene.h"
#include "states/vsIaScene.h"

using namespace Blah;

chessScene::OfflineScene offline;
chessScene::OnlineScene online;
chessScene::VsIaScene vsIa;

int mode;

void reciveMove() {
	char move[5]; strcpy(move, vsIa.modulo.getNextMove(vsIa.mo));
	if (isMove(vsIa.getGame()->getBo(), move, 0) == 1) movePiece(vsIa.getGame()->getBo(), move);
	checkCastle(vsIa.getGame()->getBo());
	isPromote(vsIa.getGame()->getBo());
	vsIa.needUpdate = true;
}

void reciveMoveServer() {
	online.sc->listendata();
	char move[5]; strcpy(move, online.sc->getData().c_str());
	if (isMove(online.getGame()->getBo(), move, 0) == 1) movePiece(online.getGame()->getBo(), move);
	online.sc->validPriority();
	checkCastle(online.getGame()->getBo());
	isPromote(online.getGame()->getBo());
	online.needUpdate = true;
}

void startup()
{
	switch (mode)
	{
	case 1:
		offline.startup();
		break;
	case 2:
		online.startup();
		break;
	case 3:
		vsIa.startup();
		break;
	}
}

void update()
{
	switch (mode)
	{
	case 1:
		offline.update();
		break;
	case 2:
		online.update();
		if (!online.sc->getPriority() && !online.listening) {
			online.listening = true;
			std::thread t(reciveMoveServer);
			t.detach();
		}
		break;
	case 3:
		vsIa.update();
		if (!vsIa.listening) {
			vsIa.listening = true;
			std::thread t(reciveMove);
			t.detach();
		}
		break;
	}


}

void render()
{
	switch (mode)
	{
	case 1:
		offline.render();
		break;
	case 2:
		online.render();
		break;
	case 3:
		vsIa.render();
		break;
	}
}

void dispose()
{
	switch (mode)
	{
	case 1:
		offline.dispose();
		break;
	case 2:
		online.dispose();
		break;
	case 3:
		vsIa.dispose();
		break;
	}
}




void launch(int start)
{
	mode = start;
	int width, height;

	vsIa.getScreenResolution(width, height);
	

	Config config;
	config.name = "Deusto Chess";
	config.width = width;
	config.height = height;
	config.target_framerate = 120;
	config.on_startup = startup;
	config.on_render = render;
	config.on_update = update;
	config.on_shutdown = dispose;

	App::run(&config);
}