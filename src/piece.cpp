#include "piece.h"

Piece::Piece(Window * window, std::string filename) : Sprite(window, filename),
    filename(filename)
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