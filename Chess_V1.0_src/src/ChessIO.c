#include <stdio.h>
#include <string.h>
#include "ChessIO.h"
#include "FileIO.h"
#include "Move.h"
#include "PrintBoard.h"

int moveMenu(BOARD *gameBoard){
	char initLocation[SLEN];
	char finalLocation[SLEN];

	char initLocRow;
	char initLocCol;
	char finalLocRow;
	char finalLocCol;
	char *piece[2];	

	int isCaptureFlag, initLocRowInt, initLocColInt, finalLocRowInt, finalLocColInt;

    MOVE *move;

	do{
		do{
            
			if(gameBoard->Active->Color == -1)
			{
				printf("Black's move:\n");
			}
			else if(gameBoard->Active->Color == 1)
			{
				printf("White's move:\n");
			}
 
			printf("Enter the starting location of the piece to moved followed by the final location\n");
			printf("(ex. 'e2 e4' or enter 'ff' to forfeit):  ");
			
			scanf("%s", initLocation);
			
			if (strcmp(initLocation, "ff") == 0)
			{
				printf("Forfeited\n");
				SaveMessage(gameBoard, "Player has forfeited.");
		
				return 1;
			}
			scanf(" %s", finalLocation);
			
			/*
			printf("Enter the location that you want to move the piece to (enter ff for forfeit): ");
			scanf("%s", finalLocation);
			*/
            

			initLocRow = initLocation[1];
			initLocCol = initLocation[0];
	
			finalLocRow = finalLocation[1];
			finalLocCol = finalLocation[0];
 
	
			if (initLocCol >= 'A' && initLocCol <= 'Z'){
				initLocCol += 32;
			}
			if (finalLocCol >= 'A' && finalLocCol <= 'Z'){
				finalLocCol += 32;
			}

			initLocRowInt = ((int) initLocRow) -  49;
			initLocColInt = ((int) initLocCol) - 97;

			finalLocRowInt = ((int) finalLocRow) - 49;
			finalLocColInt = ((int) finalLocCol) - 97;
            
            /* If statement results in 1, isCapture = 0, 2, isCapture = 1, 0, does not enter */
			if((isCaptureFlag = isMoveValid(initLocRowInt, initLocColInt, finalLocRowInt, finalLocColInt, gameBoard)) > 0){
				break;
			}
			PrintBoard(gameBoard);
            /*message of invalid move*/				
			printf("I'm sorry player, I'm afraid I can't let you do that. (Invalid move)\n");
            
		}while(1); /*Loop if move is invalid*/
        
        isCaptureFlag--;

		piece[0] = GetPiece(gameBoard->b[initLocRowInt][initLocColInt]);
		piece[1] = GetPiece(gameBoard->b[finalLocRowInt][finalLocColInt]);

		move = CreateMove(gameBoard->b[initLocRowInt][initLocColInt], gameBoard->b[finalLocRowInt][finalLocColInt], isCaptureFlag);
		/*Save*/
		SaveLog(gameBoard, piece[0], initLocation, finalLocation, "log.txt"); 
		if(piece[1] != NULL)
		{		
			printf("\n\n%s has captured %s\n\n", piece[0], piece[1]);
			SaveCaptureLog(piece[0], piece[1]);
		}
		/*Move*/
        gameBoard = Move(move, gameBoard);

        DeleteMove(move);
        break; 
	}while(1);/*Loop if quit is not selected. Break if game is over.*/	
    return 0;
}

int isMoveValid(int initLocRowInt, int initLocColInt, int finalLocRowInt, int finalLocColInt, BOARD *gameBoard){
	
	MENTRY *e;
	MENTRY *n;
	e = gameBoard->Active->moveList->First;
	
	int initRow, initCol, finalRow, finalCol;


	while(e){
		n = e->Next;
		/*gameBoard->Active->moveList*/
				
		initRow = e->Move->sPiece->row; 
		initCol = e->Move->sPiece->col;

		finalRow = e->Move->mPiece->row;
		finalCol = e->Move->mPiece->col;
		
		if(initRow == initLocRowInt && initCol == initLocColInt){
			if(finalRow == finalLocRowInt && finalCol == finalLocColInt){
				/* Check to see if move isCapture */
                if (e->Move->isCapture == 1)
                {
                    return 2;
                } else {
                    return 1;
                }
			}
		}		
		e = n;
	}
	return 0; 
}

CLASS PromotionPrompt()
{
    char choice = '0';
    CLASS classChoice;
    printf("Please choose a piece to promote your pawn to: (Q, R, B, N) ");
    scanf(" %c", &choice);
    if (choice == 'Q')
    {
        return QUEEN;
    } else if (choice == 'R')
    {   
        return ROOK;
    } else if (choice == 'B')
    {
        return BISHOP;
    } else if (choice == 'N')
    {
        return KNIGHT;
    } else {
        printf("Invalid choice.\n");
        classChoice = PromotionPrompt();
        return classChoice;
    }
}
