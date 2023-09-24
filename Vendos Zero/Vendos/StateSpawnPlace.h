#ifndef STATESPAWNPLACE_H
#define STATESPAWNPLACE_H

#include "State.h"
class StateSpawnPlace :
    public State
{
private:


public:
    StateSpawnPlace(sf::RenderWindow* window, std::stack<State*>* Stat);
    ~StateSpawnPlace();

    //Functions
    void updateKeybinds(const float& dt);
    void endState();

    void initGraphics();

    void update(const float& dt);
    void render(sf::RenderTarget* Window);

};

#endif 