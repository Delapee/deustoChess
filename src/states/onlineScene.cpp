#include "onlineScene.h"
#include "../utility/sconector.h"

namespace chessScene
{

    OnlineScene::OnlineScene():GameScene() {

    }

    void OnlineScene::update() {
		if (Input::down(MouseButton::Left) && (!board[0]->getHover())) {

			for (size_t i = 0; i < board.size(); i++)
			{
				if (board[i]->getPos().compare(getMouseBox()) == 0)
				{
					board[i]->setGrabbed(true);
					board[i]->setHover(true);
					selec = board[i];
					break;
				}
			}
		}
		else if (!Input::down(MouseButton::Left) && board[0]->getHover()) {

			std::string move = selec->getPos() + "" + getMouseBox();
			char mo[5]; strcpy(mo, move.c_str());
			char piece[2] = { mo[0] , mo[1] };

			if (sc->getPriority() && getColor(a.getBo(), piece) == a.getPlayer()
				&& isMove(a.getBo(), mo, 0) == 1 && isNailed(a.getBo(), mo) == 0)
			{
				movePiece(a.getBo(), mo);
				sc->setData(mo); sc->sendData();
				checkCastle(a.getBo());
				isPromote(a.getBo());
				loadPoisitions();
				listening = false;
				if (isCheck(a.getBo(), a.getPlayer()) == 2) App::exit();
			}

			selec->setGrabbed(false);
			selec->setHover(false);
			selec = NULL;
		}


		if (needUpdate) {
			loadPoisitions();
			needUpdate = false;
			if (isCheck(a.getBo(), (a.getPlayer() == 'b') ? 'n' : 'b') == 2) {
				App::exit();
				sc->setData("QUIT\0"); 
				sc->sendData();
			}
		}
    }

    void OnlineScene::startup() {
		char ip[20];
		std::cout << "Marca la ip del servidor: ";
		std::cin >> ip;
		sc = new Sconector(ip, 8001);

		App::fullscreen(true);
		background = Texture::create("data/img/background/background.png");
		needUpdate = false;
		if (sc->connectServer() == true) {
			sc->listendata();
			if (sc->getData() == "Blanco") {
				a = play::Game('b');
				listening = true;
				sc->validPriority();
			}
			else {
				listening = false;
				a = play::Game('n');
			}
		}
		else
		{
			App::exit();
		}

		loadPieces();
		loadPoisitions();
    }

    void OnlineScene::dispose() {
        for (auto& piece : board) delete piece;
        delete sc;
    }


}