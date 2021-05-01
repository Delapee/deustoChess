#pragma once

#include <iostream>
#include <string>
using namespace std;

namespace chessClock
{
	class Clock
	{
	private:
		string name;
		unsigned int min, sec;
		int x, y;
		bool paused;

	public:
		Clock();
		Clock(string name, unsigned int min, unsigned int sec, int x, int y);
		Clock(const Clock& copy);
		~Clock();

		string getName();
		unsigned int getMin();
		unsigned int getSec();
		int getX();
		void setX(int x);
		int getY();
		void setY(int y);
		bool getPaused();
		void setPaused(bool paused);

		void initClock();
	};
}