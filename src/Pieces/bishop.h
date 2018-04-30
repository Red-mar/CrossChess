#ifndef BISHOP_H
#define BISHOP_H

#include "piece.h"

class Bishop : public Piece
{
    public:
        Bishop(Window* window, std::string filename);

        std::vector<Tile*> canMove(Tile* currentTile, std::vector<Tile*> tiles);
    private:
};

#endif // !BISHOP_H
