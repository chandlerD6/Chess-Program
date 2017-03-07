#include <stdio.h>
#include <stdlib.h>
#include "Constants.h"
#include "PrintBoard.h"
#define RED   "\x1B[31m"
#define RESET "\x1B[0m"

void PrintBoard(BOARD *board){

    int i, j, k, x, rows = 0, blackWhite, colorSquare;
    char *pawn[6][4], *knight[6][4], *king[6][4], *queen[6][4], *rook[6][4], *bishop[6][4], *square[6][2];


    square[0][0] =   "             ";
    square[1][0] =   "             ";
    square[2][0] =   "             ";
    square[3][0] =   "             ";
    square[4][0] =   "             ";
    square[5][0] =   "             ";

    square[0][1] =   ":::::::::::::";
    square[1][1] =   ":::::::::::::";
    square[2][1] =   ":::::::::::::";
    square[3][1] =   ":::::::::::::";
    square[4][1] =   ":::::::::::::";
    square[5][1] =   ":::::::::::::";

    pawn[0][0] =   "      _      ";
    pawn[1][0] =   "     (_)     ";
    pawn[2][0] =   "    (___)    ";
    pawn[3][0] =   "    _|_|_    ";
    pawn[4][0] =   "   (_____)   ";
    pawn[5][0] =   "   /_____\\   ";

    knight[0][0] = "     |\\.     ";
    knight[1][0] = "    /   '.   ";
    knight[2][0] = "   /_.'-  \\  ";
    knight[3][0] = "     /   |   ";
    knight[4][0] = "    /____|   ";
    knight[5][0] = "   `.____.'  ";

    king[0][0] =   "     ( )     ";
    king[1][0] =   "  .-. ^ .-.  ";
    king[2][0] =   " :   `.'   : ";
    king[3][0] =   " `.       .' ";
    king[4][0] =   "  )_.---._(  ";
    king[5][0] =   "  `._____.'  ";

    queen[0][0] =  "   o   o     ";
    queen[1][0] =  "o  /\\ /\\   o ";
    queen[2][0] =  "\\`.' `  `.'/ ";
    queen[3][0] =  " \\        /  ";
    queen[4][0] =  "  \\_.--._/   ";
    queen[5][0] =  "  '.____.'   ";

    rook[0][0] =   "   | |_| |   ";
    rook[1][0] =   "   |     |   ";
    rook[2][0] =   "   '-----'   ";
    rook[3][0] =   "   |     |   ";
    rook[4][0] =   "  /_.---._\\  ";
    rook[5][0] =   "  '._____.'  ";

    bishop[0][0] = "      <>_    ";
    bishop[1][0] = "    (\\)  )   ";
    bishop[2][0] = "     \\__/    ";
    bishop[3][0] = "     |__|    ";
    bishop[4][0] = "    /____\\   ";
    bishop[5][0] = "   (______)  ";

    pawn[0][1] =   "      _      ";
    pawn[1][1] =   "     (_)     ";
    pawn[2][1] =   "    (_x_)    ";
    pawn[3][1] =   "    _|x|_    ";
    pawn[4][1] =   "   (__x__)   ";
    pawn[5][1] =   "   /xxxxx\\   ";

    knight[0][1] = "     |\\.     ";
    knight[1][1] = "    /   '.   ";
    knight[2][1] = "   /_. -  \\  ";
    knight[3][1] = "     /xx |   ";
    knight[4][1] = "    /_xx_|   ";
    knight[5][1] = "   `.xxxx.'  ";

    king[0][1] =   "     ( )     ";
    king[1][1] =   "  .-. ^ .-.  ";
    king[2][1] =   " :   `.'   : ";
    king[3][1] =   " `.   x   .' ";
    king[4][1] =   "  )_.-x-._(  ";
    king[5][1] =   "  `.xxxxx.'  ";

    queen[0][1] =  "   o   o     ";
    queen[1][1] =  "o  /\\ /\\   o ";
    queen[2][1] =  "\\`.' `  `.'/ ";
    queen[3][1] =  " \\   xx   /  ";
    queen[4][1] =  "  \\_.xx._/   ";
    queen[5][1] =  "  '.xxxx.'   ";

    rook[0][1] =   "   | |_| |   ";
    rook[1][1] =   "   |     |   ";
    rook[2][1] =   "   '--x--'   ";
    rook[3][1] =   "   |  x  |   ";
    rook[4][1] =   "  /_.-x-._\\  ";
    rook[5][1] =   "  '.xxxxx.'  ";

    bishop[0][1] = "      <>_    ";
    bishop[1][1] = "    (\\)  )   ";
    bishop[2][1] = "     \\__/    ";
    bishop[3][1] = "     |__|    ";
    bishop[4][1] = "    /_xx_\\   ";
    bishop[5][1] = "   (xxxxxx)  ";

    pawn[0][2] =   ":::::::::::::";
    pawn[1][2] =   ":::::(_):::::";
    pawn[2][2] =   "::::(___)::::";
    pawn[3][2] =   "::::_|_|_::::";
    pawn[4][2] =   ":::(_____):::";
    pawn[5][2] =   ":::/_____\\:::";

    knight[0][2] = ":::::|\\.:::::";
    knight[1][2] = "::::/   '.:::";
    knight[2][2] = ":::/_.'-  \\::";
    knight[3][2] = ":::::/   |:::";
    knight[4][2] = "::::/____|:::";
    knight[5][2] = ":::`.____.'::";

    king[0][2] =   ":::::( ):::::";
    king[1][2] =   "::.-. ^ .-.::";
    king[2][2] =   "::   `.'   ::";
    king[3][2] =   ":`.       .':";
    king[4][2] =   "::)_.---._(::";
    king[5][2] =   "::`._____.'::";

    queen[0][2] =  ":::o:::o:::::";
    queen[1][2] =  "o::/\\:/\\:::o:";
    queen[2][2] =  "\\`.' `  `.'/:";
    queen[3][2] =  ":\\        /::";
    queen[4][2] =  "::\\_.--._/:::";
    queen[5][2] =  "::'.____.':::";

    rook[0][2] =   ":::| |_| |:::";
    rook[1][2] =   ":::|     |:::";
    rook[2][2] =   ":::'-----':::";
    rook[3][2] =   ":::|     |:::";
    rook[4][2] =   "::/_.---._\\::";
    rook[5][2] =   "::'._____.'::";

    bishop[0][2] = "::::::<>_::::";
    bishop[1][2] = "::::(\\)  ):::";
    bishop[2][2] = ":::::\\__/::::";
    bishop[3][2] = ":::::|__|::::";
    bishop[4][2] = "::::/____\\:::";
    bishop[5][2] = ":::(______)::";

    pawn[0][3] =   ":::::::::::::";
    pawn[1][3] =   ":::::(_):::::";
    pawn[2][3] =   "::::(_x_)::::";
    pawn[3][3] =   "::::_|x|_::::";
    pawn[4][3] =   ":::(__x__):::";
    pawn[5][3] =   ":::/xxxxx\\:::";

    knight[0][3] = ":::::|\\.:::::";
    knight[1][3] = "::::/   '.:::";
    knight[2][3] = ":::/_. -  \\::";
    knight[3][3] = ":::::/xx |:::";
    knight[4][3] = "::::/_xx_|:::";
    knight[5][3] = ":::`.xxxx.'::";

    king[0][3] =   ":::::( ):::::";
    king[1][3] =   "::.-. ^ .-.::";
    king[2][3] =   "::   `.'   ::";
    king[3][3] =   ":`.   x   .':";
    king[4][3] =   "::)_.-x-._(::";
    king[5][3] =   "::`.xxxxx.'::";

    queen[0][3] =  ":::o:::o:::::";
    queen[1][3] =  "o::/\\:/\\:::o:";
    queen[2][3] =  "\\`.' `  `.'/:";
    queen[3][3] =  ":\\   xx   /::";
    queen[4][3] =  "::\\_.xx._/:::";
    queen[5][3] =  "::'.xxxx.':::";

    rook[0][3] =   ":::| |_| |:::";
    rook[1][3] =   ":::|     |:::";
    rook[2][3] =   ":::'--x--':::";
    rook[3][3] =   ":::|  x  |:::";
    rook[4][3] =   "::/_.-x-._\\::";
    rook[5][3] =   "::'.xxxxx.'::";

    bishop[0][3] = "::::::<>_::::";
    bishop[1][3] = "::::(\\)  ):::";
    bishop[2][3] = ":::::\\__/::::";
    bishop[3][3] = ":::::|__|::::";
    bishop[4][3] = "::::/_xx_\\:::";
    bishop[5][3] = ":::(xxxxxx)::";
    
    x = k = 0;
    for(i = 0; i < 8; i++){ 
        for(k = 0; k < 6; k++){
            for(j = 0; j < 8; j++){
                if(board->b[7-i][j]->Class == EMPTY){
                    if(x % 2 == 0){
                        printf("%s",square[k][1]);
                    }        
                    else if(x % 1 == 0){
                        printf("%s",square[k][0]);
                    }
                }

                else{ 
                    if(board->b[7-i][j]->Color == WHITE){
                        blackWhite = 0;
                    }        
                    else if(board->b[7-i][j]->Color == BLACK){
                        blackWhite = 1;
                    }
                    if (blackWhite == 0){
                        if(x % 2 == 0){
                            colorSquare = 2;
                        }
                        else if (x % 1 == 0){
                            colorSquare = 0; 
                        } 
                    }
                    else if (blackWhite == 1){
                        if(x % 2 == 0){
                            colorSquare = 3;
                        }
                        else if (x % 1 == 0){
                            colorSquare = 1; 
                        }  
                    }
                    if(board->b[7-i][j]->Class == PAWN){
                        printf("%s",pawn[k][colorSquare]);
                    }
                    else if(board->b[7-i][j]->Class == ROOK){
                        printf("%s",rook[k][colorSquare]);
                    }
                    else if(board->b[7-i][j]->Class == KNIGHT){
                        printf("%s",knight[k][colorSquare]);
                    }
                    else if(board->b[7-i][j]->Class == BISHOP){
                        printf("%s",bishop[k][colorSquare]);
                    }
                    else if(board->b[7-i][j]->Class == QUEEN){
                        printf("%s",queen[k][colorSquare]);
                    }
                    else if(board->b[7-i][j]->Class == KING){
                        printf("%s",king[k][colorSquare]);
                    }
                }
                x++;
            }
                if(k == 3){
                    printf(RED "  %d"RESET ,9 - (++rows));
                }
                puts("");
        }
        x++;
    }
        printf(RED"       A            B            C           D            E             F            G            H\n"RESET);

}

