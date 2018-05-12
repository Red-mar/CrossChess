#include "player.h"

Player::Player(std::string name): name(name),
                                    turn(false)
{

}

Player::~Player()
{
    
}

void
Player::update(float dt)
{
    currentTurnTime -= dt * 1; 
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


bool
Player::hasTurn()
{
    return turn;
}

bool
Player::hasTurnEnded()
{
    return currentTurnTime < 0;
}

void
Player::setTurn(bool nturn)
{
    if (nturn) {
        currentTurnTime = turnTime;
    } else {
        currentTurnTime = 1000;
    }
    
    turn = nturn;
}

void
Player::setMove(Tile* nmove)
{
    selectedMove = nmove;
}

Tile*
Player::getMove()
{
    return selectedMove;
}