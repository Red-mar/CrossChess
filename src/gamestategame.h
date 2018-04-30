#ifndef GAMESTATEGAME_H
#define GAMESTATEGAME_H

#include "gamestate.h"
#include "sprite.h"
#include "window.h"
#include "inputmanager.h"
#include <vector>
#include "UI\uielement.h"
#include "UI\button.h"
#include "UI\label.h"
#include "grid.h"

class GameStateGame : public GameState
{
    public:
        GameStateGame(Window* window);
        ~GameStateGame();

        void load(int stack=0);
        int unload();

        GameState::StateCode update(float dt);

        void render();
    private:
        void updateInput();
        GameState::StateCode currentStateCode;
        Window* window;
        std::vector<UIElement*> uiElements;

        Grid* grid;
};

#endif // GAMESTATEGAME_H