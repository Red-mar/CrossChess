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

    fillBoard();
}

Grid::~Grid()
{
    for (auto tile : tiles)
    {
        delete tile;
    }
}

void Grid::fillBoard()
{
    for (auto tile : tiles)
    {
        if (rand() % 5 == 1)
        {
            tile->setPiece(new Rook(window, "assets/unicorn.png"));
        }
    }
}

Tile *
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
            {
                for (auto tile : tiles)
                {
                    tile->setSelected(false);
                    tile->setColor({0, 255, 0, 255});
                }
            }

            selectedTile = tile;
            selectedTile->setSelected(true);
            if (selectedTile->getPiece())
            {
                Log::debug("current piece is " + selectedTile->getPiece()->getFilename());

                for (auto tile : selectedTile->getPiece()->canMove(selectedTile, tiles))
                {
                    tile->setSelected(true);
                    tile->setColor({0, 255, 0, 55});
                }
            }
            else
            {
                Log::debug("current piece is nullptr");
            }

            tile->setColor({255, 0, 0, 55});
            break;
        }
    }
    if (!succes)
    {
        //selectedTile->setColor({0, 255, 0, 255});
        //selectedTile->setSelected(false);
        for (auto tile : tiles)
        {
            tile->setSelected(false);
            tile->setColor({0, 255, 0, 255});
        }
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

        for (auto tile : selectedTile->getPiece()->canMove(selectedTile, tiles))
        {
            if (tile->getHexTile() == clickHex)
            {
                succes = true;
                if (selectedTile)
                {
                    for (auto tile : tiles)
                    {
                        tile->setSelected(false);
                        tile->setColor({0, 255, 0, 255});
                    }
                }
                tile->setPiece(selectedTile->getPiece());
                selectedTile->removePiece();
                selectedTile->setSelected(false);
                selectedTile = nullptr;
                break;
            }
        }
    }
    if (!succes)
    {
        for (auto tile : tiles)
        {
            tile->setSelected(false);
            tile->setColor({0, 255, 0, 255});
        }
        selectedTile = nullptr;
    }
    return succes;
}
