#ifndef AI_H_
#define AI_H_

/*I am beautiful, no matter what you say....*/

/*Sorts through the moves generated in a scan of the board and assign points to moves storing the best*/
void GetBestMove(BOARD *board);

/*Takes the current gameboard and makes a copy of all its pieces for simulation*/
BOARD *CopyBoard(BOARD *Oldboard, BOARD * Newboard);

int GetBestMax(BOARD *board, int depth, int alpha, int beta);

int GetBestMin(BOARD *board, int depth, int alpha, int beta);

int EvalBoard(BOARD *board);
#endif
