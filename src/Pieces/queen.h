#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h"

/* The queen can move in any direction
 * diagonaly or to neighboring tiles
 */
class Queen : public Piece
{
  public:
    Queen(Window *window, std::string filename);

    std::vector<Tile *> canMove(Tile *currentTile, std::vector<Tile *> tiles);

  private:
};

#endif // !QUEEN_H
