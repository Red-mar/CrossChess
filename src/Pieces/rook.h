#ifndef ROOK_H
#define ROOK_H

#include "piece.h"

/* The rook can move diagonaly left and right
 * and can move to neighboring tiles up and
 * down. also he is able to move to any
 * neighboring tiles for 1 step
 */
class Rook : public Piece
{
    public:
        Rook(Window* window, std::string filename);

        std::vector<Tile*> canMove(Tile* currentTile, std::vector<Tile*> tiles);
    private:
};

#endif // !ROOK_H