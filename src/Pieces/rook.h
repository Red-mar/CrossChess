#ifndef ROOK_H
#define ROOK_H

#include "piece.h"

class Rook : public Piece
{
    public:
        Rook(Window* window, std::string filename);

        bool canMove(Tile* currentHex, Tile* moveToHex);
    private:
};

#endif // !ROOK_H
