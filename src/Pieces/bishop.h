#ifndef BISHOP_H
#define BISHOP_H

#include "piece.h"

/* The bishop can move to any
 * neighboring 'diagonal' tiles
 * basicly the r and s coordinates
 */
class Bishop : public Piece
{
    public:
        Bishop(Window* window, std::string filename);

        std::vector<Tile*> canMove(Tile* currentTile, std::vector<Tile*> tiles);
    private:
};

#endif // !BISHOP_H
