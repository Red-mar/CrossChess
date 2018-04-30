#include "grid.h"
#include <algorithm>
#include "log.h"

Grid::Grid(Window *window, Point origin, Point size, int mapSize) : window(window),
                                                                    mapSize(mapSize),
                                                                    hexSize(size),
                                                                    hexOrigin(origin),
                                                                    selectedTile(nullptr)
{
    for (int q = -mapSize; q <= mapSize; q++)
    {
        int r1 = std::max(-mapSize, -q - mapSize);
        int r2 = std::min(mapSize, -q + mapSize);
        for (int r = r1; r <= r2; r++)
        {
            tiles.push_back(new Tile(window, 0, Point(q * (2 * 25), (r * (sqrt(3) * 25))), 25, Hex(q, r, -q - r), {hexOrientation, hexSize, hexOrigin}));
        }
    }
}

Grid::~Grid()
{
    for (auto tile : tiles)
    {
        delete tile;
    }
}

Tile*
Grid::getSelectedTile()
{
    return selectedTile;
}

void Grid::render(float xPos, float yPos)
{
    for (auto tile : tiles)
    {
        tile->render(xPos, yPos);
    }
}

bool Grid::selectTile(Point point)
{
    bool succes = false;
    Hex clickHex = hex_round(pixel_to_hex({hexOrientation, hexSize, hexOrigin}, point));

    for (auto tile : tiles)
    {
        if (tile->getHexTile() == clickHex)
        {
            succes = true;
            if (selectedTile)
                selectedTile->setColor({0, 255, 0, 255});
            selectedTile = tile;
            if (selectedTile->getPiece())
            {
                Log::debug("current piece is " + selectedTile->getPiece()->getFilename());
            }
            else
            {
                Log::debug("current piece is nullptr");
            }

            tile->setColor({255, 0, 0, 255});
            break;
        }
        else
        {
        }
    }
    if (!succes)
    {
        selectedTile->setColor({0, 255, 0, 255});
        selectedTile = nullptr;
    }
    return succes;
}

bool Grid::movePiece(Point point)
{
    bool succes = false;
    if (!selectedTile->getPiece())
    {
        Log::debug("no piece to move");
        succes = false;
    }
    else
    {
        Hex clickHex = hex_round(pixel_to_hex({hexOrientation, hexSize, hexOrigin}, point));
        for (auto tile : tiles)
        {
            if (tile->getHexTile() == clickHex &&
                tile->getPiece() == nullptr)
            {
                succes = true;
                tile->setPiece(selectedTile->getPiece());
                selectedTile->removePiece();
                selectedTile = tile;
            }
            else
            {
            }
        }
    }
    return succes;
}
