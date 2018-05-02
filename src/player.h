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

        std::string getName();
        void addPiece(Piece* npiece);
        void removePiece(Piece* piece);
        bool hasPiece(Piece* piece);
        bool hasKing();

    private:
        std::string name;
        std::vector<Piece*> pieces;
};

#endif // PLAYER_H
