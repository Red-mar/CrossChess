#ifndef PAWN_H
#define PAWN_H

#include "piece.h"

class Pawn : public Piece
{
    public:
        Pawn(Window* window, std::string filename);

        bool canMove(Tile* currentHex, Tile* hexToMove);
    private:
        int maxMovement;
};

#endif // !PAWN_H
