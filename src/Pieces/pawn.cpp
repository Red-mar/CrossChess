#include "pawn.h"

Pawn::Pawn(Window *window, std::string filename) : Piece(window, filename),
                                                   maxMovement(1)
{
}

bool Pawn::canMove(Tile* currentHex, Tile* moveToHex)
{
    return (hex_distance(currentHex->getHexTile(), moveToHex->getHexTile()) <= maxMovement &&
            hex_add(currentHex->getHexTile(), hex_direction(2)) == moveToHex->getHexTile() &&
            moveToHex->getPiece() == nullptr); // checks if the direction is correct
}