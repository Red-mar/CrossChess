#ifndef RANDOMAI_H
#define RANDOMAI_H

#include "ai.h"
#include "log.h"

class RandomAi : public Player, public Ai
{
  public:
    RandomAi(std::string name);

    Tile *getSelectedTile();
    Tile *selectTile(std::vector<Tile *> tiles);
    Point selectMove(std::vector<Tile *> tiles, Layout layout);
};

#endif // !RANDOMAI_H
