#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include "clock.h"
using namespace std;

#define DEFAULT_NAME ""
#define DEFAULT_MIN 10
#define DEFAULT_SEC 0
#define DEFAULT_X 0
#define DEFAULT_Y 0
#define DEFAULT_PAUSED true

namespace chessClock
{
    Clock::Clock()
    {
        this->name = DEFAULT_NAME;
        this->min = DEFAULT_MIN;
        this->sec = DEFAULT_SEC;
        this->x = DEFAULT_X;
        this->y = DEFAULT_Y;
        this->paused = DEFAULT_PAUSED;
    }

    Clock::Clock(string name, unsigned int min, unsigned int sec, int x, int y)
    {
        this->name = name;
        this->min = min;
        this->sec = sec;
        this->x = x;
        this->y = y;
        this->paused = DEFAULT_PAUSED;
    }

    Clock::Clock(const Clock& copy)
    {
        this->name = copy.name;
        this->min = copy.min;
        this->sec = copy.sec;
        this->x = copy.x;
        this->y = copy.y;
        this->paused = copy.paused;
    }

    Clock::~Clock()
    {

    }

    string Clock::getName()
    {
        return this->name;
    }

    unsigned int Clock::getMin()
    {
        return this->min;
    }

    unsigned int Clock::getSec()
    {
        return this->sec;
    }

    int Clock::getX()
    {
        return this->x;
    }

    void Clock::setX(int x)
    {
        this->x = x;
    }

    int Clock::getY()
    {
        return this->y;
    }

    void Clock::setY(int y)
    {
        this->y = y;
    }

    bool Clock::getPaused()
    {
        return this->paused;
    }

    void Clock::setPaused(bool paused)
    {
        this->paused = paused;
    }

    void Clock::initClock() {

        while (!this->paused) {


            if (this->min == 0) {
                cout << "00:" << this->sec << endl;
            }
            else {
                cout << this->min << ":" << this->sec << endl;
            }

            if (this->sec == 0)
            {
                if (this->min != 0)
                {
                    this->sec = 60;
                    this->min--;
                }
            }

            if (this->min == 0) {
                if (this->sec == 0) {
                    this->paused = false;
                    break;
                }
            }

            Sleep(1000);
            this->sec--;
            system("cls");

        }

    }
}