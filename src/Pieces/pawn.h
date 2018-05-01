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
        Pawn(Window* window, std::string filename);

        std::vector<Tile*> canMove(Tile* currentTile, std::vector<Tile*> tiles);
    private:
        int maxMovement;
};

#endif // !PAWN_H
