#ifndef STATEMENU_H
#define STATEMENU_H

//Aby dodawac nowe grafiki nale¿y wejœæ do Game.cpp do funkcji initTextures i dopisaæ dolejne textury

#include "State.h"
#include "StateSpawnPlace.h"

class StateMenu :
    public State
{
private:

    

public:
    StateMenu(GraphicsData* graphicsData, std::stack<State*>* Stat);
    ~StateMenu();

    //Functions
    void updateKeybinds(const float& dt);
    void endState();

    void initEquipment(GraphicsData* graphicsData);
    void initGraphics();
    void update(const float& dt);
    void render(sf::RenderTarget* Window);
};

#endif // !STATEMENU_H