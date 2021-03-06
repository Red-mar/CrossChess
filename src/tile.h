#ifndef TILE_H
#define TILE_H

class Piece;

#include "shapes.h"
#include "window.h"
#include "piece.h"

class Tile
{
  public:
    Tile(Window *window, Hex hexTile, Layout layout);
    Tile();
    ~Tile();

    Hexagon *getHexagon();
    Hex getHexTile();
    Piece *getPiece();
    void setPiece(Piece *npiece);
    void removePiece();

    void setSelected(bool nselect);

    void render(float x, float y);
    void setColor(SDL_Color ncolor);

  private:
    Window *window;
    Hexagon *hexagon;
    Hex hexTile;
    SDL_Color color = {0, 255, 0, 255};
    int tileIndex;
    Piece *piece;
    bool isSelected;
};

#endif // !TILE_H
