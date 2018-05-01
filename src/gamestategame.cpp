#include "gamestategame.h"
#include "log.h"

GameStateGame::GameStateGame(Window *window) : window(window),
                                               currentStateCode(GameState::CONTINUE)
{
}

GameStateGame::~GameStateGame()
{
}

void GameStateGame::load(GameInfo stack)
{
    players.push_back(new Player(stack.player1name));
    players.push_back(new Player(stack.player2name));
    grid = new Grid(window, Point(window->mWidth / 2, window->mHeight / 2), Point(35, 35), 4, players);
    currentTurn = players[0];

    Label *lblPlayer1 = new Label(window, 0, 0, 5, 5, stack.player1name);
    Label *lblPlayer2 = new Label(window, window->mWidth - 200, 0, 200, 100, stack.player2name);
    Label *lblCurrentPlayer = new Label(window, (window->mWidth / 2) - 200, 0, 5, 5, "Current Player: N/A");
    //Button *btnEndTurn = new Button(window, 0, window->mHeight - 100, 100, 100);
    uiElements["lblPlayer1"] = lblPlayer1;
    uiElements["lblPlayer2"] = lblPlayer2;
    uiElements["lblCurrentPlayer"] = lblCurrentPlayer;
    //uiElements["btnEndTurn"] = btnEndTurn;
}

GameState::GameInfo GameStateGame::unload()
{
    for (std::unordered_map<std::string, UIElement *>::iterator it = uiElements.begin(); it != uiElements.end(); it++)
    {
        delete it->second;
    }
    for (std::vector<Player *>::iterator it = players.begin(); it != players.end(); it++)
    {
        delete (*it);
    }
    delete grid;
    return {"", ""};
}

void GameStateGame::render()
{
    grid->render(0, 0);
    for (auto element : uiElements)
    {
        element.second->render(0, 0);
    }
}

GameState::StateCode
GameStateGame::update(float dt)
{
    updateInput();
    for (auto element : uiElements)
    {
        element.second->update(dt);
    }

    Label* label = (Label*)uiElements["lblCurrentPlayer"];
    label->setText("Current Player = " + grid->getCurrentPlayer()->getName());

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