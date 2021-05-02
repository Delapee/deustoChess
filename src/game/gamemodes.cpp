#include "gamemodes.h"
#include "../utility/sconector.h"
#include <iostream>

using namespace std;

namespace play {


	Game::Game()
	{
		prepareBoard(&(this->bo));
		loadPanel(&(this->bo), sPos);
		this->player = 'b';
		this->movement = "";
		this->winner = "";
	}

	Game::Game(char p)
	{
		prepareBoard(&(this->bo));
		loadPanel(&(this->bo), sPos);
		this->player = p;
		this->movement = "";
		this->winner = "";
	}

	Board* Game::getBo()
	{
		return &this->bo;
	}

	void Game::setBo(Board b)
	{
		this->bo = b;
	}

	char Game::getPlayer()
	{
		return player;
	}

	void Game::setPlayer(char p)
	{
		this->player = p;
	}

	std::string Game::getMovement()
	{
		return this->movement;
	}

	void Game::setMovement(std::string m)
	{
		this->movement = m;
	}

	string Game::getWinner()
	{
		return this->winner;
	}

	bool Game::updateMovement()
	{
		int submit = 1;
		char mo[5];
		do
		{
			system("cls");
			printBoard(&this->bo, (this->player == 'b') ? 0 : 1);
			cout << "\n" << endl;
			cout << "\tCasilla Inicio + fin Ej -> e2e4" << endl;
			cout << "\tFF Para rendirse" << endl;
			cout << "\tSeleccione una jugada: ";
			cin >> mo;
			char piece[2] = { mo[0] , mo[1] };

			if (mo[0] == 'F' && mo[1] == 'F')
			{
				this->movement = "QUIT";
				return true;
			}
			else if (getColor(&this->bo, piece) == this->player && isMove(&this->bo, mo, 0) && isNailed(&this->bo, mo) == 0) {
				movePiece(&this->bo, mo);
				this->movement = mo;
				return true;
			}

		} while (true);

	}

	bool Game::isFisnish()
	{
		if (isCheck(&this->bo, 'n') == 2) {
			this->winner = "Blanco";
			return true;
		}
		if (isCheck(&this->bo, 'b') == 2) {
			return true;
		}
		return false;
	}

	void playOffline()
	{
		Game a = Game('b');
		while (!a.isFisnish())
		{
			a.updateMovement();
			checkCastle(a.getBo());
			isPromote(a.getBo());
			(a.getPlayer() == 'b') ? a.setPlayer('n') : a.setPlayer('b');
		}

		cout << a.getWinner();
	}

	void playOnline()
	{
		char ip[20];
		cout << "Marca la ip del servidor: ";
		cin >> ip;

		Sconector sc = Sconector(ip, 8001);
		Game a;

		if (sc.connectServer() == true) {
			sc.listendata();
			if (sc.getData() == "Blanco") {
				a = Game('b');
				sc.validPriority();
			}
			else {
				a = Game('n');
			}

			while (!a.isFisnish())
			{
				if (sc.getPriority() == true) {
					a.updateMovement();
					sc.setData(a.getMovement());
					sc.sendData();
				}
				else {
					sc.listendata();
					char move[5];
					strcpy(move, sc.getData().c_str());
					movePiece(a.getBo(), move);
					sc.validPriority();
				}
				system("cls");
				printBoard(a.getBo(), (a.getPlayer() == 'b') ? 0 : 1);
				checkCastle(a.getBo());
				isPromote(a.getBo());
			}
			cout << a.getWinner();
		}
	}
}