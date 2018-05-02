#ifndef AI_H
#define AI_H

#include "player.h"

class Ai
{
  public:

    ~Ai();
    virtual Tile *getSelectedTile() = 0;
    virtual Tile *selectTile(std::vector<Tile *> tiles) = 0;
    virtual Point selectMove(std::vector<Tile *> tiles, Layout layout) = 0;

  protected:
    Tile *selectedTile;
};

#endif // !AI_H
