/*Lambert*/
#include "Constants.h"
#include "FileIO.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

void SaveCaptureLog(char piece1[], char piece2[])
{	
	FILE *log;
	log = fopen("log.txt", "a");

	fprintf(log, "\t     %s has captured %s\n", piece1, piece2);	

	fclose(log);
}

void SaveMessage(BOARD *game, char message[])
{
	assert(game);

	FILE *log;
	log = fopen("log.txt", "a");
	char *Color[1];

	if(game->Active->Color == (-1))
	{
		Color[0] = "Black";
	}
	else if(game->Active->Color == 1)
	{
		Color[0] = "White";
	}

	fprintf(log, "%s %s\n\n", Color[0], message);

	fclose(log);
}

char* GetPosition(PIECE *pieceType)
{

	char *pos;
	
	if(pieceType->col == 0 && pieceType->row == 0)
	{
		pos = "a1"; 
	}
	else if(pieceType->col == 0 && pieceType->row == 1)
	{
		pos = "a2"; 
	}
	else if(pieceType->col == 0 && pieceType->row == 2)
	{
		pos = "a3"; 
	}
	else if(pieceType->col == 0 && pieceType->row == 3)
	{
		pos = "a4"; 
	}
	else if(pieceType->col == 0 && pieceType->row == 4)
	{
		pos = "a5"; 
	}
	else if(pieceType->col == 0 && pieceType->row == 5)
	{
		pos = "a6"; 
	}
	else if(pieceType->col == 0 && pieceType->row == 6)
	{
		pos = "a7"; 
	}
	else if(pieceType->col == 0 && pieceType->row == 7)
	{
		pos = "a8"; 
	}

	if(pieceType->col == 1 && pieceType->row == 0)
	{
		pos = "b1"; 
	}
	else if(pieceType->col == 1 && pieceType->row == 1)
	{
		pos = "b2"; 
	}
	else if(pieceType->col == 1 && pieceType->row == 2)
	{
		pos = "b3"; 
	}
	else if(pieceType->col == 1 && pieceType->row == 3)
	{
		pos = "b4"; 
	}
	else if(pieceType->col == 1 && pieceType->row == 4)
	{
		pos = "b5"; 
	}
	else if(pieceType->col == 1 && pieceType->row == 5)
	{
		pos = "b6"; 
	}
	else if(pieceType->col == 1 && pieceType->row == 6)
	{
		pos = "b7"; 
	}
	else if(pieceType->col == 1 && pieceType->row == 7)
	{
		pos = "b8"; 
	}
	
	if(pieceType->col == 2 && pieceType->row == 0)
	{
		pos = "c1"; 
	}
	else if(pieceType->col == 2 && pieceType->row == 1)
	{
		pos = "c2"; 
	}
	else if(pieceType->col == 2 && pieceType->row == 2)
	{
		pos = "c3"; 
	}
	else if(pieceType->col == 2 && pieceType->row == 3)
	{
		pos = "c4"; 
	}
	else if(pieceType->col == 2 && pieceType->row == 4)
	{
		pos = "c5"; 
	}
	else if(pieceType->col == 2 && pieceType->row == 5)
	{
		pos = "c6"; 
	}
	else if(pieceType->col == 2 && pieceType->row == 6)
	{
		pos = "c7"; 
	}	
	else if(pieceType->col == 2 && pieceType->row == 7)
	{
		pos = "c8"; 
	}

	if(pieceType->col == 3 && pieceType->row == 0)
	{
		pos = "d1"; 
	}
	else if(pieceType->col == 3 && pieceType->row == 1)
	{
		pos = "d2"; 
	}
	else if(pieceType->col == 3 && pieceType->row == 2)
	{
		pos = "d3"; 
	}
	else if(pieceType->col == 3 && pieceType->row == 3)
	{
		pos = "d4"; 
	}
	else if(pieceType->col == 3 && pieceType->row == 4)
	{
		pos = "d5"; 
	}
	else if(pieceType->col == 3 && pieceType->row == 5)
	{
		pos = "d6"; 
	}
	else if(pieceType->col == 3 && pieceType->row == 6)
	{
		pos = "d7"; 
	}
	else if(pieceType->col == 3 && pieceType->row == 7)
	{
		pos = "d8"; 
	}

	if(pieceType->col == 4 && pieceType->row == 0)
	{
		pos = "e1"; 
	}
	else if(pieceType->col == 4 && pieceType->row == 1)
	{
		pos = "e2"; 
	}
	else if(pieceType->col == 4 && pieceType->row == 2)
	{
		pos = "e3"; 
	}
	else if(pieceType->col == 4 && pieceType->row == 3)
	{
		pos = "e4"; 
	}
	else if(pieceType->col == 4 && pieceType->row == 4)
	{
		pos = "e5"; 
	}
	else if(pieceType->col == 4 && pieceType->row == 5)
	{
		pos = "e6"; 
	}
	else if(pieceType->col == 4 && pieceType->row == 6)
	{
		pos = "e7"; 
	}
	else if(pieceType->col == 4 && pieceType->row == 7)
	{
		pos = "e8"; 
	}

	if(pieceType->col == 5 && pieceType->row == 0)
	{
		pos = "f1"; 
	}
	else if(pieceType->col == 5 && pieceType->row == 1)
	{
		pos = "f2"; 
	}
	else if(pieceType->col == 5 && pieceType->row == 2)
	{
		pos = "f3"; 
	}
	else if(pieceType->col == 5 && pieceType->row == 3)
	{
		pos = "f4"; 
	}
	else if(pieceType->col == 5 && pieceType->row == 4)
	{
		pos = "f5"; 
	}
	else if(pieceType->col == 5 && pieceType->row == 5)
	{
		pos = "f6"; 
	}
	else if(pieceType->col == 5 && pieceType->row == 6)
	{
		pos = "f7"; 
	}
	else if(pieceType->col == 5 && pieceType->row == 7)
	{
		pos = "f8"; 
	}

	if(pieceType->col == 6 && pieceType->row == 0)
	{
		pos = "g1"; 
	}
	else if(pieceType->col == 6 && pieceType->row == 1)
	{
		pos = "g2"; 
	}
	else if(pieceType->col == 6 && pieceType->row == 2)
	{
		pos = "g3"; 
	}
	else if(pieceType->col == 6 && pieceType->row == 3)
	{
		pos = "g4"; 
	}
	else if(pieceType->col == 6 && pieceType->row == 4)
	{
		pos = "g5"; 
	}
	else if(pieceType->col == 6 && pieceType->row == 5)
	{
		pos = "g6"; 
	}
	else if(pieceType->col == 6 && pieceType->row == 6)
	{
		pos = "g7"; 
	}
	else if(pieceType->col == 6 && pieceType->row == 7)
	{
		pos = "g8"; 
	}

	if(pieceType->col == 7 && pieceType->row == 0)
	{
		pos = "h1"; 
	}
	else if(pieceType->col == 7 && pieceType->row == 1)
	{
		pos = "h2"; 
	}
	else if(pieceType->col == 7 && pieceType->row == 2)
	{
		pos = "h3"; 
	}
	else if(pieceType->col == 7 && pieceType->row == 3)
	{
		pos = "h4"; 
	}
	else if(pieceType->col == 7 && pieceType->row == 4)
	{
		pos = "h5"; 
	}
	else if(pieceType->col == 7 && pieceType->row == 5)
	{
		pos = "h6"; 
	}
	else if(pieceType->col == 7 && pieceType->row == 6)
	{
		pos = "h7"; 
	}
	else if(pieceType->col == 7 && pieceType->row == 7)
	{
		pos = "h8"; 
	}
	return pos;

}
char* GetPiece(PIECE *pieceType)
{
	char *piece;

	if(pieceType->Class == PAWN)
	{
		piece = "Pawn";
	}
	else if(pieceType->Class == ROOK)
	{
		piece = "Rook";
	}
	else if(pieceType->Class == KNIGHT)
	{
		piece = "Knight";
	}
	else if(pieceType->Class == BISHOP)
	{
		piece = "Bishop";
	}
	else if(pieceType->Class == QUEEN)
	{
		piece = "Queen";
	}
	else if(pieceType->Class == KING)
	{
		piece = "King";
	}
	else if(pieceType->Class == EMPTY)
	{
		piece = NULL;
	}

	return piece;	
}
void SaveLog(BOARD *game, char piece[], char move1[],char move2[], char FILENAME[])
{
	assert(game);

	FILE *log;
	log = fopen(FILENAME, "a");	

	char *pieceColor[1];

	if(game->Active->Color == (-1))
	{
		pieceColor[0] = "Black";
	}
	else if(game->Active->Color == 1)
	{
		pieceColor[0] = "White";
	}

	fprintf(log, "%s moved: %s from %s to %s\n", pieceColor[0], piece, move1, move2);


	fclose(log);
}

