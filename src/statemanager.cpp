#include <cstdlib>
#include <ctime>
#include "statemanager.h"
#include "GameStateGame.h"
#include "gamestatemenu.h"
#include "sdl.hpp"
#include "log.h"
#include "window.h"

StateManager::StateManager(Window *window) : window(window),
                                             currentState(nullptr),
                                             sharedInfo({}),
                                             now(SDL_GetPerformanceCounter()),
                                             last(0),
                                             deltaTime(0)
{
    this->currentState = new GameStateMenu(this->window);

#ifndef __EMSCRIPTEN__ // since emscripten has no renderer yet no sprite can be loaded
    this->currentState->load();
#endif // !__EMSCRIPTEN__

}

void StateManager::LoadState()
{
    this->currentState->load();
}

StateManager::~StateManager()
{
    if (this->currentState)
    {
        this->currentState->unload();
        delete this->currentState;

        this->currentState = nullptr;
    }
}


#ifndef __EMSCRIPTEN__

void StateManager::run()
{
    bool quit = false;
    int countedFrames = 0;
    while (!quit)
    {
        last = now;
        now = SDL_GetPerformanceCounter();
        deltaTime = ((now - last) * 1000 / (double)SDL_GetPerformanceFrequency());
        float avgFPS = countedFrames / (window->getTicks() / 1000.0f);
        if (avgFPS > 200000)
        {
            avgFPS = 0;
        }

        GameState::StateCode whatToDoNow;
        whatToDoNow = currentState->update((float)(deltaTime / 1000.0));

        switch (whatToDoNow)
        {
        case GameState::GAME_START:
            sharedInfo = currentState->unload();
            currentState = new GameStateGame(window);
            currentState->load(sharedInfo);
            break;
        case GameState::MAIN_MENU:
            sharedInfo = currentState->unload();
            currentState = new GameStateMenu(window);
            currentState->load(sharedInfo);
            break;
        case GameState::CONTINUE:
            break;
        case GameState::QUIT:
            quit = true;
            break;
        default:
            break;
        }

        if (window)
        {
            window->clear();
            currentState->render();
            window->refresh();
        }

        window->delayFramerateIfNeeded();
        countedFrames++;
    }
}

#endif // !__EMSCRIPTEN__

#ifdef __EMSCRIPTEN__

void StateManager::MainLoop()
{
    last = now;
    now = SDL_GetPerformanceCounter();
    deltaTime = ((now - last) * 1000 / (double)SDL_GetPerformanceFrequency());

    GameState::StateCode whatToDoNow;
    whatToDoNow = currentState->update((float)(deltaTime / 1000.0));

    switch (whatToDoNow)
    {
    case GameState::GAME_START:
        sharedInfo = currentState->unload();
        currentState = new GameStateGame(window);
        currentState->load(sharedInfo);
        break;
    case GameState::MAIN_MENU:
        sharedInfo = currentState->unload();
        currentState = new GameStateMenu(window);
        currentState->load(sharedInfo);
        break;
    case GameState::CONTINUE:
        break;
    case GameState::QUIT:
        emscripten_cancel_main_loop();
        break;
    default:
        break;
    }

    if (window)
    {
        window->clear();
        currentState->render();
        window->refresh();
    }

    window->delayFramerateIfNeeded();
}

#endif // __EMSCRIPTEN__