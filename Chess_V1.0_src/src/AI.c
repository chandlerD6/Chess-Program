/* AI function executions by Chandler Ditolla*/
#include "Constants.h"
#include "AI.h"
#include "MoveList.h"
#include "Move.h"
#include "InitializeBoard.h"
#include "FileIO.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
/*The max for the minmax alpha beta algorithim, it copies the board positions passed in and 
  and generates a movelist for it */
int GetBestMax(BOARD * board, int depth, int alpha, int beta){
	MLIST *tempList;
	MENTRY *tempEntry;
	int score, lengthcp, tempL;
	if(depth == 0 || board->Active->moveList->Length == 0){
		return EvalBoard(board);
	}
	tempList = board->Active->moveList;
	tempEntry = tempList->First;
	for(lengthcp = 0; lengthcp < tempList->Length; lengthcp++){
		BOARD *copy;
		copy = CopyBoard(board, copy);	
		/*Free generated movelist if not already empty*/	
		copy = Move(tempEntry->Move, copy);
        	if(copy->Active->moveList->Length != 0){
        		EmptyMoveList(copy->Active->moveList);	
        	}
		/*Swaps player for the Min function to Black*/
   		if (copy->Active->Color == WHITE){
    			PLAYER *temp;
    			temp = copy->Active;
    			copy->Active = copy->Inactive;
    			copy->Inactive = temp;
    			temp = NULL;	
    		}	
        
        	GenerateAllMoves(copy);
		score = GetBestMin(copy, depth -1, alpha, beta); /*Function call for min and simulates a swaping of players*/
		if(score >= beta){
			DeleteBoard(copy);
			return beta;
		}
		if(score > alpha){
			alpha = score;
	        tempL = lengthcp;
		}
		DeleteBoard(copy);

		tempEntry = tempEntry->Next;
	}
	tempList = NULL;
    	if(depth == board->Depth - 1){
        	alpha  = tempL;
    	}
	return alpha;
}

int GetBestMin(BOARD * board, int depth, int alpha, int beta){
	MLIST *tempList;
	MENTRY *tempEntry;
	int score, lengthcp, tempL;
	if(depth == 0 || board->Active->moveList->Length == 0){
		return EvalBoard(board);
	}


	tempList = board->Active->moveList;
	tempEntry = tempList->First;
	for(lengthcp = 0; lengthcp < tempList->Length; lengthcp++){
		BOARD *copy;
		copy = CopyBoard(board, copy);	
		copy = Move(tempEntry->Move, copy);
		/*Free generated movelist if not already empty*/	
    		if(copy->Active->moveList->Length != 0){
       			EmptyMoveList(copy->Active->moveList);	
   	  	}
		/*Swaps player for the Max function to White*/
      		if (copy->Active->Color == BLACK){
    			PLAYER *temp;
    			temp = copy->Active;
    			copy->Active = copy->Inactive;
    			copy->Inactive = temp;
    			temp = NULL;	
    		}
       		GenerateAllMoves(copy);

		score = GetBestMax(copy, depth -1, alpha, beta);
		if(score <= alpha){
			DeleteBoard(copy);
			return alpha;
		}
		if(score < beta){
			beta = score;
				tempL = lengthcp;
		}
		DeleteBoard(copy);
		tempEntry = tempEntry->Next;
	}
	tempList = NULL;
    	if(depth == board->Depth - 1){
       		beta = tempL;
   	}
        return beta;
}

void GetBestMove(BOARD * board){
	MLIST *temp;
	MENTRY *e, *n;
	int i, tracker;
	char *piece[2], *pos[2];

	if(board->Active->Color == WHITE){
		tracker = GetBestMax(board, board->Depth - 1, ALPHA, BETA); 
	}
	if(board->Active->Color == BLACK){
		tracker = GetBestMin(board, board->Depth - 1, ALPHA, BETA);
	}

	temp = board->Active->moveList;
	e = temp->First;

	for(i = 0; i < tracker; i++){
		n = e->Next;
		e = n;
	} 
	
	piece[0] = GetPiece(e->Move->sPiece);
	piece[1] = GetPiece(e->Move->mPiece);
	pos[0] = GetPosition(e->Move->sPiece);
	pos[1] = GetPosition(e->Move->mPiece);

	
	if(board->Active->Color == WHITE)
	{
		printf("White moved: %s from %s to %s\n", piece[0], pos[0], pos[1]);
		SaveLog(board, piece[0], pos[0], pos[1], "log.txt");
		if(piece[1] != NULL)
		{
			printf("%s has captured %s\n", piece[0], piece[1]);
			SaveCaptureLog(piece[0], piece[1]);
		}
	}
	else if(board->Active->Color == BLACK)
	{
		printf("Black moved: %s from %s to %s\n", piece[0], pos[0], pos[1]);
		SaveLog(board, piece[0], pos[0], pos[1], "log.txt");
		if(piece[1] != NULL)
		{
			printf("%s has captured %s\n", piece[0], piece[1]);
			SaveCaptureLog(piece[0], piece[1]);
		}	
	}

	if (e != NULL){	
		Move(e->Move, board);
	}
	

}



