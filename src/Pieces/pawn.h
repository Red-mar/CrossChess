#ifndef PAWN_H
#define PAWN_H

#include "piece.h"

/* The pawn can move only one tile forward
 * depending on which player it belongs to
 * it should go forward or backwards.
 */
class Pawn : public Piece
{
    public:
        enum Direction
        {
            BLACK_LEFT = 0,
            WHITE_RIGHT = 1,
            WHITE = 2,
            WHITE_LEFT = 3,
            BLACK_RIGHT = 4,
            BLACK = 5,
            MAX_DIRECTIONS = 6
        };

        Pawn(Window* window, std::string filename, Direction direction);

        std::vector<Tile*> canMove(Tile* currentTile, std::vector<Tile*> tiles);
    private:
        Direction direction;
};

#endif // !PAWN_H
