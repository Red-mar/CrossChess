#include "bishop.h"

Bishop::Bishop(Window *window, std::string filename) : Piece(window, filename, 3)
{
}

std::vector<Tile *> Bishop::canMove(Tile *currentTile, std::vector<Tile *> tiles)
{
    std::vector<Tile *> result;

    for (auto tile : tiles)
    {
        if (currentTile == tile)
            continue;
        if ((currentTile->getHexTile().r == tile->getHexTile().r ||
             currentTile->getHexTile().s == tile->getHexTile().s))
        {
            bool visionBlocked = false;
            int blockedTilesInLine = 0;
            std::vector<Hex> hexLine = hex_linedraw(currentTile->getHexTile(), tile->getHexTile());
            for (auto it = hexLine.begin(); it != hexLine.end(); it++) // TODO: make linedraw that returns vector<tile>
            {
                if (blockedTilesInLine != 0)
                {
                    visionBlocked = true;
                }
                for (auto tilePieceCheck : tiles)
                {
                    if (tilePieceCheck->getHexTile() != currentTile->getHexTile() &&
                        tilePieceCheck->getHexTile() == (*it) && // Find which tile matches the hex and if
                        tilePieceCheck->getPiece())              // there is a piece on there, if yes vision is blocked
                    {
                        blockedTilesInLine++;

                        if (blockedTilesInLine == 1)
                        {
                            visionBlocked = false;
                        }
                        else
                        {
                            visionBlocked = true;
                        }
                    }
                }
                
            }
            if (!visionBlocked || blockedTilesInLine == 0)
            {
                result.push_back(tile);
            }
        }
    }

    return result;
}