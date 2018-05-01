#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "window.h"

class GameState
{
    public:
        struct GameInfo
        {
            std::string player1name;
            std::string player2name;
        };

        enum StateCode
        {
            QUIT, CONTINUE, MAIN_MENU, GAME_START, GAME_INSTRUCTION, GAME_OVER
        };

        virtual void load(GameInfo stack= {}) = 0;
        virtual GameInfo unload() = 0;

        virtual StateCode update(float dt) = 0;

        virtual void render() = 0;
    private:
};

#endif // !GAMESTATE_H
