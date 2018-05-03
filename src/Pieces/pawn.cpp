#include "pawn.h"

Pawn::Pawn(Window *window, std::string filename, Direction direction) : Piece(window, filename, 1), direction(direction)
{
}

std::vector<Tile *> Pawn::canMove(Tile *currentTile, std::vector<Tile *> tiles)
{
    std::vector<Tile *> result;
    Direction hitLeft;
    Direction hitRight;

    for (auto tile : tiles)
    {
        if (hex_distance(currentTile->getHexTile(), tile->getHexTile()) <= 1 &&
            hex_add(currentTile->getHexTile(), hex_direction(direction)) == tile->getHexTile() &&
            tile->getPiece() == nullptr)
        {
            result.push_back(tile);
        }
        else if (direction == BLACK)
        {
            hitLeft = BLACK_LEFT;
            hitRight = BLACK_RIGHT;
        }
        else
        {
            hitLeft = WHITE_LEFT;
            hitRight = WHITE_RIGHT;
        }

        if (hex_distance(currentTile->getHexTile(), tile->getHexTile()) <= 1)
        {
            if (hex_add(currentTile->getHexTile(), hex_direction(hitLeft)) == tile->getHexTile() &&
                tile->getPiece())
            {
                result.push_back(tile);
            }
            else if (hex_add(currentTile->getHexTile(), hex_direction(hitRight)) == tile->getHexTile() &&
                     tile->getPiece())
            {
                result.push_back(tile);
            }
        }
    }

    return result;
}