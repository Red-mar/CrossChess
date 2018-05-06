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
                                             sharedInfo({})
{
    this->currentState = new GameStateMenu(this->window);

    //this->currentState->load();
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

        this->currentState = nullptr; // you never know
    }
}

void StateManager::run(void *arg)
{
    bool quit = false;
    int countedFrames = 0;
    Uint64 NOW = SDL_GetPerformanceCounter();
    Uint64 LAST = 0;
    double deltaTime = 0;
    while (!quit)
    {
        LAST = NOW;
        NOW = SDL_GetPerformanceCounter();
        deltaTime = ((NOW - LAST) * 1000 / (double)SDL_GetPerformanceFrequency());
        float avgFPS = countedFrames / (window->getTicks() / 1000.0f);
        if (avgFPS > 200000)
        {
            avgFPS = 0;
        }
        //Log::debug(std::to_string(avgFPS));

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

void StateManager::MainLoop()
{
    int countedFrames = 0;
    Uint64 NOW = SDL_GetPerformanceCounter();
    Uint64 LAST = 0;
    double deltaTime = 0;
    LAST = NOW;
    NOW = SDL_GetPerformanceCounter();
    deltaTime = ((NOW - LAST) * 1000 / (double)SDL_GetPerformanceFrequency());
    float avgFPS = countedFrames / (window->getTicks() / 1000.0f);
    if (avgFPS > 200000)
    {
        avgFPS = 0;
    }
    //Log::debug(std::to_string(avgFPS));

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
        #ifdef __EMSCRIPTEN__
            emscripten_cancel_main_loop();
        #endif // __EMSCRIPTEN__
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