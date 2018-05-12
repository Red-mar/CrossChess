#ifndef RANDOMAI_H
#define RANDOMAI_H

#include "ai.h"
#include "log.h"

class RandomAi : public Ai
{
  public:
    RandomAi(std::string name);

    Tile *getSelectedTile();
    Tile *selectTile(std::vector<Tile *> tiles);
    Point selectMove(std::vector<Tile *> tiles, Layout layout);

    void update(float dt);
};

#endif // !RANDOMAI_H
