#ifndef GRID_H
#define GRID_H

#include "window.h"
#include "tile.h"
#include "Pieces/rook.h"

#include <vector>
#include <unordered_set>

class Grid
{
  public:
    Grid(Window *window, Point origin, Point size, int mapSize);
    ~Grid();

    int getWidth();
    int getHeight();

    void render(float xPos, float yPos);
    Tile* getSelectedTile();
    bool selectTile(Point point);
    bool movePiece(Point point);

  private:
    Window *window;
    int mapSize;
    std::vector<Tile *> tiles;
    Tile *selectedTile;
    std::unordered_set<Hex> map;
    Orientation hexOrientation = layout_flat;
    Point hexSize;
    Point hexOrigin;

    void fillBoard();
};

#endif // !GRID_H
