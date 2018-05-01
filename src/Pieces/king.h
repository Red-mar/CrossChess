#ifndef KING_H
#define KING_H

#include "piece.h"


/* The King can move in every neighboring hex
 * however diagonaly he can only move directly
 * to the left or right
 */
class King : public Piece
{
    public:
        King(Window *window, std::string filename);

        std::vector<Tile *> canMove(Tile *currentTile, std::vector<Tile*> tiles);

    private:
};

#endif // !KING_H
