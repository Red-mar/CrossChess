#ifndef KNIGHT_H
#define KNIGHT_H

#include "piece.h"

/* The knight can move in this weird pattern
 *
 * 
 */
class Knight : public Piece
{
  public:
    Knight(Window *window, std::string filename);

    std::vector<Tile *> canMove(Tile *currentTile, std::vector<Tile *> tiles);

  private:
    const std::vector<Hex> possibleMoves = {
        Hex(-1, -1, -1), Hex(1, -2, -2), Hex(3, -2, -2),
        Hex(3, -1, -1), Hex(-1, 2, 2), Hex(1, 1, 1),
        Hex(-3, 1, 1), Hex(-3, 2, 2)};
};

#endif // !KNIGHT_H
