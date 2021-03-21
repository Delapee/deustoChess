#include <stdio.h>
#include "chess.h"


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
    int option, read;
    bool rigth;

    do {
        printf("\n+---------------------------------------------+\n");
        printf("|               MENU DE INICIO                |\n");
        printf("|---------------------------------------------|\n");
        printf("| 1. Jugar Local                              |\n");
        printf("| 2. Jugar Online                             |\n");
        printf("| 3. Jugar contra IA                          |\n");
        printf("| 4. Puzzles                                  |\n");
        printf("| 5. Ver partida repetida	              |\n");
        printf("| 0. Salir                                    |\n");
        printf("+---------------------------------------------+\n");

        printf("\nSelecciona una opcion: ");
        read = scanf("%d", &option);

        if (read != 1 || option < 0 || option > 5) {
            cleanStdin();
            system("cls");
            printf("\nValor incorrecto, debe estar entre 0 y 5.\n");
            rigth = false;
        }
        else rigth = true;
    } while (!rigth);

    return option;
}

void selectOption(int option)
{
    switch (option)
    {
    case 1:
        system("cls");
        test();
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
        printf("Opcion: %d\n", option);
        // Implementar
        break;
    case 5:
        printf("Opcion: %d\n", option);
        //Implementar
        break;
    }
}