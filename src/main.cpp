#include <blah.h>
#include <unordered_map>
#include "utility/piece.h"
#include "game/gamemodes.h"
#include "utility/chess.h"
#include <iostream>
#include <string>
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
	pieces.insert({"Pb", "../../../data/img/piece/Pb.png"});
	pieces.insert({"Tb", "../../../data/img/piece/Tb.png"});
	pieces.insert({"Cb", "../../../data/img/piece/Cb.png"});
	pieces.insert({"Ab", "../../../data/img/piece/Ab.png"});
	pieces.insert({"Db", "../../../data/img/piece/Db.png"});
	pieces.insert({"Rb", "../../../data/img/piece/Rb.png"});

	// Piezas negras
	pieces.insert({"Pn", "../../../data/img/piece/Pn.png"});
	pieces.insert({"Tn", "../../../data/img/piece/Tn.png"});
	pieces.insert({"Cn", "../../../data/img/piece/Cn.png"});
	pieces.insert({"An", "../../../data/img/piece/An.png"});
	pieces.insert({"Dn", "../../../data/img/piece/Dn.png"});
	pieces.insert({"Rn", "../../../data/img/piece/Rn.png"});
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

void startup()
{
	App::fullscreen(true);
	background = Texture::create("../../../data/img/background/background.png");
	a = play::Game('b');
	loadPieces();
	loadPoisitions();
}

std::string getMouseBox() {
	Vec2 m = Input::mouse();
	int x = m.x;
	int y = m.y;
	char a [3] = "no";

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
		a[0] = 'a' + count;
	
		count = 0;
		for (size_t i = 0; i < 8; i++)
		{
			if (90 + 115 * i < y)
			{
				count++;
			}
		}
		a[1] = '9' - count;
		a[1] = '0' + count;
	}

	return a;
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

		if (getColor(a.getBo(), piece) == a.getPlayer() && isMove(a.getBo(), mo, 0) && isNailed(a.getBo(), mo) == 0) {
			movePiece(a.getBo(), mo);
			checkCastle(a.getBo());
			isPromote(a.getBo());
			loadPoisitions();
			a.setPlayer((a.getPlayer() == 'b') ? 'n' : 'b');			
		}

		selec->setGrabbed(false);
		selec->setHover(false);
		selec = NULL;
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
			board[i]->draw(&batch);
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
}

int main()
{
	//play::playOffline();

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

	App::run(&config);
	return 0;
}