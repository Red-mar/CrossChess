#ifndef PIECE_H
#define PIECE_H

#include "sprite.h"

class Tile;

#include "tile.h"

class Piece : public Sprite
{
    public:
        Piece(Window * window, std::string filename);
        ~Piece();

        std::string getFilename();
        virtual bool canMove(Tile* currentHex, Tile* moveToHex) = 0;

    private:
        std::string filename;
};

#endif // !PIECE_H
