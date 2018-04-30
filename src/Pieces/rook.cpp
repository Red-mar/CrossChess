#include "rook.h"

Rook::Rook(Window *window, std::string filename) : Piece(window, filename)
{
}

std::vector<Tile *>
Rook::canMove(Tile *currentTile, std::vector<Tile *> tiles)
{
    std::vector<Tile *> result;

    for (auto tile : tiles)
    {
        if (currentTile == tile)
            continue;
        Hex tempHexLeft = tile->getHexTile();
        Hex tempHexRight = tile->getHexTile();

        for (size_t i = 0; i < hex_distance(currentTile->getHexTile(), tile->getHexTile()); i++)
        {
            tempHexLeft = hex_add(tempHexLeft, hex_diagonals[0]);
            tempHexRight = hex_add(tempHexRight, hex_diagonals[3]);
            if (hex_diagonal_neighbor(currentTile->getHexTile(), 0) == tempHexLeft ||
                hex_diagonal_neighbor(currentTile->getHexTile(), 3) == tempHexRight &&
                    tile->getPiece() == nullptr)
            {
                bool visionBlocked = false;
                for (auto tileInLine : hex_diagonal_linedraw(currentTile->getHexTile(), tile->getHexTile())) // TODO: make linedraw that returns vector<tile>
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
    }

    for (auto tile : tiles)
    {
        if (currentTile == tile)
            continue;
        if (((currentTile->getHexTile().r == tile->getHexTile().r && (hex_distance(currentTile->getHexTile(), tile->getHexTile()) <= 1)) ||
             (currentTile->getHexTile().s == tile->getHexTile().s && (hex_distance(currentTile->getHexTile(), tile->getHexTile()) <= 1)) ||
             currentTile->getHexTile().q == tile->getHexTile().q) &&
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