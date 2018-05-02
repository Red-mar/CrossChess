#include "randomai.h"
RandomAi::RandomAi(std::string name) : Player(name),
                                       selectedTile(nullptr)
{
}

Tile *
RandomAi::selectTile(std::vector<Tile *> tiles)
{
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
                    selectedTile = tile;
                    return tile;
                }
            }
        }
    }

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
        if (!move->getPiece() ||
            !hasPiece(move->getPiece()))
        {
            availableMoves.push_back(move);
        }
    }
    return hex_to_pixel(layout,
                        availableMoves[(rand() % availableMoves.size())]->getHexTile());
}

