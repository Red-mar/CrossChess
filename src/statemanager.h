#ifndef StateManager_H
#define StateManager_H

#include "gamestate.h"
#include "window.h"
#include "emscripten.h"

#include "inputmanager.h"

class StateManager
{
    public:
        StateManager(Window* window);

        virtual ~StateManager();

        void run(void *arg = NULL);
        void MainLoop();
        void LoadState();
        Window* window;
    private:
        
        GameState* currentState;
        GameState::GameInfo sharedInfo;
};

#endif // !StateManager_H