/* evaluates the gamestate of the board and returns a negative number for black and a positive number for white*/
int EvalBoard(BOARD * board){
	int  min = 0 , x, y, pieceCount = 0;
	double pawnplace;
	PLAYER *temp;
	/*Swap player and generate a move list for moves counter*/
	temp = board->Active;
	board->Active = board->Inactive;
	board->Inactive = temp;
	GenerateAllMoves(board);
	/*Gives Points for total moves i.e. piece movement/development*/
	if(board->Active->Color == BLACK){
		min = min - (0.1 * board->Active->moveList->Length);
		min = min + (0.1 * board->Inactive->moveList->Length);
		/*CheckMate*/
		if(board->Active->moveList->Length == 0){
			min = min + KING;
		}
		if(board->b[board->Active->kRow][board->Active->kCol]->hasMoved == 1){
			min = min + 6;
		}
		/*Caslting Points*/
		if((board->b[7][2]->Class == KING && board->b[7][3]->Class == ROOK) || (board->b[7][6]->Class == KING && board->b[7][5]->Class == ROOK)){
			min = min - 4;
		}  
	} else if(board->Active->Color == WHITE){
		min = min + (0.1 * board->Active->moveList->Length);
		min = min - (0.1 * board->Inactive->moveList->Length);
		if(board->Active->moveList->Length == 0){
			min = min -  KING;
		}
		if(board->b[board->Active->kRow][board->Active->kCol]->hasMoved == 1){
			min = min - 6;
		}
		/*Caslting Points*/
		if((board->b[0][2]->Class == KING && board->b[0][3]->Class == ROOK) || (board->b[0][6]->Class == KING && board->b[0][5]->Class == ROOK)){
			min = min + 4;
		}  
	}
	/*Empty the generated movelist and swap back active players*/
	EmptyMoveList(board->Active->moveList);
	temp = board->Active;
	board->Active = board->Inactive;
	board->Inactive = temp;

	for(x = 0; x < 8; x++){
		for(y = 0; y < 8; y++){
			if(board->b[x][y]->Color == BLACK){
				if(board->b[x][y]->Class == PAWN){
					pawnplace = pawnplace + 0.3*(2 - x);
				}
				/*For initial pawn moves to go towards center of the board */
				if(board->b[x][y]->Class == PAWN && ((x == 4 || x == 5) && ( y == 3 || y == 4))){
					min = min - board->b[x][y]->Class - 2;
					/*For the center pawns to cover other friendly pieces */
					if (board->b[x-1][y-1]->Color == BLACK || board->b[x-1][y+1]->Color == BLACK){
						min = min - board->b[x][y]->Class - 1;
					}
				} else  { 
					min = min - board->b[x][y]->Class;	
				}
			pieceCount++;
			}else if(board->b[x][y]->Color == WHITE) {
				if(board->b[x][y]->Class == PAWN){
					pawnplace = pawnplace + 0.3*(x - 2);
				}
				/*For initial pawn moves to go towards center of the board */
				if(board->b[x][y]->Class == PAWN && ((x == 2 || x == 3) && ( y == 3 || y == 4))){
					min = min + board->b[x][y]->Class + 2;
					/*For the center pawns to cover other friendly pieces */
					if (board->b[x+1][y-1]->Color == WHITE || board->b[x+1][y+1]->Color == WHITE){
						min = min + board->b[x][y]->Class + 1;
					}
				} else {   
					min = min + board->b[x][y]->Class;
				}
			pieceCount++;
			}
		}
	}
	min = min + (int)pawnplace;	
	/*If near the end of the game prioritize getting king out near center to hel defend pieces and promote pawns*/
	if ( min > -100 && min < 100 && pieceCount < 8){
		for(x = 2; x < 6; x++){
			for(y = 2; y < 6; y++){
				if(board->b[x][y]->Class == KING && board->b[x][y]->Color == BLACK){
					min = min - 4;
				} else if (board->b[x][y]->Class == KING && board->b[x][y]->Color == WHITE){
					min = min + 4;
				}
			}
		}
	}
		
	return min;				
}

/*Takes the current gameboard and makes a copy of all its pieces for simulation*/
BOARD *CopyBoard(BOARD * Oldboard, BOARD * Newboard){
    int x, y;
    
     Newboard = CreateBoard();
     Newboard->Active->kRow = Oldboard->Active->kRow;
     Newboard->Active->kCol = Oldboard->Active->kCol;
     Newboard->Inactive->kRow = Oldboard->Inactive->kRow;
     Newboard->Inactive->kCol = Oldboard->Inactive->kCol;

     if (Oldboard->Active->Color == BLACK){
           Newboard->Active->Color = BLACK;
           Newboard->Inactive->Color = WHITE;
        
     }

    for(x = 0; x < 8; x++){
        for(y = 0; y < 8; y++){
            Newboard->b[x][y]->Class = Oldboard->b[x][y]->Class;
            Newboard->b[x][y]->Color = Oldboard->b[x][y]->Color;
            Newboard->b[x][y]->hasMoved = Oldboard->b[x][y]->hasMoved;
            Newboard->b[x][y]->row = Oldboard->b[x][y]->row;
            Newboard->b[x][y]->col = Oldboard->b[x][y]->col;
            Newboard->b[x][y]->enPassant = Oldboard->b[x][y]->enPassant;    
        }
    }
    Newboard->Active->isHuman = 0;
    Newboard->Inactive->isHuman =0;
    Newboard->Depth = Oldboard->Depth;
    return Newboard;
}
