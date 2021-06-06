#include "gameScene.h"

#include "../utility/chess.h"
#include <blah.h>
#include <windows.h>


namespace chessScene
{

	void GameScene::getScreenResolution(int& width, int& height) {
		width = (int)GetSystemMetrics(SM_CXSCREEN);
		height = (int)GetSystemMetrics(SM_CYSCREEN);
	}

	void GameScene::loadPieces() {
		selec = NULL;

		// Piezas blancas
		pieces.insert({ "Pb", "data/img/piece/Pb.png" });
		pieces.insert({ "Tb", "data/img/piece/Tb.png" });
		pieces.insert({ "Cb", "data/img/piece/Cb.png" });
		pieces.insert({ "Ab", "data/img/piece/Ab.png" });
		pieces.insert({ "Db", "data/img/piece/Db.png" });
		pieces.insert({ "Rb", "data/img/piece/Rb.png" });

		// Piezas negras
		pieces.insert({ "Pn", "data/img/piece/Pn.png" });
		pieces.insert({ "Tn", "data/img/piece/Tn.png" });
		pieces.insert({ "Cn", "data/img/piece/Cn.png" });
		pieces.insert({ "An", "data/img/piece/An.png" });
		pieces.insert({ "Dn", "data/img/piece/Dn.png" });
		pieces.insert({ "Rn", "data/img/piece/Rn.png" });
	}

	void GameScene::loadPoisitions() {
		for (auto& piece : board) delete piece;
		board.clear();
		for (size_t i = 0; i < 64; i++)
		{
			std::string aux = (a.getBo())->panel[i];

			if (aux.compare("  ") != 0 && aux.compare(" b") && aux.compare(" n")) {
				char ab[3];
				ab[0] = getColumnId(i); ab[1] = '0' + getRowId(i); ab[2] = '\0';
				chessSprite::Piece* p = new chessSprite::Piece(pieces[aux], ab);
				board.push_back(p);
			}
		}
	}

	std::string GameScene::getMouseBox() {
		Vec2 m = Input::mouse();
		int x = m.x;
		int y = m.y;
		char box[3] = "no";

		if ((x > 455 && x < 455 + 115.5 * 8) && (y > 90 && y < 90 + 115.5 * 8))
		{
			int count = -1;
			for (size_t i = 0; i < 8; i++)
			{
				if (455 + 115.5 * i < x)
				{
					count++;
				}
			}
			(a.getPlayer() == 'b') ? box[0] = 'a' + count : box[0] = 'h' - count;

			count = 0;
			for (size_t i = 0; i < 8; i++)
			{
				if (90 + 115 * i < y)
				{
					count++;
				}
			}
			(a.getPlayer() == 'b') ? box[1] = '9' - count : box[1] = '0' + count;
		}

		return box;
	}

	void GameScene::render()
	{
		App::backbuffer->clear(Color::black);
		auto transform = Mat3x2::create_transform(Vec2::zero, Vec2::zero, Vec2::one, 0);
		batch.push_matrix(transform);
		batch.tex(background, Vec2(0, 0), Color::white);

		for (int i = 0; i < board.size(); i++)
		{
			if (!board[i]->isGrabbed()) {
				board[i]->draw(&batch, a.getPlayer());
			}
		}

		if (selec != NULL) {
			selec->drawMouse(&batch);
		}

		//////////////////////////////////////////
		batch.pop_matrix();
		batch.render();
		batch.clear();
	}


	GameScene::GameScene() {

	}

	play::Game* GameScene::getGame() {
		return &a;
	}
}