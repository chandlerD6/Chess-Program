/* Jesse Campbell	January 17 */
#ifndef MOVE_H_
#define MOVE_H_

#include "Constants.h" 

void GenerateAllMoves(BOARD *gameBoard);
void GenearteMoves(PIECE *p, BOARD *gameBoard);
BOARD *Move(MOVE *move, BOARD *gameBoard);
MOVE *CreateMove(PIECE *p, PIECE *m, int isCapture);
void DeleteMove(MOVE *move);
void isCheck(PIECE *p, PIECE *m, BOARD *gameVoard, int isCapture);
#endif
