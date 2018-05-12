#ifndef LOCALPLAYER_H
#define LOCALPLAYER_H

#include "player.h"

class LocalPlayer : public Player 
{
    public:
        LocalPlayer(std::string name);
        ~LocalPlayer();
        void update(float dt);

    private:
};

#endif // !LOCALPLAYER_H
