#include "ai.h"

Ai::Ai(std::string name) : Player(name)
{
}


std::vector<Tile *>
Ai::getOpponentAvailableMoves(Tile* tile, std::vector<Tile *> tiles)
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
    return availableMoves;
}

std::vector<Tile *>
Ai::getOpponentDefendMoves(Tile* tile, std::vector<Tile *> tiles)
{
    std::vector<Tile *> availableMoves;
    for (auto move : tile->getPiece()->canMove(tile, tiles))
    {
        if (move->getPiece() &&
            !hasPiece(move->getPiece()))
        {
            availableMoves.push_back(move);
        }
    }
    return availableMoves;
}

std::vector<Tile *>
Ai::getMyAvailableMoves(Tile* tile, std::vector<Tile *> tiles)
{
    std::vector<Tile *> availableMoves;

    return availableMoves;
}