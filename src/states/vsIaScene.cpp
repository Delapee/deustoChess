#include "vsIaScene.h"
#include "../utility/chess.h"
#include <thread> 

namespace chessScene
{
	VsIaScene::VsIaScene():GameScene() {

	}

	void VsIaScene::startup() {
		App::fullscreen(true);
		a = play::Game('b');

		if (a.getPlayer() == 'b')
		{
			listening = true;
			needUpdate = false;
		}

		background = Texture::create("background.png");
		modulo = moduloStockfish::Modulo();
		modulo.initSF();
		loadPieces();
		loadPoisitions();
	}

	void  VsIaScene::update() {
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
			strcpy(mo, move.c_str());
			char piece[2] = { mo[0] , mo[1] };

			if (getColor(a.getBo(), piece) == a.getPlayer() &&
				isMove(a.getBo(), mo, 0) == 1 && isNailed(a.getBo(), mo) == 0)
			{
				movePiece(a.getBo(), mo);
				checkCastle(a.getBo());
				isPromote(a.getBo());
				loadPoisitions();
				if (isCheck(a.getBo(), a.getPlayer()) == 2) App::exit();
				listening = false;
			}
			selec->setGrabbed(false);
			selec->setHover(false);
			selec = NULL;
		}
		/*
		if (!listening) {
			listening = true;
			std::thread t(&reciveMove,this);
			t.detach();
		}
		*/
		if (needUpdate) {
			loadPoisitions();
			if (isCheck(a.getBo(), (a.getPlayer() == 'b') ? 'n' : 'b') == 2) App::exit();
			needUpdate = false;
		}
	}

	void VsIaScene::dispose() {
		for (auto& piece : board) delete piece;
	}

	


}