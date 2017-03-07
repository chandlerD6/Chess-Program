#include "Constants.h"
#include "MoveList.h"
#include <stdio.h>
#include <stdlib.h>
#include "InitializeBoard.h"
#include <assert.h>
BOARD *InitializeBoard(void){

    int i, j;
    COLOR blackWhite;
    CLASS piece;
    BOARD *wholeBoard;

    wholeBoard = CreateBoard();
    assert(wholeBoard);


    for(j = 0; j < 8; j++){
        for(i = 0; i < 8; i++)
        {
            if(i == 6){       /*changed*/
                (wholeBoard->b[i][j]->Class) = PAWN;
                (wholeBoard->b[i][j]->Color) = BLACK;
                (wholeBoard->b[i][j]->hasMoved) = 0;
                (wholeBoard->b[i][j]->row) = i; 
                (wholeBoard->b[i][j]->col) = j;
            }
            else if(i == 1){/*changed*/
                (wholeBoard->b[i][j]->Class) = PAWN;
                (wholeBoard->b[i][j]->Color) = WHITE;
                (wholeBoard->b[i][j]->hasMoved) = 0;
                (wholeBoard->b[i][j]->row) = i;
                (wholeBoard->b[i][j]->col) = j;
            }
            else if(i == 0 || i == 7){

                if(i == 0){/*changed*/
                    blackWhite = WHITE;
                }
                else{
                    blackWhite = BLACK;
                }

                if(j == 0 || j == 7){
                    piece = ROOK;
                }
                if(j == 1 || j == 6){
                    piece = KNIGHT;
                }
                if(j == 2 || j == 5){
                    piece = BISHOP;
                }
                if(j == 3){
                    piece = QUEEN;
                }
                if(j == 4){
                    piece = KING;
                }



                (wholeBoard->b[i][j]->Class) = piece;
                (wholeBoard->b[i][j]->Color) = blackWhite;
                (wholeBoard->b[i][j]->hasMoved) = 0;
                (wholeBoard->b[i][j]->row) = i;
                (wholeBoard->b[i][j]->col) = j;
            }
            else{
                (wholeBoard->b[i][j]->Class) = EMPTY;
                (wholeBoard->b[i][j]->Color) = EMPTYCOLOR;
                (wholeBoard->b[i][j]->hasMoved) = 0;
                (wholeBoard->b[i][j]->row) = i;
                (wholeBoard->b[i][j]->col) = j; 
            }
        wholeBoard->b[i][j]->enPassant = 0;
        }
    }

    wholeBoard->Active->kRow = 0;
    wholeBoard->Active->kCol = 4;
    wholeBoard->Inactive->kRow = 7;
    wholeBoard->Inactive->kCol = 4;

    return wholeBoard;
}

void DeleteBoard(BOARD *b){
    int i, j;

    for(j = 0; j < 8; j++){
        for(i = 0; i < 8; i++)
        {
            free(b->b[i][j]);

        }
    }
    DeleteMoveList(b->Inactive->moveList);  
    free(b->Inactive);
    DeleteMoveList(b->Active->moveList);
    free(b->Active);
    free(b);
}

BOARD *CreateBoard(void)
{
    BOARD *gameBoard;
    int i, j;
    gameBoard = malloc(sizeof(BOARD));
    if (!gameBoard)
    {
        perror("Out of memory! Aborting...");
        exit(10);
    }
    gameBoard->Depth = DEPTH;
    gameBoard->Active = 0;
    gameBoard->Inactive = 0;
    gameBoard->Active = malloc(sizeof(PLAYER));
    if (!gameBoard->Active)
    {
        perror("Out of memory! Aborting...");
        exit(10);
    }
    gameBoard->Active->moveList = CreateMoveList();
    gameBoard->Inactive = malloc(sizeof(PLAYER));
    if (!gameBoard->Inactive)
    {
        perror("Out of memory! Aborting...");
        exit(10);
    }
    gameBoard->Inactive->moveList = CreateMoveList();
    for (i = 0; i < 8; i++ ) { for (j = 0; j < 8; j++ ) {
        gameBoard->b[i][j] = malloc(sizeof(PIECE));
        assert(gameBoard->b[i][j]);
        if (!gameBoard->b[i][j])
        {
            perror("Out of memory! Aborting...");
            exit(10);
        }
    }}

    gameBoard->Active->Color = WHITE;
    gameBoard->Inactive->Color = BLACK;
    return gameBoard;
}
