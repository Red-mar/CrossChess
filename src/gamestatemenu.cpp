#include "gamestatemenu.h"
#include "log.h"

GameStateMenu::GameStateMenu(Window *window) : window(window),
                                               currentStateCode(GameState::CONTINUE),
                                               currentGameInfo({"", "", LOCAL})
{
}

GameStateMenu::~GameStateMenu()
{
}

void GameStateMenu::load(GameInfo stack)
{
    UNUSED(stack);
    Button *btnLocal = new Button(window, window->mWidth / 4 - 50, (window->mHeight / 4) * 3 - 20, 100, 40, "assets/button.png");
    Button *btnAi = new Button(window, (window->mWidth / 4) * 3 - 50, (window->mHeight / 4) * 3 - 20, 100, 40, "assets/buttonai.png");
    Label *lblTitle = new Label(window, window->mWidth / 2, (window->mHeight / 4) * 3, 5, 5, "Welcome to Cross Chess");
    lblTitle->setFontSize(68);
    lblTitle->setText("Welcome to Cross Chess");
    lblTitle->position = new Point((window->mWidth / 2) - (lblTitle->getWidth() / 2), (window->mHeight / 4) - lblTitle->getHeight());
    uiElements["btnLocal"] = btnLocal;
    uiElements["btnAi"] = btnAi;
    uiElements["lblTitle"] = lblTitle;
}

GameState::GameInfo GameStateMenu::unload()
{
    for (std::unordered_map<std::string, UIElement *>::iterator it = uiElements.begin(); it != uiElements.end(); it++)
    {
        delete it->second;
    }

    return currentGameInfo;
}

GameState::StateCode GameStateMenu::update(float dt)
{
    updateInput();
    for (auto element : uiElements)
    {
        element.second->update(dt);
    }

    return currentStateCode;
}

void GameStateMenu::render()
{
    for (auto element : uiElements)
    {
        element.second->render(0, 0);
    }
}

void GameStateMenu::updateInput()
{
    InputManager *inputManager = InputManager::getInstance();

    inputManager->update();
    if (inputManager->quitRequested() ||
        inputManager->isKeyDown(KEY_ESCAPE))
    {
        currentStateCode = GameState::QUIT;
    }
    if (inputManager->isKeyDown(KEY_1))
    {
        currentStateCode = GameState::GAME_START;
    }

    if (inputManager->isKeyDown(KEY_RETURN) && inputManager->alt())
    {
        if (window->mHeight == 1080)
        {
            window->resize(800, 600, 0);
        }
        else
        {
            window->resize(1920, 1080, SDL_WINDOW_FULLSCREEN_DESKTOP);
        }
        resetUI();
    }
    if (inputManager->isMouseUp(MOUSE_LEFT))
    {
        if (inputManager->isMouseInside(uiElements["btnAi"]->box))
        {
            currentGameInfo.gameType = GameType::AI;
            currentGameInfo.player1name = "You";
            currentGameInfo.player2name = "Computer";
            currentStateCode = GameState::GAME_START;
        }
        if (inputManager->isMouseInside(uiElements["btnLocal"]->box))
        {
            currentGameInfo.gameType = GameType::LOCAL;
            currentGameInfo.player1name = "Player 1";
            currentGameInfo.player2name = "Player 2";
            currentStateCode = GameState::GAME_START;
        }
    }
}

void GameStateMenu::resetUI() // TODO: reset method in uielement
{
    uiElements["lblTitle"]->box->setX((window->mWidth / 2) - (uiElements["lblTitle"]->getWidth() / 2));
    uiElements["lblTitle"]->box->setY((window->mHeight / 4) - uiElements["lblTitle"]->getHeight());

    uiElements["btnAi"]->box->setX((window->mWidth / 4) * 3 - 50);
    uiElements["btnAi"]->box->setY((window->mHeight / 4) - uiElements["lblTitle"]->getHeight());

    uiElements["btnLocal"]->box->setX((window->mWidth / 2) - (window->mWidth / 4) - 50);
    uiElements["btnLocal"]->box->setY((window->mHeight / 4) * 3 - 20);

    uiElements["lblTitle"]->position = new Point((window->mWidth / 2) - (uiElements["lblTitle"]->getWidth() / 2), (window->mHeight / 4) - uiElements["lblTitle"]->getHeight());
    uiElements["btnAi"]->position = new Point((window->mWidth / 4) * 3 - 50, (window->mHeight / 4) * 3 - 20);
    uiElements["btnLocal"]->position = new Point((window->mWidth / 2) - (window->mWidth / 4) - 50, (window->mHeight / 4) * 3 - 20);
}