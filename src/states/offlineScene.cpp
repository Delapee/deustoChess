#include "offlineScene.h"

namespace chessScene
{
	OfflineScene::OfflineScene():GameScene() {

	}

	void OfflineScene::startup() {
		App::fullscreen(true);
		background = Texture::create("data/img/background/background.png");
		a = play::Game('b');
		loadPieces();
		loadPoisitions();
	}

    void  OfflineScene::update() {
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

			if (getColor(a.getBo(), piece) == a.getPlayer() &&
				isMove(a.getBo(), mo, 0) == 1 && isNailed(a.getBo(), mo) == 0)
			{
				movePiece(a.getBo(), mo);
				checkCastle(a.getBo());
				isPromote(a.getBo());
				loadPoisitions();
				if (isCheck(a.getBo(), a.getPlayer()) == 2) App::exit();
				a.setPlayer((a.getPlayer() == 'b') ? 'n' : 'b');
			}

			selec->setGrabbed(false);
			selec->setHover(false);
			selec = NULL;
		}
    }
    
    void OfflineScene::dispose() {
		for (auto& piece : board) delete piece;
    }
}