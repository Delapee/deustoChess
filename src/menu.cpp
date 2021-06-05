#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "dataBase/dbManager.h"

using namespace std;

void selectMenuOption(int option);
void initGameMenu();
int selectGameMenuOption();
void selectGameMenuOption(int option);

DBManager db;
#define dbName "deustoChess.db"

int main() 
{
    db = DBManager(dbName);

    string option;
    bool rigth = false;

    do
    {
        cout << "\n+---------------------------------------------+\n" <<
                "|               MENU DE INICIO                |\n" <<
                "|---------------------------------------------|\n" <<
                "| 1. Iniciar sesion                           |\n" <<
                "| 2. Registrarser                             |\n" <<
                "| 0. Salir                                    |\n" <<
                "+---------------------------------------------+" << endl;

        cout << "\nSelecciona una opcion: ";
        cin >> option;

        if (option.length() != 1 || option.at(0) - '0' < 0 || option.at(0) - '0' > 2)
        {
            system("cls");
            cout << "\nValor incorrecto, debe estar entre 0 y 2." << endl;
        }
        else rigth = true;
    } while (!rigth);

    selectMenuOption(stoi(option));

    return 0;
}

void selectMenuOption(int option)
{
    system("cls");
    switch (option)
    {
    case 1:
        login();
        break;
    case 2:
        regis();
    default:
        break;
    }
}

void login() 
{
    char* user;
    char* pass;
    bool rigth = false;

    do
    {
        cout << "\nUsuario: ";
        cin >> user;

        cout << "\nContraseña: ";
        cin >> pass;

        if (!db.verifyUser(user, pass))
        {
            system("cls");
            cout << "\nUsuario o contraseña incorecta" << endl;
        }
        else rigth = true;
    } while (!rigth);

    initGameMenu();
}

void regis() 
{
    vector<char*> userNames;
    char* user;
    char* pass;
    bool rigth = false;

    do
    {
        cout << "\nUsuario: ";
        cin >> user;

        if (count(userNames.begin(), userNames.end(), user))
        {
            system("cls");
            cout << "\nUsuario no valido" << endl;
        }
        else rigth = true;
    } while (!rigth);

    rigth = false;

    do
    {
        cout << "\nContraseña: ";
        cin >> pass;

        if (pass[7] == NULL)
        {
            system("cls");
            cout << "\nContraseña no valida" << endl;
            cout << "\nUsuario: " << user << endl;
        }
        else rigth = true;
    } while (!rigth);

    db.addNewUser(user, pass);

    initGameMenu();
}

void initGameMenu() 
{
    system("cls");
    int opcion;

    do
    {
        opcion = selectGameMenuOption();
        selectMenuOption(opcion);
    } while (opcion != 0);
}

int selectGameMenuOption()
{
    string option;
    bool rigth = false;
    
    do
    {
        cout << "\n+---------------------------------------------+\n" <<
                "|               MENU DE JUEGO                 |\n" <<
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

void selectGameMenuOption(int option)
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