#include "Window.h"
#include "Log.h"

Window::Window(uint32_t width, uint32_t height, std::string title) : window(nullptr),
                                                                     //surface(nullptr),
                                                                     renderer(nullptr),
                                                                     mWidth(width),
                                                                     mHeight(height),
                                                                     originalWidth(width),
                                                                     originalHeight(height),
                                                                     isFullscreen(false),
                                                                     mTitle(title),
                                                                     bg_color({0, 0, 0, 0}),
                                                                     framerate(60),
                                                                     frame_delay(0),
                                                                     current_frame_delta(0)
{
    create(title, width, height);

    if (!window)
    {
        Log::error("Window: could not create window");
        throw "Window failed";
    }

    frame_delay = 1000 / framerate;
    framerateTimer.start();
    deltaTimer.start();

#ifndef __EMSCRIPTEN__
    //setIcon("assets/icon.bmp");
#endif // !__EMSCRIPTEN__

    clear();
    refresh();
    SDL_Delay(500);
}

Window::~Window()
{
    destroy();
}

void Window::create(std::string title, int width, int height, int windowFlags, int rendererFlags)
{
    destroy();
    window = SDL_CreateWindow("", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, windowFlags);
    if (window == NULL)
    {
        Log::error("Window: Could not create window");
    }
    rendererFlags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;

#ifndef __EMSCRIPTEN__ // Renderer is a bit finicky with emscripten, creating it in the emscripten_set_main_loop seems to work
    this->renderer = SDL_CreateRenderer(window, -1, rendererFlags);
    if (renderer == NULL)
    {
        Log::error("Could not create renderer");
    }
#endif // !__EMSCRIPTEN__

    setTitle(title);

    mWidth = width;
    mHeight = height;
    SDL_GetWindowSize(window, &mWidth, &mHeight);
}

