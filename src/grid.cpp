#include "grid.h"
#include <algorithm>
#include "log.h"

Grid::Grid(Window *window, Point origin, Point size, int mapSize, std::vector<Player *> players) : window(window),
                                                                                                   mapSize(mapSize),
                                                                                                   hexSize(size),
                                                                                                   hexOrigin(origin),
                                                                                                   selectedTile(nullptr),
                                                                                                   players(players),
                                                                                                   currentPlayer(players[0]),
                                                                                                   otherPlayer(players[1])
{
    for (int q = -mapSize; q <= mapSize; q++)
    {
        int r1 = std::max(-mapSize, -q - mapSize);
        int r2 = std::min(mapSize, -q + mapSize);
        for (int r = r1; r <= r2; r++)
        {
            tiles.push_back(new Tile(
                window,
                Hex(q, r, -q - r),
                {hexOrientation, hexSize, hexOrigin}));
        }
    }

    fillBoard();
}

Grid::~Grid()
{
    for (auto tile : tiles)
    {
        delete tile;
    }
}

void Grid::fillBoard() // TODO: find a better way
{
    for (auto tile : tiles)
    {
        //player 1

        if (tile->getHexTile().q == -4 && tile->getHexTile().r == 4 ||
            tile->getHexTile().q == -3 && tile->getHexTile().r == 3 ||
            tile->getHexTile().q == -2 && tile->getHexTile().r == 3 ||
            tile->getHexTile().q == -1 && tile->getHexTile().r == 2 ||
            tile->getHexTile().q == 0 && tile->getHexTile().r == 2 ||
            tile->getHexTile().q == 1 && tile->getHexTile().r == 1 ||
            tile->getHexTile().q == 2 && tile->getHexTile().r == 1 ||
            tile->getHexTile().q == 3 && tile->getHexTile().r == 0 ||
            tile->getHexTile().q == 4 && tile->getHexTile().r == 0)
        {
            Pawn *pawn = new Pawn(window, "assets/wpawn.png", Pawn::Direction::WHITE);
            players[0]->addPiece(pawn);
            tile->setPiece(pawn);
        }
        if (tile->getHexTile().q == -3 && tile->getHexTile().r == 4 ||
            tile->getHexTile().q == 0 && tile->getHexTile().r == 3 ||
            tile->getHexTile().q == 3 && tile->getHexTile().r == 1)
        {
            Rook *rook = new Rook(window, "assets/wrook.png");
            players[0]->addPiece(rook);
            tile->setPiece(rook);
        }
        if (tile->getHexTile().q == -1 && tile->getHexTile().r == 3 ||
            tile->getHexTile().q == 1 && tile->getHexTile().r == 2)
        {
            Bishop *bishop = new Bishop(window, "assets/wbishop.png");
            players[0]->addPiece(bishop);
            tile->setPiece(bishop);
        }

        if (tile->getHexTile().q == 0 && tile->getHexTile().r == 4 ||
            tile->getHexTile().q == -2 && tile->getHexTile().r == 4 ||
            tile->getHexTile().q == 2 && tile->getHexTile().r == 2)
        {
            Knight *knight = new Knight(window, "assets/wunicorn.png");
            players[0]->addPiece(knight);
            tile->setPiece(knight);
        }
        if (tile->getHexTile().q == 1 && tile->getHexTile().r == 3)
        {
            King *king = new King(window, "assets/wking.png");
            players[0]->addPiece(king);
            tile->setPiece(king);
        }
        if (tile->getHexTile().q == -1 && tile->getHexTile().r == 4)
        {
            Queen *queen = new Queen(window, "assets/wqueen.png");
            players[0]->addPiece(queen);
            tile->setPiece(queen);
        }

        // player 2

        if (tile->getHexTile().q == -4 && tile->getHexTile().r == 0 ||
            tile->getHexTile().q == -3 && tile->getHexTile().r == 0 ||
            tile->getHexTile().q == -2 && tile->getHexTile().r == -1 ||
            tile->getHexTile().q == -1 && tile->getHexTile().r == -1 ||
            tile->getHexTile().q == -1 && tile->getHexTile().r == -1 ||
            tile->getHexTile().q == 0 && tile->getHexTile().r == -2 ||
            tile->getHexTile().q == 1 && tile->getHexTile().r == -2 ||
            tile->getHexTile().q == 2 && tile->getHexTile().r == -3 ||
            tile->getHexTile().q == 3 && tile->getHexTile().r == -3 ||
            tile->getHexTile().q == 4 && tile->getHexTile().r == -4)
        {
            Pawn *pawn = new Pawn(window, "assets/bpawn.png", Pawn::Direction::BLACK);
            players[1]->addPiece(pawn);
            tile->setPiece(pawn);
        }
        if (tile->getHexTile().q == -3 && tile->getHexTile().r == -1 ||
            tile->getHexTile().q == 0 && tile->getHexTile().r == -3 ||
            tile->getHexTile().q == 3 && tile->getHexTile().r == -4)
        {
            Rook *rook = new Rook(window, "assets/brook.png");
            players[1]->addPiece(rook);
            tile->setPiece(rook);
        }
        if (tile->getHexTile().q == -1 && tile->getHexTile().r == -2 ||
            tile->getHexTile().q == 1 && tile->getHexTile().r == -3)
        {
            Bishop *bishop = new Bishop(window, "assets/bbishop.png");
            players[1]->addPiece(bishop);
            tile->setPiece(bishop);
        }
        if (tile->getHexTile().q == 0 && tile->getHexTile().r == -4 ||
            tile->getHexTile().q == 2 && tile->getHexTile().r == -4 ||
            tile->getHexTile().q == -2 && tile->getHexTile().r == -2)
        {
            Knight *knight = new Knight(window, "assets/bunicorn.png");
            players[1]->addPiece(knight);
            tile->setPiece(knight);
        }
        if (tile->getHexTile().q == 1 && tile->getHexTile().r == -4)
        {
            King *king = new King(window, "assets/bking.png");
            players[1]->addPiece(king);
            tile->setPiece(king);
        }
        if (tile->getHexTile().q == -1 && tile->getHexTile().r == -3)
        {
            Queen *queen = new Queen(window, "assets/bqueen.png");
            players[1]->addPiece(queen);
            tile->setPiece(queen);
        }
    }
}

