/* Jesse Campbell	January 17 */
#ifndef MOVELIST_H_
#define MOVELIST_H_
MLIST *CreateMoveList(void);
void EmptyMoveList(MLIST *moveList);
void DeleteMoveList(MLIST *moveList);
void SortMoveList(MLIST *moveList);
MENTRY *CreateMoveEntry(MOVE *move);
MOVE *DeleteMoveEntry(MENTRY *e);
void AppendMove(MLIST *moveList, MOVE *move);
#endif