void Window::createRenderer()
{
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

void Window::destroy()
{
    if (renderer)
    {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
    if (window)
    {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
}

void Window::renderImage(SDL_Texture *texture, SDL_Rect *clip, SDL_Rect *renderQuad, double angle, SDL_Point *center, SDL_RendererFlip flip)
{
    if (!texture)
    {
        Log::warning("Window::render: tried to render nullptr");
        return;
    }

    SDL_RenderCopyEx(renderer, texture, clip, renderQuad, angle, center, flip);
}

void Window::refresh()
{
    SDL_RenderPresent(renderer);
}

SDL_Texture *Window::loadImage(std::string filename)
{
    SDL_Texture *newTexture = IMG_LoadTexture(renderer, filename.c_str());

    if (newTexture == NULL)
    {
        printf(SDL_GetError());
        std::string error = SDL_GetError();
        Log::error(error);
    }
    return newTexture;
}

void Window::freeImage(SDL_Texture *image)
{
    if (image)
    {
        SDL_DestroyTexture(image);
    }
}

void Window::minimize()
{
    SDL_MinimizeWindow(window);
}

void Window::maximize()
{
    SDL_MaximizeWindow(window);
    SDL_GetWindowSize(window, &mWidth, &mHeight);
}

void Window::restore()
{
    SDL_RestoreWindow(window);
}

void Window::fill(SDL_Color color)
{
    SDL_SetRenderDrawColor(renderer,
                           color.r,
                           color.g,
                           color.b,
                           color.a);
    SDL_RenderClear(renderer);
}

void Window::clear()
{
    fill(bg_color);
}

void Window::setBackgroundColor(SDL_Color color)
{
    bg_color = color;
}

void Window::delayFramerateIfNeeded()
{
    unsigned int frameTicks = deltaTimer.getTicks();

    if (frameTicks < frame_delay)
    {
        SDL_Delay(frame_delay - frameTicks);
    }

    deltaTimer.start();
}

float Window::getDelta()
{
    return deltaTimer.getTicks() / 1000.000f;
}

unsigned int Window::getTicks()
{
    return framerateTimer.getTicks();
}

void Window::setTitle(std::string title)
{
    if (window)
    {
        SDL_SetWindowTitle(window, title.c_str());
    }
}

void Window::setFramerateLimit(int limit)
{
    framerate = limit;
    if (limit <= 0)
    {
        frame_delay = 0;
    }
    else
    {
        frame_delay = 1000 / framerate;
    }
}

int Window::getFramerateLimit()
{
    return framerate;
}

void Window::setIcon(std::string filepath)
{
    SDL_Surface *icon = IMG_Load(filepath.c_str());
    if (icon == NULL)
    {
        Log::error("could not load icon, error: ");
    }
    SDL_SetWindowIcon(window, icon);
    SDL_FreeSurface(icon);
}

void Window::resize(int width, int height, int windowFlags)
{
    SDL_SetWindowSize(window, width, height);
    SDL_SetWindowFullscreen(window, windowFlags);
    mWidth = width;
    mHeight = height;
}

void Window::drawBox(RotatedRectangle *r, SDL_Color color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    SDL_RenderDrawLine(renderer,
                       (int)r->A.x, (int)r->A.y,
                       (int)r->B.x, (int)r->B.y);

    SDL_RenderDrawLine(renderer,
                       (int)r->B.x, (int)r->B.y,
                       (int)r->C.x, (int)r->C.y);

    SDL_RenderDrawLine(renderer,
                       (int)r->C.x, (int)r->C.y,
                       (int)r->D.x, (int)r->D.y);

    SDL_RenderDrawLine(renderer,
                       (int)r->D.x, (int)r->D.y,
                       (int)r->A.x, (int)r->A.y);
}

void Window::drawHexagon(Hexagon *hexagon, SDL_Color color)
{
// NOTE: float to Sint16 might be bad?

// NOTE: takes a lot of cpu power not realy worth it maybe as an option
//aapolygonRGBA(renderer, vx, vy, 6, color.r, color.g, color.b, color.a);

#ifndef __EMSCRIPTEN__
    Sint16 vx[6];
    Sint16 vy[6];
    for (int i = 0; i < 6; i++)
    {
        vx[i] = (Sint16)hexagon->points[i].x;
        vy[i] = (Sint16)hexagon->points[i].y;
    }

    polygonRGBA(renderer, vx, vy, 6, color.r, color.g, color.b, color.a);
#endif // !__EMSCRIPTEN__

#ifdef __EMSCRIPTEN__
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    const SDL_Point points[7] = {
        (int)hexagon->points[0].x, (int)hexagon->points[0].y,
        (int)hexagon->points[1].x, (int)hexagon->points[1].y,
        (int)hexagon->points[2].x, (int)hexagon->points[2].y,
        (int)hexagon->points[3].x, (int)hexagon->points[3].y,
        (int)hexagon->points[4].x, (int)hexagon->points[4].y,
        (int)hexagon->points[5].x, (int)hexagon->points[5].y,
        (int)hexagon->points[0].x, (int)hexagon->points[0].y};

    SDL_RenderDrawLines(renderer, points, 7);

#endif // __EMSCRIPTEN__
}

void Window::drawFilledHexagon(Hexagon *hexagon, SDL_Color color)
{
#ifndef __EMSCRIPTEN__
    Sint16 vx[6];
    Sint16 vy[6];
    for (int i = 0; i < 6; i++)
    {
        vx[i] = (Sint16)hexagon->points[i].x;
        vy[i] = (Sint16)hexagon->points[i].y;
    }
    filledPolygonRGBA(renderer, vx, vy, 6, color.r, color.g, color.b, color.a);
#endif // !__EMSCRIPTEN__

#ifdef __EMSCRIPTEN__
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    const SDL_Point points[7] = {
        (int)hexagon->points[0].x, (int)hexagon->points[0].y,
        (int)hexagon->points[1].x, (int)hexagon->points[1].y,
        (int)hexagon->points[2].x, (int)hexagon->points[2].y,
        (int)hexagon->points[3].x, (int)hexagon->points[3].y,
        (int)hexagon->points[4].x, (int)hexagon->points[4].y,
        (int)hexagon->points[5].x, (int)hexagon->points[5].y,
        (int)hexagon->points[0].x, (int)hexagon->points[0].y};

    SDL_RenderDrawLines(renderer, points, 7);
#endif // __EMSCRIPTEN__
}