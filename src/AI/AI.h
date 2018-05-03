#ifndef AI_H
#define AI_H

#include "player.h"

class Ai : public Player
{
public:
  Ai(std::string name);
  virtual Tile *getSelectedTile() = 0;
  virtual Tile *selectTile(std::vector<Tile *> tiles) = 0;
  virtual Point selectMove(std::vector<Tile *> tiles, Layout layout) = 0;

protected:
  Tile *selectedTile;
  std::vector<Tile *> getOpponentAvailableMoves(Tile *tile, std::vector<Tile *> tiles);
  std::vector<Tile *> getOpponentDefendMoves(Tile *tile, std::vector<Tile *> tiles);
  std::vector<Tile *> getMyAvailableMoves(Tile *tile, std::vector<Tile *> tiles);
};

#endif // !AI_H
