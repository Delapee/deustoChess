#ifndef _GAMEMODE_
#define _GAMEMODE_


#include "../utility/chess.h"
#include <iostream>


namespace play {
    class Game {
    private:
        Board bo;
        char player;
        std::string movement;
        std::string winner;

    public:
        Game();
        Game(char p);
        Board* getBo();
        void setBo(Board b);
        char getPlayer();
        void setPlayer(char p);
        std::string getMovement();
        void setMovement(std::string m);
        std::string getWinner();

        bool updateMovement();
        bool isFisnish();

    };

    void playOffline();
    void playOnline();
}
#endif