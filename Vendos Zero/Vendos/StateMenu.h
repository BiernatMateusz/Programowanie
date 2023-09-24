#ifndef STATEMENU_H
#define STATEMENU_H

#include "State.h"
#include "StateSpawnPlace.h"

class StateMenu :
    public State
{
private:

    

public:
    StateMenu(sf::RenderWindow* window, std::stack<State*>* Stat);
    ~StateMenu();

    //Functions
    void updateKeybinds(const float& dt);
    void endState();

    void initGraphics();
    void update(const float& dt);
    void render(sf::RenderTarget* Window);
};

#endif // !STATEMENU_H