int PrintMainMenu()
{	Banner();
	printf("Welcome to Chessence!\n\n");
	char choice = '0';

	while(choice != '1' && choice != '2' && choice != '3' && choice != '4' && choice != '5')
	{
		printf("Please choose one of the options (1, 2, 3, 4, 5)\n");
		printf("1)\t Player vs Computer\n");
		printf("2)\t Player vs Player\n");
		printf("3)\t Computer vs Computer\n");
		printf("4)\t Help\n");
		printf("5)\t Quit\n");
		printf("Choice:  ");

		scanf(" %c", &choice);

		if(choice != '1' && choice != '2' && choice != '3' && choice != '4' && choice != '5')
		{
			printf("\nInvalid option.\n");
		}		
	}

	int ichoice = choice - '0';

	return (ichoice);
}

void PrintHelpMenu()
{
    printf("----Help Menu----\n");
    printf("Enter all locations in the format column and row, with a space between starting and ending position. Example: e2 e4\n");
    printf("You can find the rules of chess here: http://www-math.bgsu.edu/~zirbel/chess/BasicChessRules.pdf \n");
}


int PrintEndMenu()
{
	char choice = '0';

	while(choice != '1' && choice != '2' && choice != '3')
	{	
		printf("Please choose an option\n");
		printf("1)\t Return to main menu\n");
		printf("2)\t Review log of game\n");
		printf("3)\t Quit\n");
		printf("Choice:  ");
		scanf(" %c", &choice);

		if(choice != '1' && choice != '2' && choice != '3')
		{
			printf("\nInvalid option.\n");
		}

	}

	int ichoice = choice - '0';

	return ichoice;
}

