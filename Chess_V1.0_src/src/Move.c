/* Jesse Campbell    January 17 */
/* Last edit: January 19        */

#include "Constants.h"
#include "Move.h"
#include "MoveList.h"
#include "InitializeBoard.h"
#include "PrintBoard.h"
#include "AI.h"
#include "ChessIO.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void GenerateMoves(PIECE *p, BOARD *gameBoard)
{
    int mRow, mCol, isCapture;
    PIECE *b[8][8];
    b[0][0] = gameBoard->b[0][0];
   

    /* PAWN */
    if (p->Class == PAWN)
    {
        if (p->Color == WHITE)
        { 
            /* FORWARD */
            isCapture = 0;
            if (p->row + 1 <= 7)
            {
                mRow = p->row + 1;
                mCol = p->col;
                if (gameBoard->b[mRow][mCol]->Class == EMPTY)
                {
                    isCheck(p, gameBoard->b[mRow][mCol], gameBoard, isCapture);
                    /* DOUBLE FORWARD */
                    isCapture = 0;
                    if (p->hasMoved == 0 && p->row + 2 <= 7)
                    {
                        mRow = p->row + 2;
                        mCol = p->col;
                        if (gameBoard->b[mRow][mCol]->Class == EMPTY)
                        {
                            isCheck(p, gameBoard->b[mRow][mCol], gameBoard, isCapture);
                        }
                    }
                }
                /* UP LEFT CAPTURE */
                isCapture = 1;
                if (p->col - 1 >= 0)
                {
                    mRow = p->row + 1;
                    mCol = p->col - 1;
                    if (gameBoard->b[mRow][mCol]->Color == gameBoard->Inactive->Color)
                    {
                        isCheck(p, gameBoard->b[mRow][mCol], gameBoard, isCapture);
                    }
                }
                /* UP RIGHT CAPTURE */
                isCapture = 1;
                if (p->col + 1 <= 7)
                {
                    mRow = p->row + 1;
                    mCol = p->col + 1;
                    if (gameBoard->b[mRow][mCol]->Color == gameBoard->Inactive->Color)
                    {
                        isCheck(p, gameBoard->b[mRow][mCol], gameBoard, isCapture);
                    }
                }
            }
        
            /* EN PASSANTE RIGHT */
            isCapture = 1;
            mRow = p->row + 1;
            mCol = p->col + 1;
            if ((p->row == 4) && (p->col + 1 <= 7) && (gameBoard->b[p->row][p->col + 1]->enPassant == 1) && (gameBoard->b[p->row][p->col + 1]->Color == gameBoard->Inactive->Color))
            {
                isCheck(p, gameBoard->b[mRow][mCol], gameBoard, isCapture);
            }
            /* EN PASSANTE LEFT */
            isCapture = 1;
            mRow = p->row + 1;
            mCol = p->col - 1;
            if ((p->row == 4) && (p->col - 1 >= 0) && (gameBoard->b[p->row][p->col - 1]->enPassant == 1) && (gameBoard->b[p->row][p->col - 1]->Color == gameBoard->Inactive->Color))
            {
                isCheck(p, gameBoard->b[mRow][mCol], gameBoard, isCapture);
            }
        } else /* if Color = BLACK */ { 
            /* DOWN */
            isCapture = 0;
            if (p->row - 1 >= 0)
            {
                mRow = p->row - 1;
                mCol = p->col;
                if (gameBoard->b[mRow][mCol]->Class == EMPTY)
                {
                    isCheck(p, gameBoard->b[mRow][mCol], gameBoard, isCapture);
                    /* DOUBLE DOWN */
                    isCapture = 0;
                    if (p->hasMoved == 0)
                    {
                        mRow = p->row - 2;
                        mCol = p->col;
                        if (gameBoard->b[mRow][mCol]->Class == EMPTY)
                        {
                            isCheck(p, gameBoard->b[mRow][mCol], gameBoard, isCapture);
                        }
                    }
                }
                /* DOWN LEFT CAPTURE */
                isCapture = 1;
                if (p->col - 1 >= 0)
                {
                    mRow = p->row - 1;
                    mCol = p->col - 1;
                    if (gameBoard->b[mRow][mCol]->Color == gameBoard->Inactive->Color)
                    {
                        isCheck(p, gameBoard->b[mRow][mCol], gameBoard, isCapture);
                    }
                }
                /* DOWN RIGHT CAPTURE */
                isCapture = 1;
                if (p->col + 1 <= 7)
                {
                    mRow = p->row - 1;
                    mCol = p->col + 1;
                    if (gameBoard->b[mRow][mCol]->Color == gameBoard->Inactive->Color)
                    {
                        isCheck(p, gameBoard->b[mRow][mCol], gameBoard, isCapture);
                    }
                }
            }
            /* EN PASSANTE RIGHT */
            isCapture = 1;
            mRow = p->row - 1;
            mCol = p->col + 1;
            if ((p->row == 3) && (p->col + 1 <= 7) && (gameBoard->b[p->row][p->col + 1]->enPassant == 1) && (gameBoard->b[p->row][p->col + 1]->Color == gameBoard->Inactive->Color))
            {
                isCheck(p, gameBoard->b[mRow][mCol], gameBoard, isCapture);
            }
            /* EN PASSANTE LEFT */
            isCapture = 1;
            mRow = p->row - 1;
            mCol = p->col - 1;
            if ((p->row == 3) && (p->col - 1 >= 0) && (gameBoard->b[p->row][p->col - 1]->enPassant == 1) && (gameBoard->b[p->row][p->col - 1]->Color == gameBoard->Inactive->Color))
            {
                isCheck(p, gameBoard->b[mRow][mCol], gameBoard, isCapture);
            }
        }
    } /* END OF PAWN */

    /* ROOK / QUEEN */
    if (p->Class == ROOK || p->Class == QUEEN)
    {
        /* FORWARD */
        if (p->row + 1 <= 7)
        {
            isCapture = 0;
            mRow = p->row + 1;
            mCol = p->col;
            while (!isCapture && (gameBoard->b[mRow][mCol]->Class == EMPTY || gameBoard->b[mRow][mCol]->Color == gameBoard->Inactive->Color))
            {
                if (!gameBoard->b[mRow][mCol]->Class == EMPTY)
                {
                    isCapture = 1;
                }
                isCheck(p, gameBoard->b[mRow][mCol], gameBoard, isCapture);
                mRow++;
                if (mRow > 7)
                {
                    isCapture = 1; /* Just a shortcut to exit the loop */
                }
            }
        }
        /* DOWNWARD */
        if (p->row - 1 >= 0)
        {
            isCapture = 0;
            mRow = p->row - 1;
            mCol = p->col;
            while (!isCapture && (gameBoard->b[mRow][mCol]->Class == EMPTY || gameBoard->b[mRow][mCol]->Color == gameBoard->Inactive->Color))
            {
                if (!gameBoard->b[mRow][mCol]->Class == EMPTY)
                {
                    isCapture = 1;
                }
                isCheck(p, gameBoard->b[mRow][mCol], gameBoard, isCapture);
                mRow--;
                if (mRow < 0)
                {
                    isCapture = 1; /* Just a shortcut to exit the loop */
                }
            }
        }
        /* LEFTWARD */
        if (p->col - 1 >= 0)
        { 
            isCapture = 0;
            mRow = p->row;
            mCol = p->col - 1;
            while (!isCapture && (gameBoard->b[mRow][mCol]->Class == EMPTY || gameBoard->b[mRow][mCol]->Color == gameBoard->Inactive->Color))
            {
                if (!gameBoard->b[mRow][mCol]->Class == EMPTY)
                {
                    isCapture = 1;
                }
                isCheck(p, gameBoard->b[mRow][mCol], gameBoard, isCapture);
                mCol--;
                if (mCol < 0)
                {
                    isCapture = 1; /* Just a shortcut to exit the loop */
                }
            }
        }
        /* RIGHTWARD */
        if (p->col + 1 <= 7)
        { 
            isCapture = 0;
            mRow = p->row;
            mCol = p->col + 1;
            while (!isCapture && (gameBoard->b[mRow][mCol]->Class == EMPTY || gameBoard->b[mRow][mCol]->Color == gameBoard->Inactive->Color))
            {
                if (!gameBoard->b[mRow][mCol]->Class == EMPTY)
                {
                    isCapture = 1;
                }
                isCheck(p, gameBoard->b[mRow][mCol], gameBoard, isCapture);
                mCol++;
                if (mCol > 7)
                {
                    isCapture = 1; /* Just a shortcut to exit the loop */
                }
            }
        }
    } /* END OF ROOK / QUEEN */

    /* KNIGHT */
    if (p->Class == KNIGHT)
    {
        /* FORWARD */
        if (p->row + 2 <= 7)
        {
            /* LEFT */
            if (p->col - 1 >= 0)
            {
                mRow = p->row + 2;
                mCol = p->col - 1;
                if (gameBoard->b[mRow][mCol]->Class == EMPTY)
                {
                    isCapture = 0;
                    isCheck(p, gameBoard->b[mRow][mCol], gameBoard, isCapture);
                }
                if (gameBoard->b[mRow][mCol]->Color == gameBoard->Inactive->Color)
                {
                    isCapture = 1;
                    isCheck(p, gameBoard->b[mRow][mCol], gameBoard, isCapture);
                }
            }
            /* RIGHT */
            if (p->col + 1 <= 7)
            {
                mRow = p->row + 2;
                mCol = p->col + 1;
                if (gameBoard->b[mRow][mCol]->Class == EMPTY)
                {
                    isCapture = 0;
                    isCheck(p, gameBoard->b[mRow][mCol], gameBoard, isCapture);
                }
                if (gameBoard->b[mRow][mCol]->Color == gameBoard->Inactive->Color)
                {
                    isCapture = 1;
                    isCheck(p, gameBoard->b[mRow][mCol], gameBoard, isCapture);
                }
            }
        }
        /* RIGHTWARD */
        if (p->col + 2 <= 7)
        {
            /* UP */
            if (p->row + 1 <= 7)
            {
                mCol = p->col + 2;
                mRow = p->row + 1;
                if (gameBoard->b[mRow][mCol]->Class == EMPTY)
                {
                    isCapture = 0;
                    isCheck(p, gameBoard->b[mRow][mCol], gameBoard, isCapture);
                }
                if (gameBoard->b[mRow][mCol]->Color == gameBoard->Inactive->Color)
                {
                    isCapture = 1;
                    isCheck(p, gameBoard->b[mRow][mCol], gameBoard, isCapture);
                }
            }
            /* DOWN */
            if (p->row - 1 >= 0)
            {
                mCol = p->col + 2;
                mRow = p->row - 1;
                if (gameBoard->b[mRow][mCol]->Class == EMPTY)
                {
                    isCapture = 0;
                    isCheck(p, gameBoard->b[mRow][mCol], gameBoard, isCapture);
                }
                if (gameBoard->b[mRow][mCol]->Color == gameBoard->Inactive->Color)
                {
                    isCapture = 1;
                    isCheck(p, gameBoard->b[mRow][mCol], gameBoard, isCapture);
                }
            }
        }
        /* DOWNWARD */
        if (p->row - 2 >= 0)
        {
            /* LEFT */
            if (p->col - 1 >= 0)
            {
                mRow = p->row - 2;
                mCol = p->col - 1;
                if (gameBoard->b[mRow][mCol]->Class == EMPTY)
                {
                    isCapture = 0;
                    isCheck(p, gameBoard->b[mRow][mCol], gameBoard, isCapture);
                }
                if (gameBoard->b[mRow][mCol]->Color == gameBoard->Inactive->Color)
                {
                    isCapture = 1;
                    isCheck(p, gameBoard->b[mRow][mCol], gameBoard, isCapture);
                }
            }
            /* RIGHT */
            if (p->col + 1 <= 7)
            {
                mRow = p->row - 2;
                mCol = p->col + 1;
                if (gameBoard->b[mRow][mCol]->Class == EMPTY)
                {
                    isCapture = 0;
                    isCheck(p, gameBoard->b[mRow][mCol], gameBoard, isCapture);
                }
                if (gameBoard->b[mRow][mCol]->Color == gameBoard->Inactive->Color)
                {
                    isCapture = 1;
                    isCheck(p, gameBoard->b[mRow][mCol], gameBoard, isCapture);
                }
            }
        }
        /* LEFTWARD */
        if (p->col - 2 >= 0)
        {
            /* UP */
            if (p->row + 1 <= 7)
            {
                mCol = p->col - 2;
                mRow = p->row + 1;
                if (gameBoard->b[mRow][mCol]->Class == EMPTY)
                {
                    isCapture = 0;
                    isCheck(p, gameBoard->b[mRow][mCol], gameBoard, isCapture);
                }
                if (gameBoard->b[mRow][mCol]->Color == gameBoard->Inactive->Color)
                {
                    isCapture = 1;
                    isCheck(p, gameBoard->b[mRow][mCol], gameBoard, isCapture);
                }
            }
            /* DOWN */
            if (p->row - 1 >= 0)
            {
                mCol = p->col - 2;
                mRow = p->row - 1;
                if (gameBoard->b[mRow][mCol]->Class == EMPTY)
                {
                    isCapture = 0;
                    isCheck(p, gameBoard->b[mRow][mCol], gameBoard, isCapture);
                }
                if (gameBoard->b[mRow][mCol]->Color == gameBoard->Inactive->Color)
                {
                    isCapture = 1;
                    isCheck(p, gameBoard->b[mRow][mCol], gameBoard, isCapture);
                }
            }
        }
    } /* END OF KNIGHT */

    /* BISHOP / QUEEN */
    if (p->Class == BISHOP || p->Class == QUEEN)
    {
        /* FORWARD-LEFT */
        if (p->row + 1 <= 7 && p->col - 1 >= 0)
        {
            isCapture = 0;
            mRow = p->row + 1;
            mCol = p->col - 1;
            while (!isCapture && (gameBoard->b[mRow][mCol]->Class == EMPTY || gameBoard->b[mRow][mCol]->Color == gameBoard->Inactive->Color))
            {
                if (!gameBoard->b[mRow][mCol]->Class == EMPTY)
                {
                    isCapture = 1;
                }
                isCheck(p, gameBoard->b[mRow][mCol], gameBoard, isCapture);
                mRow++;
                mCol--;
                if (mRow > 7 || mCol < 0)
                {
                    isCapture = 1; /* Just a shortcut to exit the loop */
                }
            }
        }
        /* DOWNWARD-LEFT */
        if (p->row - 1 >= 0 && p->col - 1 >= 0)
        {
            isCapture = 0;
            mRow = p->row - 1;
            mCol = p->col - 1;
            while (!isCapture && (gameBoard->b[mRow][mCol]->Class == EMPTY || gameBoard->b[mRow][mCol]->Color == gameBoard->Inactive->Color))
            {
                if (!gameBoard->b[mRow][mCol]->Class == EMPTY)
                {
                    isCapture = 1;
                }
                isCheck(p, gameBoard->b[mRow][mCol], gameBoard, isCapture);
                mRow--;
                mCol--;
                if (mRow < 0 || mCol < 0)
                {
                    isCapture = 1; /* Just a shortcut to exit the loop */
                }
            }
        }
        /* FORWARD-RIGHT */
        if (p->row + 1 <= 7 && p->col + 1 <= 7)
        { 
            isCapture = 0;
            mRow = p->row + 1;
            mCol = p->col + 1;
            while (!isCapture && (gameBoard->b[mRow][mCol]->Class == EMPTY || gameBoard->b[mRow][mCol]->Color == gameBoard->Inactive->Color))
            {
                if (!gameBoard->b[mRow][mCol]->Class == EMPTY)
                {
                    isCapture = 1;
                }
                isCheck(p, gameBoard->b[mRow][mCol], gameBoard, isCapture);
                mRow++;
                mCol++;
                if (mRow > 7 || mCol > 7)
                {
                    isCapture = 1; /* Just a shortcut to exit the loop */
                }
            }
        }
        /* DOWNWARD-RIGHT */
        if (p->row - 1 >= 0 && p->col + 1 <= 7)
        { 
            isCapture = 0;
            mRow = p->row - 1;
            mCol = p->col + 1;
            while (!isCapture && (gameBoard->b[mRow][mCol]->Class == EMPTY || gameBoard->b[mRow][mCol]->Color == gameBoard->Inactive->Color))
            {
                if (!gameBoard->b[mRow][mCol]->Class == EMPTY)
                {
                    isCapture = 1;
                }
                isCheck(p, gameBoard->b[mRow][mCol], gameBoard, isCapture);
                mRow--;
                mCol++;
                if (mRow < 0 || mCol > 7)
                {
                    isCapture = 1; /* Just a shortcut to exit the loop */
                }
            }
        }
    } /* END OF BISHOP / QUEEN */

    /* KING */
    if (p->Class == KING)
    {
        /* UP */
        if (p->row + 1 <= 7)
        {
            mRow = p->row + 1;
            mCol = p->col;
            if (gameBoard->b[mRow][mCol]->Class == EMPTY)
            {
                isCapture = 0;
                isCheck(p, gameBoard->b[mRow][mCol], gameBoard, isCapture);
            }
            if (gameBoard->b[mRow][mCol]->Color == gameBoard->Inactive->Color)
            {
                isCapture = 1;
                isCheck(p, gameBoard->b[mRow][mCol], gameBoard, isCapture);
            }
        }
        /* DOWN */
        if (p->row - 1 >= 0)
        {
            mRow = p->row - 1;
            mCol = p->col;
            if (gameBoard->b[mRow][mCol]->Class == EMPTY)
            {
                isCapture = 0;
                isCheck(p, gameBoard->b[mRow][mCol], gameBoard, isCapture);
            }
            if (gameBoard->b[mRow][mCol]->Color == gameBoard->Inactive->Color)
            {
                isCapture = 1;
                isCheck(p, gameBoard->b[mRow][mCol], gameBoard, isCapture);
            }
        }
        /* LEFT */
        if (p->col - 1 >= 0)
        {
            mRow = p->row;
            mCol = p->col - 1;
            if (gameBoard->b[mRow][mCol]->Class == EMPTY)
            {
                isCapture = 0;
                isCheck(p, gameBoard->b[mRow][mCol], gameBoard, isCapture);
            }
            if (gameBoard->b[mRow][mCol]->Color == gameBoard->Inactive->Color)
            {
                isCapture = 1;
                isCheck(p, gameBoard->b[mRow][mCol], gameBoard, isCapture);
            }
        }
        /* RIGHT */
        if (p->col + 1 <= 7)
        {
            mRow = p->row;
            mCol = p->col + 1;
            if (gameBoard->b[mRow][mCol]->Class == EMPTY)
            {
                isCapture = 0;
                isCheck(p, gameBoard->b[mRow][mCol], gameBoard, isCapture);
            }
            if (gameBoard->b[mRow][mCol]->Color == gameBoard->Inactive->Color)
            {
                isCapture = 1;
                isCheck(p, gameBoard->b[mRow][mCol], gameBoard, isCapture);
            }
        }
        /* UPLEFT */
        if (p->row + 1 <= 7 && p->col - 1 >= 0)
        {
            mRow = p->row + 1;
            mCol = p->col - 1;
            if (gameBoard->b[mRow][mCol]->Class == EMPTY)
            {
                isCapture = 0;
                isCheck(p, gameBoard->b[mRow][mCol], gameBoard, isCapture);
            }
            if (gameBoard->b[mRow][mCol]->Color == gameBoard->Inactive->Color)
            {
                isCapture = 1;
                isCheck(p, gameBoard->b[mRow][mCol], gameBoard, isCapture);
            }
        }
        /* UPRIGHT */
        if (p->row + 1 <= 7 && p->col + 1 <= 7)
        {
            mRow = p->row + 1;
            mCol = p->col + 1;
            if (gameBoard->b[mRow][mCol]->Class == EMPTY)
            {
                isCapture = 0;
                isCheck(p, gameBoard->b[mRow][mCol], gameBoard, isCapture);
            }
            if (gameBoard->b[mRow][mCol]->Color == gameBoard->Inactive->Color)
            {
                isCapture = 1;
                isCheck(p, gameBoard->b[mRow][mCol], gameBoard, isCapture);
            }
        }
        /* DOWNLEFT */
        if (p->row - 1 >= 0 && p->col - 1 >= 0)
        {
            mRow = p->row - 1;
            mCol = p->col - 1;
            if (gameBoard->b[mRow][mCol]->Class == EMPTY)
            {
                isCapture = 0;
                isCheck(p, gameBoard->b[mRow][mCol], gameBoard, isCapture);
            }
            if (gameBoard->b[mRow][mCol]->Color == gameBoard->Inactive->Color)
            {
                isCapture = 1;
                isCheck(p, gameBoard->b[mRow][mCol], gameBoard, isCapture);
            }
        }
        /* DOWNRIGHT */
        if (p->row - 1 >= 0 && p->col + 1 <= 7)
        {
            mRow = p->row - 1;
            mCol = p->col + 1;
            if (gameBoard->b[mRow][mCol]->Class == EMPTY)
            {
                isCapture = 0;
                isCheck(p, gameBoard->b[mRow][mCol], gameBoard, isCapture);
            }
            if (gameBoard->b[mRow][mCol]->Color == gameBoard->Inactive->Color)
            {
                isCapture = 1;
                isCheck(p, gameBoard->b[mRow][mCol], gameBoard, isCapture);
            }
        }
        /* CASTLING */
        if (p->hasMoved == 0)
        {
            /* KING SIDE */
            mRow = p->row;
            mCol = p->col + 2;
            isCapture = 0;
            if (gameBoard->b[p->row][p->col + 1]->Class == EMPTY)
            {
                if (gameBoard->b[p->row][p->col + 2]->Class == EMPTY)
                {
                    if (gameBoard->b[p->row][p->col + 3]->Class == ROOK && gameBoard->b[p->row][p->col + 3]->hasMoved == 0)
                    {
                        MOVE *move;
                        int verify;
                        verify = gameBoard->Active->moveList->Length;
                        isCheck(p, gameBoard->b[p->row][p->col], gameBoard, isCapture);
                        if (gameBoard->Active->moveList->Length != verify)
                        {
                            verify++;
                            isCheck(p, gameBoard->b[p->row][p->col + 1], gameBoard, isCapture);
                            if (gameBoard->Active->moveList->Length != verify)
                            {
                                verify = -1;
                                move = DeleteMoveEntry(gameBoard->Active->moveList->First);
                                DeleteMove(move);
                                gameBoard->Active->moveList->Length--;
                            }
                            move = DeleteMoveEntry(gameBoard->Active->moveList->First);
                            DeleteMove(move);
                            gameBoard->Active->moveList->Length--;
                        }
                        if (verify == -1) 
                        {
                            isCheck(p, gameBoard->b[mRow][mCol], gameBoard, isCapture);
                        }
                    }
                }
            }
            /* QUEEN SIDE */
            mRow = p->row;
            mCol = p->col - 2;
            if (gameBoard->b[p->row][p->col - 1]->Class == EMPTY)
            {
                if (gameBoard->b[p->row][p->col - 2]->Class == EMPTY)
                {
                    if (gameBoard->b[p->row][p->col - 3]->Class == EMPTY)
                    {
                        if (gameBoard->b[p->row][p->col - 4]->Class == ROOK && gameBoard->b[p->row][p->col - 4]->hasMoved == 0)
                        {
                        MOVE *move;
                        int verify;
                        verify = gameBoard->Active->moveList->Length;
                        isCheck(p, gameBoard->b[p->row][p->col], gameBoard, isCapture);
                        if (gameBoard->Active->moveList->Length != verify)
                        {
                            verify++;
                            isCheck(p, gameBoard->b[p->row][p->col - 1], gameBoard, isCapture);
                            if (gameBoard->Active->moveList->Length != verify)
                            {
                                verify = -1;
                                move = DeleteMoveEntry(gameBoard->Active->moveList->First);
                                DeleteMove(move);
                                gameBoard->Active->moveList->Length--;
                            }
                            move = DeleteMoveEntry(gameBoard->Active->moveList->First);
                            DeleteMove(move);
                            gameBoard->Active->moveList->Length--;
                        }
                        if (verify == -1) 
                        {
                            isCheck(p, gameBoard->b[mRow][mCol], gameBoard, isCapture);
                        }
                        }
                    }
                }
            }
        }
   }

}

