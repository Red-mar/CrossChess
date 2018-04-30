#ifndef PIECE_H
#define PIECE_H

#include "sprite.h"

class Piece : public Sprite
{
    public:
        Piece(Window * window, std::string filename);
        ~Piece();

        std::string getFilename();

    private:
        std::string filename;
};

#endif // !PIECE_H
