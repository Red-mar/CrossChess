#include "tile.h"

Tile::Tile(Window *window, Hex hexTile, Layout layout) : window(window),
                                                                                                tileIndex(tileIndex),
                                                                                                hexagon(nullptr),
                                                                                                hexTile(hexTile),
                                                                                                piece(nullptr),
                                                                                                isSelected(false)
{
    std::vector<Point> points = polygon_corners(layout, hexTile);

    hexagon = new Hexagon(points[0], points[1], points[2], points[3], points[4], points[5]);
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

Hexagon *
Tile::getHexagon()
{
    return hexagon;
}

Hex Tile::getHexTile()
{
    return hexTile;
}

Piece *
Tile::getPiece()
{
    return piece;
}

void Tile::setPiece(Piece *npiece)
{
    piece = npiece;
}

void Tile::removePiece()
{
    piece = nullptr; // NOTE: be careful don't want to lose the pointer
}

void Tile::render(float x, float y)
{
    if (isSelected)
    {
        window->drawFilledHexagon(hexagon, color);
    }
    else
    {
        window->drawHexagon(hexagon, color);
    }

    if (piece)
    {
        piece->render((float)hexagon->points[4].x - 3, (float)hexagon->points[4].y + 5); // TODO easiest for now; need to line it up properly
    }
}

void Tile::setColor(SDL_Color ncolor)
{
    color = ncolor;
}

void Tile::setSelected(bool nselect)
{
    isSelected = nselect;
}