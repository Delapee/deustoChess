#include "modulo.h"
#include <iostream>

#include "../../dependencies/stockfish/src/bitboard.h"
#include "../../dependencies/stockfish/src/endgame.h"
#include "../../dependencies/stockfish/src/position.h"
#include "../../dependencies/stockfish/src/psqt.h"
#include "../../dependencies/stockfish/src/search.h"
#include "../../dependencies/stockfish/src/syzygy/tbprobe.h"
#include "../../dependencies/stockfish/src/thread.h"
#include "../../dependencies/stockfish/src/tt.h"
#include "../../dependencies/stockfish/src/uci.h"

using namespace Stockfish;

#define DEFAULT_BESTMOVE ""
#define DEFAULT_DONE false

namespace moduloStockfish
{
	string Modulo::bestMove = DEFAULT_BESTMOVE;
	bool Modulo::done = DEFAULT_DONE;
	char** Modulo::argv = NULL;

	Modulo::Modulo()
	{
		this->comd = "position startpos moves";
		initSF();
	}

	Modulo::~Modulo()
	{

	}

	void Modulo::setBestMove(string bestMove)
	{
		Modulo::bestMove = bestMove;
	}

	string Modulo::getBestMove()
	{
		return Modulo::bestMove;
	}

	void Modulo::setDone(bool done)
	{
		Modulo::done = done;
	}

	bool Modulo::getDone()
	{
		return Modulo::done;
	}

	void Modulo::setArgv(char** cmd)
	{
		Modulo::argv = new char* [1];
		Modulo::argv[0] = new char[strlen(cmd[0]) + 1];
		strcpy(Modulo::argv[0], cmd[0]);
	}

	void Modulo::initSF() 
	{
		CommandLine::init(1, Modulo::argv);
		UCI::init(Options);
		Tune::init();
		PSQT::init();
		Bitboards::init();
		Position::init();
		Bitbases::init();
		Endgames::init();
		Threads.set(size_t(Options["Threads"]));
		Search::clear(); // After threads are up
		Eval::NNUE::init();
		UCI::initLoop();
	}

	char* Modulo::getNextMove(char* lastMove)
	{
		Modulo::done = false;
		char newMove[5];
		string move = lastMove;
		this->comd = this->comd + " " + move;

		UCI::loop(this->comd);
		UCI::loop("go depth 12");
		while (!Modulo::done);

		string best = getBestMove();
		this->comd = this->comd + " " + best;

		for (int i = 0; i < best.length(); i++)
		{
			newMove[i] = best[i];
		}
		newMove[4] = '\0';

		return newMove;
	}

	void Modulo::endModulo()
	{
		UCI::loop("quit");
		Threads.set(0);
	}
}
