#include <stdio.h>
#include "chess.h"
#include "puzzle.h"
#include "gamemode.h"

typedef enum { false, true } bool;

int selectMenuOption(void );
void selectOption(int option);
void cleanStdin(void );


int main() 
{
    int opcion;

    do {
        opcion = selectMenuOption();
        selectOption(opcion);
    } while (opcion != 0);

    return 0;
}

void cleanStdin() {
    while (getchar() != '\n');
}

int selectMenuOption() {
    int read;
    char option;
    bool rigth;

    do {
        printf("\n+---------------------------------------------+\n");
        printf("|               MENU DE INICIO                |\n");
        printf("|---------------------------------------------|\n");
        printf("| 1. Jugar Local                              |\n");
        printf("| 2. Jugar Online                             |\n");
        printf("| 3. Jugar contra IA                          |\n");
        printf("| 4. Puzzles Rush                             |\n");
        printf("| 5. Creador de puzzles                       |\n");
        printf("| 6. Ver partida repetida                     |\n");
        printf("| 0. Salir                                    |\n");
        printf("+---------------------------------------------+\n");

        printf("\nSelecciona una opcion: ");
        read = scanf("%c", &option);

        if (read != 1 || option == '\n' || option - '0' < 0 || option - '0' > 6) {
            cleanStdin();
            system("cls");
            printf("\nValor incorrecto, debe estar entre 0 y 5.\n");
            rigth = false;
        }
        else rigth = true;
    } while (!rigth);

    return option - '0';
}

void selectOption(int option)
{
    switch (option)
    {
    case 1:
        system("cls");
        offlineGamemode();
        break;
    case 2:
        printf("Opcion: %d\n", option);
        // Implementar
        break;
    case 3:
        printf("Opcion: %d\n", option);
        // Implementar
        break;
    case 4:
        system("cls");
        initPuzzles();
        break;
    case 5:
        printf("Opcion: %d\n", option);
        //Implementar
        break;
    case 6:
        printf("Opcion: %d\n", option);
        //Implementar
        break;
    }
}