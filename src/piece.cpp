#include "piece.h"

Piece::Piece(Window * window, std::string filename, int relativeValue) : Sprite(window, filename),
    filename(filename),
    relativeValue(relativeValue)
{
    
}

Piece::~Piece()
{
    
}

std::string
Piece::getFilename()
{
    return filename;
}

int
Piece::getRelativeValue()
{
    return relativeValue;
}