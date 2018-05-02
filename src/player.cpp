#include "player.h"

Player::Player(std::string name): name(name)
{

}

Player::~Player()
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

void
Player::removePiece(Piece* piece)
{
    if (piece)
    {
        pieces.erase(std::remove(pieces.begin(), pieces.end(), piece), pieces.end());
    }
}

bool
Player::hasPiece(Piece* piece)
{
    return (std::find(pieces.begin(), pieces.end(), piece) != pieces.end());
}

bool
Player::hasKing()
{
    for(auto piece : pieces)
    {
        if(!piece) continue;
        if (King* king = dynamic_cast<King*>(piece)) // very expensive
        {
            return true;
        }
    }
    
    return false;
}