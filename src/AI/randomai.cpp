#include "randomai.h"
#include "time.h"
RandomAi::RandomAi(std::string name) : Player(name),
                                       selectedTile(nullptr)
{
    srand(time(NULL));
}

Tile *
RandomAi::selectTile(std::vector<Tile *> tiles)
{
    //check if the king can be taken by the opponent
    for(auto tile : tiles)
    {
        if (tile->getPiece() && !hasPiece(tile->getPiece()))
        {
            std::vector<Tile *> availableMoves;
            for (auto move : tile->getPiece()->canMove(tile, tiles))
            {
                if (!move->getPiece() ||
                    hasPiece(move->getPiece()))
                {
                    availableMoves.push_back(move);
                }
            }
            for(auto move : availableMoves)
            {
                King* king;
                if (move->getPiece() &&
                    (king = dynamic_cast<King*>(move->getPiece())))
                {
                    Log::log("Randomai says: Help my king is beign taken and I don't know what to do!");
                }
            }
        }
    }

    //check if it can take any pieces
    for (auto tile : tiles)
    {
        if (hasPiece(tile->getPiece()))
        {
            std::vector<Tile *> availableMoves;
            for (auto move : tile->getPiece()->canMove(tile, tiles))
            {
                if (!move->getPiece() ||
                    !hasPiece(move->getPiece()))
                {
                    availableMoves.push_back(move);
                }
            }
            for(auto move : availableMoves)
            {
                if (move->getPiece())
                {
                    Log::log("Randomai says: Instead of a random move I will take your piece!");
                    selectedTile = tile;
                    return tile;
                }
            }
        }
    }

    // if it can't take any piece do a random move
    for (auto tile : tiles)
    {
        if (rand() % tiles.size() == 1 &&
            hasPiece(tile->getPiece()))
        {
            std::vector<Tile *> availableMoves;
            for (auto move : tile->getPiece()->canMove(tile, tiles))
            {
                if (!move->getPiece() ||
                    !hasPiece(move->getPiece()))
                {
                    availableMoves.push_back(move);
                }
            }
            if (availableMoves.size())
            {
                Log::log("Randomai says: If I don't know what I'm doing you won't either!");
                selectedTile = tile;
                return tile;
            }
        }
    }
    return selectTile(tiles);
}

Point RandomAi::selectMove(std::vector<Tile *> tiles, Layout layout)
{
    std::vector<Tile *> availableMoves;
    for (auto move : selectedTile->getPiece()->canMove(selectedTile, tiles))
    {
        if (move->getPiece() &&
            !hasPiece(move->getPiece()))
        {
            return hex_to_pixel(layout,
                        move->getHexTile()); // return immediately if it can take a piece
        }

        if (!move->getPiece() ||
            !hasPiece(move->getPiece()))
        {
            availableMoves.push_back(move);
        }
    }
    return hex_to_pixel(layout,
                        availableMoves[(rand() % availableMoves.size())]->getHexTile());
}

