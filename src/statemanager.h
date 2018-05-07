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

#ifdef __EMSCRIPTEN__
        void MainLoop();
#endif // __EMSCRIPTEN__

#ifndef __EMSCRIPTEN__
        void run();
#endif // !__EMSCRIPTEN__


        void LoadState();
        Window* window;
    private:
        
        GameState* currentState;
        GameState::GameInfo sharedInfo;
        Uint64 now;
        Uint64 last;
        double deltaTime;
};

#endif // !StateManager_H
