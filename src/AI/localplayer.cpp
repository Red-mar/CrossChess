#include "localplayer.h"

LocalPlayer::LocalPlayer(std::string name) : Player(name)
{

}

LocalPlayer::~LocalPlayer()
{
    
}

void
LocalPlayer::update(float dt)
{
    currentTurnTime -= dt * 1;
}