void GenerateAllMoves(BOARD *gameBoard)
{
    int i, j;
    for (i = 0; i < 8; i++) { for (j = 0; j < 8; j++) {
        if (gameBoard->b[i][j]->Color == gameBoard->Active->Color)
        {
            GenerateMoves(gameBoard->b[i][j], gameBoard);
        }
    }}
    SortMoveList(gameBoard->Active->moveList);
}

BOARD *Move(MOVE *move, BOARD *gameBoard)
{    
    int i, j, enPassantFlag;
    PIECE *sPiece, *mPiece;
    CLASS Promotion;
    sPiece = gameBoard->b[move->sPiece->row][move->sPiece->col];
    mPiece = gameBoard->b[move->mPiece->row][move->mPiece->col];
    enPassantFlag = 0;
    
    /* If castling */   
    if ((sPiece->Class == KING && (sPiece->col - mPiece->col) * (sPiece->col - mPiece->col) == 4))
    {  
        if (mPiece->col == 6 && (gameBoard->b[sPiece->row][sPiece->col + 3]->Class == ROOK && gameBoard->b[sPiece->row][sPiece->col + 3]->Color == sPiece->Color))
        {
            mPiece->Class = sPiece->Class;
            mPiece->Color = sPiece->Color;
            mPiece->hasMoved = 1;
            sPiece->Class = EMPTY;
            sPiece->Color = EMPTYCOLOR;
            sPiece->hasMoved = 0;
            gameBoard->b[mPiece->row][5]->Class = ROOK;
            gameBoard->b[mPiece->row][5]->Color = mPiece->Color;
            gameBoard->b[mPiece->row][5]->hasMoved = 1;
            gameBoard->b[mPiece->row][7]->Class = EMPTY;
            gameBoard->b[mPiece->row][7]->Color = EMPTYCOLOR;
            gameBoard->b[mPiece->row][7]->hasMoved = 0;
        }
        if (mPiece->col == 2 && (gameBoard->b[sPiece->row][sPiece->col - 4]->Class == ROOK && gameBoard->b[sPiece->row][sPiece->col - 4]->Color == sPiece->Color))
        {
            mPiece->Class = sPiece->Class;
            mPiece->Color = sPiece->Color;
            mPiece->hasMoved = 1;
            sPiece->Class = EMPTY;
            sPiece->Color = EMPTYCOLOR;
            sPiece->hasMoved = 0; 
            gameBoard->b[mPiece->row][3]->Class = ROOK;
            gameBoard->b[mPiece->row][3]->Color = mPiece->Color;
            gameBoard->b[mPiece->row][3]->hasMoved = 1;
            gameBoard->b[mPiece->row][0]->Class = EMPTY;
            gameBoard->b[mPiece->row][0]->Color = EMPTYCOLOR;
            gameBoard->b[mPiece->row][0]->hasMoved = 0;
        }
    } /* If En Passant */ else if ((sPiece->Class == PAWN) && (mPiece->Class == EMPTY && move->isCapture == 1))
    {
        if (sPiece->Color == BLACK)
        {
            mPiece->Class = sPiece->Class;
            mPiece->Color = sPiece->Color;
            mPiece->hasMoved = 1;
            sPiece->Class = EMPTY;
            sPiece->Color = EMPTYCOLOR;
            sPiece->hasMoved = 0;
            gameBoard->b[mPiece->row + 1][mPiece->col]->Class = EMPTY;
            gameBoard->b[mPiece->row + 1][mPiece->col]->Color = EMPTYCOLOR;
            gameBoard->b[mPiece->row + 1][mPiece->col]->hasMoved = 0;
        } else {
            mPiece->Class = sPiece->Class;
            mPiece->Color = sPiece->Color;
            mPiece->hasMoved = 1;
            sPiece->Class = EMPTY;
            sPiece->Color = EMPTYCOLOR;
            sPiece->hasMoved = 0;
            gameBoard->b[mPiece->row - 1][mPiece->col]->Class = EMPTY;
            gameBoard->b[mPiece->row - 1][mPiece->col]->Color = EMPTYCOLOR;
            gameBoard->b[mPiece->row - 1][mPiece->col]->hasMoved = 0;
        }
    } /* If double move pawn */ else if ((sPiece->Class == PAWN) && (sPiece->row - mPiece->row) * (sPiece->row - mPiece->row) == 4) {
        mPiece->Class = sPiece->Class;
        mPiece->Color = sPiece->Color;
        mPiece->hasMoved = 1;
        sPiece->Class = EMPTY;
        sPiece->Color = EMPTYCOLOR;
        sPiece->hasMoved = 0;
        mPiece->enPassant = 1;
        enPassantFlag = 1;
    } /* Other pieces */ else
    {
        mPiece->Class = sPiece->Class;
        mPiece->Color = sPiece->Color;
        mPiece->hasMoved = 1;
        sPiece->Class = EMPTY;
        sPiece->Color = EMPTYCOLOR;
        sPiece->hasMoved = 0;
    }
    
    /* Adjusting KRow and KCol */
    if (mPiece->Class == KING)
    {
        gameBoard->Active->kRow = mPiece->row;
        gameBoard->Active->kCol = mPiece->col;
    }
    
    /* Promotion */
    if ((mPiece->Class == PAWN))
    {
        if (gameBoard->Active->Color == WHITE && move->mPiece->row == 7)
        {       
            if (gameBoard->Active->isHuman && gameBoard->Depth == DEPTH)
            {
                Promotion = PromotionPrompt();
            } else if(gameBoard->Active->isHuman == 0 && gameBoard->Depth == DEPTH) {
                Promotion = QUEEN;
            }
            gameBoard->b[move->mPiece->row][move->mPiece->col]->Class = Promotion;
	    gameBoard->b[move->mPiece->row][move->mPiece->col]->Color = WHITE;
        } else if (gameBoard->Active->Color == BLACK && move->mPiece->row == 0) {
            if (gameBoard->Active->isHuman && gameBoard->Depth == DEPTH)
            {
                Promotion = PromotionPrompt();
            } else if(gameBoard->Active->isHuman == 0 && gameBoard->Depth == DEPTH){
                Promotion = QUEEN;
            }
            gameBoard->b[move->mPiece->row][move->mPiece->col]->Class = Promotion;
	    gameBoard->b[move->mPiece->row][move->mPiece->col]->Color = BLACK;
        }
    }
    
    /* enPassant flag scrubbing */
    for (i = 0; i < 8; i++) { for (j = 0; j < 8; j++) {
        if (!(gameBoard->b[i][j] == mPiece) || enPassantFlag == 0)
        {
            gameBoard->b[i][j]->enPassant = 0;
        }
    }}

    return gameBoard;
}

