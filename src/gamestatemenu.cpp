#include "gamestatemenu.h"
#include "log.h"

GameStateMenu::GameStateMenu(Window *window) : window(window),
                                               currentStateCode(GameState::CONTINUE)
{
}

GameStateMenu::~GameStateMenu()
{
}

void GameStateMenu::load(GameInfo stack)
{
    UNUSED(stack);
    Button* btnTest = new Button(window, 250, 350, 50, 20);
    Label* lblTest = new Label(window, 200, 200, 5, 5, "WELCOME to the main menu");
    uiElements["btnTest"] = btnTest;
    uiElements["lblTest"] = lblTest;
}

GameState::GameInfo GameStateMenu::unload()
{
    for(std::unordered_map<std::string, UIElement*>::iterator it = uiElements.begin(); it != uiElements.end(); it++ )
    {
        delete it->second;
    }

    return {"player1", "player2"};
}

GameState::StateCode GameStateMenu::update(float dt)
{
    updateInput();
    for(auto element : uiElements)
    {
        element.second->update(dt);
    }

    return currentStateCode;
}

void GameStateMenu::render()
{
    for(auto element : uiElements)
    {
        element.second->render(0, 0);   
    }
}

void GameStateMenu::updateInput()
{
    InputManager *inputManager = InputManager::getInstance();

    inputManager->update();
    if (inputManager->quitRequested())
    {
        currentStateCode = GameState::QUIT;
    }
    if (inputManager->isKeyDown(KEY_0))
    {
        Label* label = (Label*)uiElements["lblTest"];
        label->setFontSize(72);
        label->setText("test");
    }
    if (inputManager->isKeyDown(KEY_1))
    {
        currentStateCode = GameState::GAME_START;
    }

    if (inputManager->isKeyDown(KEY_5))
    {
        if (window->getFramerateLimit() == 0)
        {
            window->setFramerateLimit(60);
        } else {
            window->setFramerateLimit(0);
        }
    }
    if (inputManager->isMouseUp(MOUSE_LEFT) && inputManager->isMouseInside(uiElements["btnTest"]->box))
    {
        Log::debug("Clicked the button!");
        currentStateCode = GameState::GAME_START;
    }
}