#include "Constants.h"
#include "FileIO.h"
#include "InitializeBoard.h"
#include "AI.h"
#include "ChessIO.h"
#include "Move.h"
#include "MoveList.h"
#include "PrintBoard.h"
#include <stdio.h>
#include <assert.h>

int PlayGame(int gameType, COLOR color);

int main(void){

    int mainMenuFlag = 0, color;
    int x;

    while(mainMenuFlag != 5){
        mainMenuFlag = PrintMainMenu();

        if (mainMenuFlag == 5){
            puts("Play again soon!");
	    x = 0;
	    
        }
        else if (mainMenuFlag == 1){
            printf("What color would you like (black = -1, white = 1)? ");
                scanf("%d", &color);
            x = PlayGame(mainMenuFlag, color);
        }
        else if (mainMenuFlag == 2){
            x = PlayGame(mainMenuFlag, 0);
        }
        else if (mainMenuFlag == 3){
            x = PlayGame(mainMenuFlag, 0);   
        }
        else if (mainMenuFlag == 4){
            LoadHelp();   
        }

	
		if(x == 1)
		{
			mainMenuFlag = 0;
		}
		else if (x == 2)
		{
			LoadLog();	
			mainMenuFlag = 0;
		}
		else if (x == 3)
		{
			mainMenuFlag = 5;
		}
    }
    return 0;
}


int PlayGame(int gameType, COLOR color)
{
    BOARD *gameBoard;
    MENTRY *e, *n;
    int endGame = 0, x, count = 0;
    PLAYER *temp;
    
    gameBoard = InitializeBoard();
    if (gameType == 1)
    {
        if (color == WHITE)
        {
            gameBoard->Active->isHuman = 1;
            gameBoard->Inactive->isHuman = 0;
        } else {
            gameBoard->Active->isHuman = 0;
            gameBoard->Inactive->isHuman = 1;
        }
    }
    else if (gameType == 2)
    {
        gameBoard->Active->isHuman = 1;
        gameBoard->Inactive->isHuman = 1;
    }
    else if (gameType == 3)
    {
        gameBoard->Active->isHuman = 0;
        gameBoard->Inactive->isHuman = 0;
    }
    do
    {
        GenerateAllMoves(gameBoard);
        if (gameBoard->Active->moveList->Length == 0)
        {
            endGame = 1;
        }
        else {
            count++;
            PrintBoard(gameBoard);
            if (gameBoard->Active->isHuman)
            {
                endGame = moveMenu(gameBoard);
            } else { /* If Active is an AI... */
                GetBestMove(gameBoard); 
            }
        }
        EmptyMoveList(gameBoard->Active->moveList);
        temp = gameBoard->Active;
        gameBoard->Active = gameBoard->Inactive;
        gameBoard->Inactive = temp;
    } while (!endGame);
    endGame = 0; /* Now is a flag to signal checkmate */
    GenerateAllMoves(gameBoard);
    e = gameBoard->Active->moveList->First;
    while (e)
    {
        n = e->Next;
        if (e->Move->mPiece->row == gameBoard->Inactive->kRow && e->Move->mPiece->col == gameBoard->Inactive->kCol)
        {
            endGame = 1;
        }
        e = n;
    }
    EmptyMoveList(gameBoard->Active->moveList);
    if (endGame == 1)
    {
        if (gameBoard->Active->Color == WHITE)
        {
            PrintBoard(gameBoard);
            printf("Checkmate!  White wins!\n\n");
        } else {
            PrintBoard(gameBoard);
            printf("Checkmate! Black wins!\n\n");
        }
    }
    if (endGame == 0)
    {
        printf("Stalemate! No winner!\n\n");
    }
    EndOfGameLog();
    DeleteBoard(gameBoard);
 
    x = PrintEndMenu();

    return x;
}
