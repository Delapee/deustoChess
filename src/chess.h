#if !defined(CHESS)
#define CHESS
#define sPos "e1/d1/a1h1/c1f1/b1g1/a2b2c2d2e2f2g2h2/|e8/d8/a8h8/c8f8/b8g8/a7b7c7d7e7f7g7h7/"
typedef struct Board
{   
    char panel[64][3];
    int castl[4];
}Board;

// Metodos tablero
void test(void);
void prepareBoard(Board * bo);                                  // Inicializa el tablero
void loadPanel(Board *bo, char status[80]);                     // Carga un estado dentro del tablero
void savePanel(Board* bo, char estatus[80]);                    // Guarda el estado actual del tablero
void printBoard(Board* bo, int player);                         // Imprime el tablero teniendo en cuenta el jugador
void loadPiece(Board *bo, char status[40], char player);        // Carga un grupo de piezas
void clearPanel(Board* bo);                                     // Limpia la Board actual

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
void isPromote(Board* bo);                                  // Comprobar si hay alguna promoción y la realiza
int isNailed(Board* bo, char move[5]);                      // Comprueba si la pieza esta clavada
#endif // CHESS