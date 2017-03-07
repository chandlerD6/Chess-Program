/* Constants header file for struct declarations and enumerator declarations*/
#ifndef CONSTANTS_H_
#define CONSTANTS_H_
#define SLEN 80 
#define ALPHA -2147483647
#define BETA 2147483647
#define DEPTH 5
 
typedef struct MLIST MLIST;
typedef struct MENTRY MENTRY;
typedef struct MOVE MOVE;
typedef struct PIECE PIECE;
typedef struct PLAYER PLAYER;
typedef struct BOARD BOARD;

typedef enum COLOR COLOR;
typedef enum CLASS CLASS;

enum COLOR{
    EMPTYCOLOR = 0,
    BLACK = -1,
    WHITE = 1
};

enum CLASS{
    EMPTY = 0,
    PAWN = 10,
    ROOK = 50,
    KNIGHT = 30,
    BISHOP = 31,
    QUEEN = 90,
    KING = 2000
};

struct MLIST{
    int Length;
    MENTRY *First;
};

struct MENTRY{
    MLIST *List;
    MENTRY *Next;
    MOVE *Move;
};

struct MOVE{
    int isCapture;
    PIECE *sPiece;
    PIECE *mPiece;
    int pointValue;
};


struct PIECE{
    CLASS Class;
    COLOR Color;
    int hasMoved;
    int row;
    int col;
    int enPassant;
};

struct PLAYER{ 
    COLOR Color;
    MLIST *moveList;
    int kRow;
    int kCol;
    int isHuman;
};

struct BOARD { 
    PLAYER *Active;
    PLAYER *Inactive;
    PIECE *b[8][8];
    int Depth;
};

#endif