MOVE *CreateMove(PIECE *p, PIECE *m, int isCapture)
{
    MOVE *move;
    assert(p);
    assert(m);
    move = malloc(sizeof(MOVE));
    if (!move)
    {
        perror("Out of memory! Aborting...");
        exit(10);
    }
    move->sPiece = p;
    move->mPiece = m;
    move->isCapture = isCapture;
    return move;
}

void DeleteMove(MOVE *move)
{
    assert(move);
    free(move);
}

void isCheck(PIECE *p, PIECE *m, BOARD *gameBoard, int isCapture)
{
    MOVE *move;
    BOARD *newBoard = 0;
    MENTRY *e, *n;
    PLAYER *tempPlayer;
    int i, j, verify;
    move = CreateMove(p, m, isCapture);
    if (gameBoard->Depth == DEPTH)
    {
        newBoard = CopyBoard(gameBoard, newBoard);
	    newBoard = Move(move, newBoard);
        newBoard->Depth--;
        tempPlayer = newBoard->Active;
        newBoard->Active = newBoard->Inactive;
        newBoard->Inactive = tempPlayer;
       	for (i = 0; i < 8; i++) { for (j = 0; j < 8; j++) {
	        if (newBoard->Active->Color == newBoard->b[i][j]->Color)
            {
                GenerateMoves(newBoard->b[i][j], newBoard);
            }
        }} 
        e = newBoard->Active->moveList->First;
        verify = 0;
        while (e)
        {
            n = e->Next;
            if ((e->Move->mPiece->Class == KING && e->Move->mPiece->Color == newBoard->Inactive->Color))
            {
                verify = -1;
            }
            e = n;
        }
        if (verify == 0)
        {
            AppendMove(gameBoard->Active->moveList, move);
        } else {
            DeleteMove(move);
        }
        DeleteBoard(newBoard); 
    } else {
        AppendMove(gameBoard->Active->moveList, move);
    }
}
