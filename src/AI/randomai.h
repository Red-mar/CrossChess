#ifndef RANDOMAI_H
#define RANDOMAI_H

#include "ai.h"

class RandomAi : public Player, public Ai
{
    public:
        RandomAi(std::string name);

        Tile* selectTile(std::vector<Tile*> tiles);
        Point selectMove(std::vector<Tile*> tiles, Layout layout);

    private:
        Tile* selectedTile;
};

#endif // !RANDOMAI_H
