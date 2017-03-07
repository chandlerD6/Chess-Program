#ifndef CHESSIO_H_
#define CHESSIO_H_
#include "Constants.h"

int moveMenu(BOARD *gameBoard);
int isMoveValid(int initLocRowInt, int initLocColInt, int finalLocColInt, int finalLocRowInt, BOARD *gameBoard);
CLASS PromotionPrompt();

#endif
