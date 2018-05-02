#ifndef GAMESTATEGAME_H
#define GAMESTATEGAME_H

#include "gamestate.h"
#include "sprite.h"
#include "window.h"
#include "inputmanager.h"
#include <vector>
#include <unordered_map>
#include "UI\uielement.h"
#include "UI\button.h"
#include "UI\label.h"
#include "grid.h"

#include "player.h"
#include "ai/localplayer.h"

#include "ai/randomai.h"

class GameStateGame : public GameState
{
    public:
        GameStateGame(Window* window);
        ~GameStateGame();

        void load(GameInfo stack= {});
        GameInfo unload();

        GameState::StateCode update(float dt);

        void render();
    private:
        void updateInput();
        GameState::StateCode currentStateCode;
        Window* window;
        std::unordered_map<std::string, UIElement*> uiElements;

        Grid* grid;
        std::vector<Player*> players;
        Player* currentTurn;

        void nextTurn();
};

#endif // GAMESTATEGAME_H