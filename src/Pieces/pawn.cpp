#include "pawn.h"

Pawn::Pawn(Window *window, std::string filename) : Piece(window, filename),
                                                   maxMovement(1)
{
}

std::vector<Tile*> Pawn::canMove(Tile* currentTile, std::vector<Tile*> tiles)
{
    std::vector<Tile*> result;

    for(auto tile : tiles)
    {
        if (hex_distance(currentTile->getHexTile(), tile->getHexTile()) <= maxMovement &&
            hex_add(currentTile->getHexTile(), hex_direction(2)) == tile->getHexTile() &&
            tile->getPiece() == nullptr)
        {
            result.push_back(tile);
        }
    }

    return result;
}