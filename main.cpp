#include "Sdl.hpp"
#include "Statemanager.h"
#include "Window.h"
#include "Log.h"

//#ifdef __EMSCRIPTEN__

#include "emscripten.h"
#include <chrono>
#include <thread>
void usleep(signed long long usec)
{
    std::this_thread::sleep_for(std::chrono::microseconds(usec));
}

void main_loop(void * arg)
{
    
    StateManager* manager = (StateManager*)arg;
    if (!manager->window->renderer)
    {
        Log::log("made renderer i guess");
        manager->window->createRenderer();
        manager->LoadState();
    }
    manager->MainLoop();
}

//#endif // EMSCRIPTEN

int main(int argc, char *args[])
{

    SDL::init();
    
    int width = 800;
    int height = 600;

    Window window(width, height, "Cross Chess");
    
    StateManager manager(&window);
    emscripten_set_main_loop_arg(main_loop, &manager, 0, 1);
#ifdef __EMSCRIPTEN__
    //StateManager manager(&window);
    //emscripten_set_main_loop_arg(main_loop, &manager, -1, 1);
#endif // __EMSCRIPTEN

#ifndef __EMSCRIPTEN__
    // StateManager manager(&window);
    //manager.run();
#endif // !__EMSCRIPTEN

    return 0;
}