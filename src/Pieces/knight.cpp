#include "knight.h"

Knight::Knight(Window *window, std::string filename) : Piece(window, filename, 3)
{
}

std::vector<Tile *>
Knight::canMove(Tile *currentTile, std::vector<Tile *> tiles)
{
    std::vector<Tile *> result;

    for (auto tile : tiles)
    {
        Hex h = hex_subtract(tile->getHexTile(), currentTile->getHexTile());
        if (std::find(possibleMoves.begin(), possibleMoves.end(), hex_subtract(tile->getHexTile(), currentTile->getHexTile())) != possibleMoves.end())
        {
            result.push_back(tile);
        }
    }

    return result;
}