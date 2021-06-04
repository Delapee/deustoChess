#include "menu.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void initMenu() 
{
    system("cls");
    int opcion;

    do
    {
        opcion = selectMenuOption();
        selectOption(opcion);
    } while (opcion != 0);
}

int selectMenuOption()
{
    string option;
    bool rigth = false;
    
    do
    {
        cout << "\n+---------------------------------------------+\n" <<
                "|               MENU DE INICIO                |\n" <<
                "|---------------------------------------------|\n" <<
                "| 1. Jugar Local                              |\n" <<
                "| 2. Jugar Online                             |\n" <<
                "| 3. Jugar contra IA                          |\n" <<
                "| 4. Puzzles Rush                             |\n" <<
                "| 0. Salir                                    |\n" <<
                "+---------------------------------------------+" << endl;

        cout << "\nSelecciona una opcion: ";
        cin >> option;

        if (option.length() != 1 || option.at(0) - '0' < 0 || option.at(0) - '0' > 4)
        {
            system("cls");
            cout << "\nValor incorrecto, debe estar entre 0 y 4." << endl;
        }
        else rigth = true;
    } while (!rigth);

    return stoi(option);
}

void selectOption(int option)
{
    system("cls");
    switch (option)
    {
    case 1:
        // Implementar
        cout << "\nOpcion: " << option << endl;
        break;
    case 2:
        // Implementar
        cout << "\nOpcion: " << option << endl;
        break;
    case 3:
        // Implementar
        cout << "\nOpcion: " << option << endl;
        break;
    case 4:
        // Implementar
        cout << "\nOpcion: " << option << endl;
        break;
    default:
        break;
    }
}