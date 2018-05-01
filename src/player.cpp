#include "player.h"

Player::Player(std::string name): name(name)
{

}

std::string
Player::getName()
{
    return name;
}

void
Player::addPiece(Piece* piece)
{
    pieces.push_back(piece);
}

bool
Player::hasPiece(Piece* piece)
{
    return (std::find(pieces.begin(), pieces.end(), piece) != pieces.end());
}