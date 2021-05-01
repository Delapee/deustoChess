#include <iostream>
#include <thread>
#include <stdio.h>
#include <windows.h>
#include "clock.h"

using namespace chessClock;
using namespace std;

void hiloLlamado(Clock* c1){
    c1->setPaused(false);
    c1->initClock();
}

int main(){
    Clock* c1 = new Clock("hola", 0, 50, 500, 500);

    thread clockThread(hiloLlamado, c1);
    
    clockThread.join();

    Sleep(10000);

    clockThread.detach();
    c1->setPaused(true);
    
    return 0;
}