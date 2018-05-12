#ifndef GRID_H
#define GRID_H

#include "window.h"
#include "tile.h"
#include "Pieces/Bishop.h"
#include "Pieces/Rook.h"
#include "Pieces/King.h"
#include "Pieces/Knight.h"
#include "Pieces/Queen.h"
#include "Pieces/Pawn.h"
#include "player.h"
#include "ai/ai.h"

#include <vector>
#include <unordered_set>

class Grid
{
  public:
    Grid(Window *window, Point origin, Point size, int mapSize, std::vector<Player*> players);
    ~Grid();

    int getWidth();
    int getHeight();

    Player* getCurrentPlayer();
    void render(float xPos, float yPos);
    void update(float dt);
    Tile* getSelectedTile();
    bool selectTile(Point point);
    Tile* canMovePiece(Point point);
    void movePiece(Tile* moveTile);

  private:
    Window *window;
    int mapSize;
    std::vector<Tile *> tiles;
    Tile *selectedTile;
    Orientation hexOrientation = layout_flat;
    Point hexSize;
    Point hexOrigin;
    std::vector<Player*> players;
    Player* currentPlayer;
    Player* otherPlayer;

    void fillBoard();
    void nextTurn();
    //int threadFunction(void * data);
};

#endif // !GRID_H
