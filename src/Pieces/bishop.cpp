#include "bishop.h"

Bishop::Bishop(Window *window, std::string filename) : Piece(window, filename)
{
}

std::vector<Tile *> Bishop::canMove(Tile *currentTile, std::vector<Tile *> tiles)
{
    std::vector<Tile *> result;

    for (auto tile : tiles)
    {
        if (currentTile == tile) continue;
        if ((currentTile->getHexTile().r == tile->getHexTile().r ||
             currentTile->getHexTile().s == tile->getHexTile().s) &&
            tile->getPiece() == nullptr)
        {
            bool visionBlocked = false;
            for (auto tileInLine : hex_linedraw(currentTile->getHexTile(), tile->getHexTile())) // TODO: make linedraw that returns vector<tile>
            {
                for (auto tilePieceCheck : tiles)
                {
                    if (tilePieceCheck->getHexTile() != currentTile->getHexTile() && 
                        tilePieceCheck->getHexTile() == tileInLine && // Find which tile matches the hex and if
                        tilePieceCheck->getPiece())                   // there is a piece on there, if yes vision is blocked
                    {
                        visionBlocked = true;
                    }
                }
            }
            if (!visionBlocked)
            {
                result.push_back(tile);
            }
        }
    }

    return result;
}