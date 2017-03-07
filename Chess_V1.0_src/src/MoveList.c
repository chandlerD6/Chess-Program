/* Jesse Campbell	January 17 */

#include "Constants.h"
#include "MoveList.h"
#include "Move.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

MLIST *CreateMoveList(void)
{
	MLIST *moveList;
	moveList = malloc(sizeof(MLIST));
	if (!moveList)
	{
		perror("Out of memory! Aborting...");
		exit(10);
	}
	moveList->Length = 0;
	moveList->First = NULL;
	return moveList;
}

void EmptyMoveList(MLIST *moveList)
{
	MENTRY *e, *n;
	MOVE *move;
	
	assert(moveList);
	e = moveList->First;
	while (e)
	{
		n = e->Next;
		move = DeleteMoveEntry(e);
		DeleteMove(move);
		e = n;
	}
    moveList->Length = 0;
}

void DeleteMoveList(MLIST *moveList)
{
    assert(moveList);
    EmptyMoveList(moveList);
    free(moveList);
}

void SortMoveList(MLIST *moveList)
{
    MENTRY *p, *e, *n;
    e = p = moveList->First;
    while (e)
    {
        n = e->Next;
        if (moveList->Length >= 2 && e->Move->isCapture == 1)
        {
            e->Next = moveList->First;
            moveList->First = e;
            p->Next = n;
        } else {
            p = e;
        }
        e = n;
    }
}

MENTRY *CreateMoveEntry(MOVE *move)
{
	MENTRY *e;
	assert(move);
	e = malloc(sizeof(MENTRY));
	if (!e)
	{
		perror("Out of memory! Aborting...");
		exit(10);
	}
	e->List = NULL;
	e->Next = NULL;
	e->Move = move;
	return e;
}

MOVE *DeleteMoveEntry(MENTRY *e)
{
	MOVE *move;
	assert(e);
	move = e->Move;
    e->List->First = e->Next;
	free(e);
	return move;
}

void AppendMove(MLIST *moveList, MOVE *move)
{
	MENTRY *e;
	assert(moveList);
	assert(move);
	e = CreateMoveEntry(move);
	if (moveList->First)
	{
		e->List = moveList;
		e->Next = moveList->First;
		moveList->First = e;
	} else {
		e->List = moveList;
		e->Next = NULL;
		moveList->First = e;
	}
	moveList->Length++;	
}
