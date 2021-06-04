#pragma once

#include <string>

using namespace std;

namespace moduloStockfish
{
	class Modulo
	{
	private:
		static char** argv;
		static string bestMove;
		static bool done;

		string comd;

	public:
		Modulo();
		~Modulo();

		static void setArgv(char** cmd);
		static void setBestMove(string bestMove);
		static string getBestMove();
		static void setDone(bool done);
		static bool getDone();
		
		void initSF();
		char* getNextMove(char* lastMove);
		void endModulo();
	};
}
