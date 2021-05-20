#include <blah.h>
#include <unordered_map>
#include "utility/piece.h"
#include "game/gamemodes.h"
#include "utility/chess.h"
#include "utility/sconector.h"
#include <iostream>
#include <string>
#include <thread> 
#if WIN32
#include <windows.h>
#else
#include <X11/Xlib.h>
#endif
using namespace Blah;

Batch batch;
TextureRef background;
play::Game a;
std::unordered_map<std::string, String> pieces;
std::vector<chessSprite::Piece*> board;
chessSprite::Piece *selec;
Sconector *sc;
bool listening , needUpdate;
std::thread t1;

void getScreenResolution(int& width, int& height) {
	#if WIN32
		width = (int)GetSystemMetrics(SM_CXSCREEN);
		height = (int)GetSystemMetrics(SM_CYSCREEN);
	#else
		Display* disp = XOpenDisplay(NULL);
		Screen* scrn = DefaultScreenOfDisplay(disp);
		width = scrn->width;
		height = scrn->height;
	#endif
}

void loadPieces() {
	selec = NULL;

	// Piezas blancas
	pieces.insert({ "Pb", "piezas/Pb.png" });
	pieces.insert({ "Tb", "piezas/Tb.png" });
	pieces.insert({ "Cb", "piezas/Cb.png" });
	pieces.insert({ "Ab", "piezas/Ab.png" });
	pieces.insert({ "Db", "piezas/Db.png" });
	pieces.insert({ "Rb", "piezas/Rb.png" });

	// Piezas negras
	pieces.insert({ "Pn", "piezas/Pn.png" });
	pieces.insert({ "Tn", "piezas/Tn.png" });
	pieces.insert({ "Cn", "piezas/Cn.png" });
	pieces.insert({ "An", "piezas/An.png" });
	pieces.insert({ "Dn", "piezas/Dn.png" });
	pieces.insert({ "Rn", "piezas/Rn.png" });
}

void loadPoisitions() {
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

void reciveMove() {
	sc->listendata();
	char move[5]; strcpy(move, sc->getData().c_str());
	if (isMove(a.getBo(), move, 0) == 1) movePiece(a.getBo(), move);
	sc->validPriority();
	checkCastle(a.getBo());
	isPromote(a.getBo());
	needUpdate = true;
}


void startup()
{
	App::fullscreen(false);
 	background = Texture::create("background.png");
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

std::string getMouseBox() {
	Vec2 m = Input::mouse();
	int x = m.x;
	int y = m.y;
	char box [3] = "no";

	if ((x > 455 && x < 455 + 115.5 * 8) && (y > 90 && y < 90 + 115.5 * 8))
	{
		int count = -1;
		for (size_t i = 0; i < 8; i++)
		{
			if (455 + 115.5 *i < x)
			{
				count++;
			}
		}
		(a.getPlayer() == 'b') ? box[0] = 'a' + count : box[0] = 'h' - count;
		//box[0] = 'a' + count;

		count = 0;
		for (size_t i = 0; i < 8; i++)
		{
			if (90 + 115 * i < y)
			{
				count++;
			}
		}
		(a.getPlayer() == 'b') ? box[1] = '9' - count : box[1] = '0' + count;
		//box[1] = '9' - count;
	}

	return box;
}

void update()
{	
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
		}

		selec->setGrabbed(false);
		selec->setHover(false);
		selec = NULL;
	}

	
	if (!sc->getPriority() && !listening) {
		listening = true;
		std::thread t(reciveMove);
		t.detach();
	}

	if (needUpdate) {
		loadPoisitions();
		needUpdate = false;
	}

}

void render()
{
	App::backbuffer->clear(Color::black);
	auto transform = Mat3x2::create_transform(Vec2::zero, Vec2::zero, Vec2::one, 0);
	batch.push_matrix(transform);
	
	// AQUI DIBUJO TODO
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



void dispose()
{
	for (auto& piece : board) delete piece;
	delete sc;
}

int main()
{
	int width, height;
	getScreenResolution(width, height);

	Config config;
	config.name = "Deusto Chess";
	config.width = width;
	config.height = height;
	config.target_framerate = 120;
	config.on_startup = startup;
	config.on_render = render;
	config.on_update = update;
	config.on_shutdown = dispose;

	char ip[20];
	std::cout << "Marca la ip del servidor: ";
	std::cin >> ip;
	sc = new Sconector(ip, 8001);

	App::run(&config);
	return 0;
}