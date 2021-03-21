#if !defined(CHESS)
#define CHESS

typedef struct Board
{   
    char panel[64][3];
    int castl[4];
}Board;

// Metodos tablero
void test(void);
void prepareBoard(Board * bo);                                  // Inicializa el tablero
void loadPanel(Board *bo, char status[80]);                     // Carga un estado dentro del tablero
void loadPiece(Board *bo, char status[40], char player);        // Carga un grupo de piezas
void printBoard(Board *bo, int player);                         // Imprime el tablero teniendo en cuenta el jugador
void savePanel(Board* bo, char estatus[80]);                    // Guarda el estado actual del tablero

// Utilidades
int getPos(char move[3]);                   // Recibe una casilla y devuelve el indice 
char getColumn(char move[3]);               // Devuelve la Columna
int getRow(char move[3]);                   // Devuelve la Fila
char getColumnId(int pos);                  // Devuelve la Columna por id 
int getRowId(int pos);                      // Devuelve la Fila por id 
char getPiece(Board *bo, char move[3]);     // Devuelve la pieza
char getColor(Board *bo, char move[3]);     // Devuelve el color


// Movimento
void movePiece(Board *bo, char move[5]);                    // Mueve una pieza de a -> b
int isMove(Board *bo, char move[5], int protec);            // Comprueba si es posible mover de a -> b
int isSpot(Board* bo, char pos[3], char color);             // Comprueba si una pieza esta amenazada por otra de X color
int checkWin(Board* bo, char player);                       // Devuelve 0 - Nada | 1 - Jaque | 2 - Mate
void checkCastle(Board* bo);                                // Comprobar si se rompe el enroque
void isPromote(Board* bo);

#endif // CHESS