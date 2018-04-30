#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h"

class Queen : public Piece
{
  public:
    Queen(Window *window, std::string filename);

    std::vector<Tile *> canMove(Tile *currentTile, std::vector<Tile *> tiles);

  private:
};

#endif // !QUEEN_H
