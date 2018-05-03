#include "king.h"

King::King(Window *window, std::string filename) : Piece(window, filename,10)
{}

std::vector<Tile *>
King::canMove(Tile *currentTile, std::vector<Tile *> tiles)
{
    std::vector<Tile *> result;

    for (auto tile : tiles)
    {
        if ((std::find(hex_directions.begin(), hex_directions.end(), hex_subtract(currentTile->getHexTile(), tile->getHexTile())) != hex_directions.end() ||
            hex_diagonal_neighbor(currentTile->getHexTile(), 0) == tile->getHexTile() ||
            hex_diagonal_neighbor(currentTile->getHexTile(), 3) == tile->getHexTile()))
        {
            result.push_back(tile);
        }
    }

    return result;
}