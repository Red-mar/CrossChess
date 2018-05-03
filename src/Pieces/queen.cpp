#include "queen.h"

Queen::Queen(Window *window, std::string filename) : Piece(window, filename, 9)
{
}

std::vector<Tile *>
Queen::canMove(Tile *currentTile, std::vector<Tile *> tiles) // TODO this is ridiculous
{
    std::vector<Tile *> result;

    for (auto tile : tiles)
    {
        if (currentTile == tile)
            continue;
        Hex tempHexLeft = tile->getHexTile();
        Hex tempHexRight = tile->getHexTile();
        bool visionBlocked = false;
        for (size_t i = 0; i < hex_distance(currentTile->getHexTile(), tile->getHexTile()); i++)
        {
            tempHexLeft = hex_add(tempHexLeft, hex_diagonals[0]);
            tempHexRight = hex_add(tempHexRight, hex_diagonals[3]);
            if (hex_diagonal_neighbor(currentTile->getHexTile(), 0) == tempHexLeft ||
                hex_diagonal_neighbor(currentTile->getHexTile(), 3) == tempHexRight)
            {
                int blockedTilesInLine = 0;                                                                  //I do not want to block the first piece
                for (auto tileInLine : hex_diagonal_linedraw(currentTile->getHexTile(), tile->getHexTile())) // NOTE: need seperate line for diagonals...
                {
                    if (blockedTilesInLine != 0)
                    {
                        visionBlocked = true;
                    }
                    for (auto tilePieceCheck : tiles)
                    {
                        if (tilePieceCheck->getHexTile() != currentTile->getHexTile() &&
                            tilePieceCheck->getHexTile() == tileInLine && // Find which tile matches the hex and if
                            tilePieceCheck->getPiece())                   // there is a piece on there, if yes vision is blocked
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
                if (!visionBlocked)
                {
                    result.push_back(tile);
                }
            }
        }
    }

    //NOTE need to seperate diagonal movement because of the different linedraw, not ideal

    for (auto tile : tiles)
    {
        bool visionBlocked = false;
        if (currentTile == tile)
            continue;
        if ((currentTile->getHexTile().r == tile->getHexTile().r ||
             currentTile->getHexTile().s == tile->getHexTile().s ||
             currentTile->getHexTile().q == tile->getHexTile().q))
        {
            int blockedTilesInLine = 0;                                                         //I do not want to block the first piece
            for (auto tileInLine : hex_linedraw(currentTile->getHexTile(), tile->getHexTile())) // TODO: make linedraw that returns vector<tile>
            {
                if (blockedTilesInLine != 0)
                {
                    visionBlocked = true;
                }
                for (auto tilePieceCheck : tiles)
                {
                    if (tilePieceCheck->getHexTile() != currentTile->getHexTile() &&
                        tilePieceCheck->getHexTile() == tileInLine && // Find which tile matches the hex and if
                        tilePieceCheck->getPiece())                   // there is a piece on there, if yes vision is blocked
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
            if (!visionBlocked)
            {
                result.push_back(tile);
            }
        }
    }

    return result;
}