void LoadLog()
{
	FILE *log;
	char buffer[10000], next;
	log = fopen("log.txt", "r");
	/* NEW */

	if(log == NULL)
	{
		printf("Error opening file!\n");
		return;
	}
	
	while(fgets(buffer, 10000, log) != NULL)
	{
		printf("%s", buffer);
	}
	
	fclose(log);

	while(next != 'c')
	{		
		printf("\nType 'c' then enter to exit:  ");

		scanf("%s", &next);
	}
}

void LoadHelp()
{
	FILE *help;
	char buffer[10000000], next;
	help = fopen("../src/HELP.txt", "r");

	if(help == NULL)
	{
		printf("Error opening file!\n");
		return;
	}
	
	while(fgets(buffer, 10000000, help) != NULL)
	{
		printf("%s", buffer);
	}
	
	fclose(help);

	while(next != 'c')
	{		
		printf("\nType 'c' then enter to exit:  ");

		scanf("%s", &next);
	}	
}

void EndOfGameLog()
{
	FILE *log;
	log = fopen("log.txt", "a");

	fprintf(log, "----------------------------\n\n");

	fclose(log);
}

void Banner()
{
	puts("  _______  .__                          _________               __   __        ");
	puts(" /   ___ \\ |  |__   ____   ______ _____ |_____   \\ ____   ____ |  | / /,______ ");
	puts("/    \\  \\/ |  |  \\_/ __ \\ /  ___//  ___/|    |  _//  _ \\ /  _ \\|  |/ / /  ___/ ");
	puts("\\     \\___ |   Y  \\  ___/ \\___ \\ \\___ \\ |    |   (  <_> |  <_> )    <  \\___ \\  ");
	puts(" \\_______ /|___|__/\\_____> ____/ _____/ |________/\\____/ \\____/|__|__\\/_____/ \n\n");

	puts("  _______  .__                                                                 ");
	puts(" /   ___ \\ |  |__   ____   ______ ______ ____   ____   ____   ____              ");
	puts("/    \\  \\/ |  |  \\_/ __ \\ /  ___//  ___// __ \\ /    \\_/ ___\\ / __ \\             ");
	puts("\\     \\___ |   Y  \\  ___/ \\___ \\ \\___ \\ \\  __/ |  |  |\\  \\__ \\ ___/             ");
	puts(" \\________/|___|__/\\_____> ____/ _____/  \\_____>__|  / \\____/ \\____>            \n\n"); 
}
