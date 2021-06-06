#include <iostream>
#include <string>
#include "dataBase/dbManager.h"
#include "launchGame.h"
#include "utility/modulo.h"
extern "C" {
    #include "game/puzzle.h"
}

using namespace std;

void login();
void regis();
void selectMenuOption(int option);
void initGameMenu();
int selectGameMenuOption();
void gameMenuOption(int option);

#define dbName "deustoChess.db"
DBManager db = DBManager(dbName);

int main(int argc, char* argv[])
{
    moduloStockfish::Modulo::setArgv(argv);
    system("cls");

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
        break;
    }
}

void login()
{
    char* user = new char[15];
    char* pass = new char[15];
    bool rigth = false;

    do
    {
        std::cout << "\nUsuario: ";
        cin >> user;

        std::cout << "Contraseña: ";
        cin >> pass;

        if (!db.verifyUser(user, pass))
        {
            system("cls");
            std::cout << "\nUsuario o contraseña incorecta" << endl;
        }
        else rigth = true;
    } while (!rigth);

    initGameMenu();
}

void regis()
{
    char* user = new char[15];
    char* pass = new char[15];
    bool rigth = false;

    do
    {
        std::cout << "\nUsuario: ";
        cin >> user;

        if (db.userExists(user))
        {
            system("cls");
            std::cout << "\nUsuario no valido" << endl;
        }
        else rigth = true;
    } while (!rigth);

    std::cout << "Contraseña: ";
    cin >> pass;

    db.addNewUser(user, pass);

    initGameMenu();
}

void initGameMenu()
{
    system("cls");
    int opcion;
        
    opcion = selectGameMenuOption();
    gameMenuOption(opcion);
}

int selectGameMenuOption()
{
    system("cls");

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
            "| 4. Puzzles Rush (Clasico)                   |\n" <<
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

void gameMenuOption(int option)
{
    system("cls");
    switch (option)
    {
    case 1:
        launch(1);
        break;
    case 2:
        launch(2);
        break;
    case 3:
        launch(3);
        break;
    case 4:
        initPuzzles();
        break;
    default:
        break;
    }
}