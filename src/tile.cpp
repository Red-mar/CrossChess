#include "tile.h"

Tile::Tile(Window *window, int tileIndex, Point center, int size, Hex hexTile, Layout layout) : window(window),
                                                                                 tileIndex(tileIndex),
                                                                                hexagon(nullptr),
                                                                                hexTile(hexTile),
                                                                                piece(nullptr)
{
    std::vector<Point> points = polygon_corners(layout, hexTile);
    
    hexagon = new Hexagon(points[0], points[1], points[2], points[3], points[4], points[5]);
    if (rand() % 2 == 1)
    {
        piece = new Piece(window, "assets/unicorn.png");
    }

    
}
Tile::~Tile()
{
    if (hexagon)
    {
        delete hexagon;
    }
    if (piece)
    {
        delete piece;
    }
}

int Tile::getTileIndex()
{
    return tileIndex;
}

Hexagon *
Tile::getHexagon()
{
    return hexagon;
}

Hex
Tile::getHexTile()
{
    return hexTile;
}

Piece*
Tile::getPiece()
{
    return piece;
}

void
Tile::setPiece(Piece* npiece)
{
    piece = npiece;
}

void
Tile::removePiece()
{
    piece = nullptr; // NOTE: be careful don't want to lose the pointer
}

void Tile::render(float x, float y)
{
    window->drawHexagon(hexagon, color);
    if (piece)
    {
        piece->render(hexagon->points[4].x,hexagon->points[4].y); // TODO easiest for now; need to line it up properly
    }
}

void Tile::setColor(SDL_Color ncolor)
{
    color = ncolor;
}