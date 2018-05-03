#ifndef PIECE_H
#define PIECE_H

#include "sprite.h"

class Tile;

#include "tile.h"

class Piece : public Sprite
{
    public:
        Piece(Window * window, std::string filename, int relativeValue);
        ~Piece();

        std::string getFilename();
        virtual std::vector<Tile*> canMove(Tile* currentTile, std::vector<Tile*> tiles) = 0;

        int getRelativeValue();

    protected:
        std::string filename;
        //https://en.wikipedia.org/wiki/Chess_piece_relative_value
        const int relativeValue;
};

#endif // !PIECE_H
