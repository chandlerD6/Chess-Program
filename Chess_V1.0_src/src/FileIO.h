/*Lambert*/

#ifndef FILEIO_H
#define FILEIO_H

void SaveCaptureLog(char piece1[], char piece2[]);
void SaveMessage(BOARD *game, char message[]);
char* GetPiece(PIECE *pieceType);
char* GetPosition(PIECE *pieceType);
void SaveLog(BOARD *game, char piece[], char move1[],char move2[], char FILENAME[]);
int PrintMainMenu();
void LoadLog();
void EndOfGameLog();
int PrintEndMenu();
void Banner();
void LoadHelp();
#endif
