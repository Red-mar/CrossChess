#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include "piece.h"
#include "Pieces/King.h"

class Player
{
  public:
    Player(std::string name);
    virtual ~Player();

    std::string getName();
    void addPiece(Piece *npiece);
    void removePiece(Piece *piece);
    bool hasPiece(Piece *piece);
    bool hasKing();
    bool hasTurn();
    bool hasTurnEnded();
    void setTurn(bool nturn);
    void startTurn();
    void setMove(Tile* nmove);
    Tile* getMove();
    virtual void update(float dt);

  protected:
    bool turn;
    float currentTurnTime = 0;
    float turnTime = 10;
    Tile* selectedMove;
    std::string name;
    std::vector<Piece *> pieces;
};

#endif // PLAYER_H
