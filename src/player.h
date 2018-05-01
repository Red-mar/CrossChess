#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include "piece.h"

class Player
{
    public:
        Player(std::string name);

        std::string getName();
        void addPiece(Piece* npiece);
        bool hasPiece(Piece* piece);

    private:
        std::string name;
        std::vector<Piece*> pieces;
};

#endif // PLAYER_H
