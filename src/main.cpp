#include <blah.h>
#include <unordered_map>
#include "utility/piece.h"
#include "game/gamemodes.h"
#include "utility/chess.h"
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

	for (size_t i = 0; i < 64; i++)
	{
		std::string aux = (a.getBo())->panel[i];
		std::string aux2 = "" + getColumnId(i) + getRowId(i);
		if (aux.compare("  ") != 0) {
			chessSprite::Piece* p = new chessSprite::Piece(pieces[aux], 900, 900);
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

void render()
{
	App::backbuffer->clear(Color::black);
	auto transform = Mat3x2::create_transform(Vec2::zero, Vec2::zero, Vec2::one, 0);
	batch.push_matrix(transform);
	// AQUI DIBUJO TODO
	batch.tex(background, Vec2(0, 0), Color::white);

	for (int i = 0; i < board.size(); i++)
	{
		board[i]->draw(&batch);
	}


	//////////////////////////////////////////
	batch.pop_matrix();
	batch.render();
	batch.clear();
}

void update()
{

}

void dispose()
{
	for (auto& piece : pieces) delete piece.second;
}

int main()
{
	int width, height;
	getScreenResolution(width, height);

	Config config;
	config.name = "Deusto Chess";
	config.width = width;
	config.height = height;
	config.target_framerate = 60;
	config.on_startup = startup;
	config.on_render = render;
	config.on_update = update;
	config.on_shutdown = dispose;

	App::run(&config);
	return 0;
}