Tile *
Grid::getSelectedTile()
{
    return selectedTile;
}

void Grid::render(float xPos, float yPos)
{
    for (auto tile : tiles)
    {
        tile->render(xPos, yPos);
    }
}

bool Grid::selectTile(Point point)
{
    bool succes = false;
    Hex clickHex = hex_round(pixel_to_hex({hexOrientation, hexSize, hexOrigin}, point));

    for (auto tile : tiles)
    {
        if (tile->getHexTile() == clickHex)
        {
            succes = true;
            if (selectedTile)
            {
                for (auto tile : tiles)
                {
                    tile->setSelected(false);
                    tile->setColor({0, 255, 0, 255});
                }
            }

            selectedTile = tile;
            selectedTile->setSelected(true);
            if (selectedTile->getPiece() && currentPlayer->hasPiece(selectedTile->getPiece()))
            {
                Log::debug("current piece is " + selectedTile->getPiece()->getFilename());

                for (auto tile : selectedTile->getPiece()->canMove(selectedTile, tiles))
                {
                    if (!tile->getPiece())
                    {
                        tile->setSelected(true);
                        tile->setColor({0, 255, 0, 55});
                    }
                    else if (!currentPlayer->hasPiece(tile->getPiece()))
                    {
                        tile->setSelected(true);
                        tile->setColor({255, 0, 0, 55});
                    }
                }
            }
            else
            {
                Log::debug("current piece is nullptr");
            }

            tile->setColor({0, 0, 255, 55});
            break;
        }
    }
    if (!succes)
    {
        //selectedTile->setColor({0, 255, 0, 255});
        //selectedTile->setSelected(false);
        for (auto tile : tiles)
        {
            tile->setSelected(false);
            tile->setColor({0, 255, 0, 255});
        }
        selectedTile = nullptr;
    }
    return succes;
}

bool Grid::movePiece(Point point)
{
    bool succes = false;
    if (!selectedTile->getPiece() || !currentPlayer->hasPiece(selectedTile->getPiece()))
    {
        Log::debug("no piece to move");
        succes = false;
    }
    else
    {
        Hex clickHex = hex_round(pixel_to_hex({hexOrientation, hexSize, hexOrigin}, point));

        for (auto tile : selectedTile->getPiece()->canMove(selectedTile, tiles))
        {
            if (tile->getHexTile() == clickHex)
            {
                if (tile->getPiece())
                {
                    if (currentPlayer->hasPiece(tile->getPiece()))
                    {
                        break;
                    }
                    else
                    {
                        otherPlayer->removePiece(tile->getPiece());
                        delete tile->getPiece();
                    }
                }
                succes = true;
                if (selectedTile)
                {
                    for (auto tile : tiles)
                    {
                        tile->setSelected(false);
                        tile->setColor({0, 255, 0, 255});
                    }
                }
                tile->setPiece(selectedTile->getPiece());
                selectedTile->removePiece();
                selectedTile->setSelected(false);
                selectedTile = nullptr;
                break;
            }
        }
    }
    if (!succes)
    {
        for (auto tile : tiles)
        {
            tile->setSelected(false);
            tile->setColor({0, 255, 0, 255});
        }
        selectedTile = nullptr;
    }
    else
    {
        nextTurn();
    }
    return succes;
}

void Grid::nextTurn()
{
    if (Ai *ai = dynamic_cast<Ai *>(otherPlayer))
    {
        std::swap(currentPlayer, otherPlayer);
        selectedTile = ai->selectTile(tiles);
        selectedTile->setSelected(true);
        selectedTile->setColor({0, 255, 0, 55});
        Point point = ai->selectMove(tiles, {hexOrientation, hexSize, hexOrigin});
        movePiece(point);
    } 
    else if (currentPlayer == players[0])
    {
        currentPlayer = players[1];
        otherPlayer = players[0];
    }
    else
    {
        currentPlayer = players[0];
        otherPlayer = players[1];
    }
}

Player *
Grid::getCurrentPlayer()
{
    return currentPlayer;
}
