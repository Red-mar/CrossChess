#include "randomai.h"
#include "time.h"
RandomAi::RandomAi(std::string name) : Ai(name)
{
    srand(time(NULL));
    selectedTile = nullptr;
}

Tile *
RandomAi::selectTile(std::vector<Tile *> tiles)
{
    //check if the king can be taken by the opponent

    for (auto tile : tiles)
    {
        if (tile->getPiece() && !hasPiece(tile->getPiece()))
        {
            std::vector<Tile *> availableMoves = getOpponentAvailableMoves(tile, tiles);
            for (auto move : availableMoves)
            {
                King *king;
                if (move->getPiece() &&
                    (king = dynamic_cast<King *>(move->getPiece())))
                {
                    std::vector<Tile *> availableMoves;
                    for (auto kingMoves : king->canMove(move, tiles))
                    {
                        if (!kingMoves->getPiece() ||
                            !hasPiece(kingMoves->getPiece()))
                        {
                            availableMoves.push_back(kingMoves);
                        }
                    }
                    for (auto myMoves : availableMoves)
                    {
                        if (myMoves->getPiece())
                        {
                            //check if when it takes another piece his piece could be taken
                            bool pieceIsDefended = false;
                            for (auto opponentTile : tiles)
                            {
                                if (opponentTile->getPiece() && !hasPiece(opponentTile->getPiece()))
                                {
                                    for (auto opponentMove : getOpponentDefendMoves(opponentTile, tiles))
                                    {
                                        if (opponentMove == myMoves)
                                        {
                                            pieceIsDefended = true;
                                        }
                                    }
                                }
                            }

                            if (!pieceIsDefended)
                            {
                                Log::log("Randomai says: have to move king!");
                                selectedTile = move;
                                return move;
                            }
                        }
                        else
                        {
                            bool tileIsDefended = false;
                            for (auto opponentTile : tiles)
                            {
                                if (opponentTile->getPiece() && !hasPiece(opponentTile->getPiece()))
                                {
                                    for (auto opponentMove : getOpponentAvailableMoves(opponentTile, tiles))
                                    {
                                        if (opponentMove == myMoves)
                                        {
                                            Log::log("Randomai says: I could move there but my piece would be taken!");
                                            tileIsDefended = true;
                                        }
                                    }
                                }
                            }
                            if (!tileIsDefended)
                            {
                                Log::log("Randomai says: have to move king!");
                                selectedTile = move;
                                return move;
                            }
                        }
                    }

                    Log::log("Randomai says: Help my king is being taken and I don't know what to do!");
                }
            }
        }
    }

    //check if it can take any pieces
    for (auto tile : tiles)
    {
        if (hasPiece(tile->getPiece()))
        {
            std::vector<Tile *> availableMoves;
            for (auto move : tile->getPiece()->canMove(tile, tiles))
            {
                if (!move->getPiece() ||
                    !hasPiece(move->getPiece()))
                {
                    availableMoves.push_back(move);
                }
            }
            for (auto move : availableMoves)
            {
                if (move->getPiece())
                {
                    //check if when it takes another piece his piece could be taken
                    bool pieceIsDefended = false;
                    for (auto opponentTile : tiles)
                    {
                        if (opponentTile->getPiece() && !hasPiece(opponentTile->getPiece()))
                        {
                            for (auto opponentMove : getOpponentDefendMoves(opponentTile, tiles))
                            {
                                if (opponentMove == move)
                                {
                                    if (opponentTile->getPiece()->getRelativeValue() < tile->getPiece()->getRelativeValue())
                                    {
                                        pieceIsDefended = true;
                                    }
                                }
                            }
                        }
                    }

                    if (!pieceIsDefended)
                    {
                        Log::log("Randomai says: Instead of a random move I will take your piece!");
                        selectedTile = tile;
                        return tile;
                    }
                }
            }
        }
    }

    // if it can't take any piece do a random move
    std::vector<Tile *> availablePieces;
    for (auto tile : tiles)
    {
        if (hasPiece(tile->getPiece()))
        {
            availablePieces.push_back(tile);
        }
    }
    bool pieceFound = false;
    Tile *randomPiece;
    while (!pieceFound) // should be an easier way to get a random viable piece move
    {
        randomPiece = availablePieces[rand() % availablePieces.size()];
        std::vector<Tile *> availableMoves;
        for (auto move : randomPiece->getPiece()->canMove(randomPiece, tiles))
        {
            if (!move->getPiece())
            {
                bool tileIsDefended = false;
                for (auto opponentTile : tiles)
                {
                    if (opponentTile->getPiece() && !hasPiece(opponentTile->getPiece()))
                    {
                        for (auto opponentMove : getOpponentAvailableMoves(opponentTile, tiles))
                        {
                            if (opponentMove == move)
                            {
                                Log::log("Randomai says: I could move there but my piece would be taken!");
                                tileIsDefended = true;
                            }
                        }
                    }
                }
                if (!tileIsDefended)
                {
                    availableMoves.push_back(move);
                }
            }
        }
        if (availableMoves.size())
        {
            Log::log("Randomai says: If I don't know what I'm doing you won't either!");
            selectedTile = randomPiece;
            pieceFound = true;
        }
    }
    return randomPiece;
}

Point RandomAi::selectMove(std::vector<Tile *> tiles, Layout layout)
{
    std::vector<Tile *> availableMoves;
    for (auto move : selectedTile->getPiece()->canMove(selectedTile, tiles))
    {
        if (move->getPiece() &&
            !hasPiece(move->getPiece()))
        {
            return hex_to_pixel(layout,
                                move->getHexTile()); // return immediately if it can take a piece
        }

        if (!move->getPiece() ||
            !hasPiece(move->getPiece()))
        {
            availableMoves.push_back(move);
        }
    }
    return hex_to_pixel(layout,
                        availableMoves[(rand() % availableMoves.size())]->getHexTile());
}

Tile *
RandomAi::getSelectedTile()
{
    return selectedTile;
}
