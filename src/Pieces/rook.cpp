#include "rook.h"

Rook::Rook(Window *window, std::string filename) : Piece(window, filename)
{
}

bool Rook::canMove(Tile *currentHex, Tile *moveToHex)
{
    bool canMove = false;

    if (currentHex->getHexTile().r == moveToHex->getHexTile().r ||
        currentHex->getHexTile().s == moveToHex->getHexTile().s)
    {
        canMove = true;
    }

/*
    for (int direction = 0; direction < 5; direction++)
    {
        if(direction == 2 || direction == 5) continue;
        Hex tempHex = currentHex->getHexTile();
        for (int i = 0; i < 15; i++)
        {
            if (tempHex == moveToHex->getHexTile())
            {
                canMove = true;
            }
            tempHex = hex_add(tempHex, hex_direction(direction));
        }
    }*/

    return (canMove && !moveToHex->getPiece());

/*
    return (
        (
            hex_add(currentHex->getHexTile(), hex_direction(1)) == moveToHex->getHexTile() ||
            hex_add(currentHex->getHexTile(), hex_direction(3)) == moveToHex->getHexTile() ||
            hex_add(currentHex->getHexTile(), hex_direction(4)) == moveToHex->getHexTile() ||
            hex_add(currentHex->getHexTile(), hex_direction(0)) == moveToHex->getHexTile()) &&
        moveToHex->getPiece() == nullptr); // checks if the direction is correct*/
}