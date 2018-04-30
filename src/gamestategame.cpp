#include "gamestategame.h"
#include "log.h"

GameStateGame::GameStateGame(Window *window) : window(window),
                                               currentStateCode(GameState::CONTINUE)
{
}

GameStateGame::~GameStateGame()
{
}

void GameStateGame::load(int stack)
{
    grid = new Grid(window, Point(window->mWidth / 2, window->mHeight / 2), Point(35, 35), 4);
}

int GameStateGame::unload()
{
    for (std::vector<UIElement *>::iterator it = uiElements.begin(); it != uiElements.end(); it++)
    {
        delete (*it);
    }
    delete grid;
    return 0;
}

void GameStateGame::render()
{
    grid->render(0, 0);
}

GameState::StateCode
GameStateGame::update(float dt)
{
    updateInput();
    for (auto element : uiElements)
    {
        element->update(dt);
    }

    return currentStateCode;
}

void GameStateGame::updateInput()
{
    InputManager *inputManager = InputManager::getInstance();

    inputManager->update();
    if (inputManager->quitRequested())
    {
        currentStateCode = GameState::QUIT;
    }
    if (inputManager->isKeyDown(KEY_1))
    {
        currentStateCode = GameState::MAIN_MENU;
    }

    if (inputManager->isMouseDown(MOUSE_LEFT))
    {
        if (grid->getSelectedTile() && grid->getSelectedTile()->getPiece())
        {
            if (grid->movePiece(Point(inputManager->getMouseX(), inputManager->getMouseY())))
                Log::debug("moved piece!");
        }
        else if (grid->selectTile(Point(inputManager->getMouseX(), inputManager->getMouseY())))
            Log::debug("selected tile!");
    }

    if (inputManager->isKeyDown(KEY_RETURN))
    {
        if (window->mHeight == 1080)
        {
            window->resize(800, 600, 0);
        }
        else
        {
            window->resize(1920, 1080, SDL_WINDOW_FULLSCREEN_DESKTOP);
        }
    }
}