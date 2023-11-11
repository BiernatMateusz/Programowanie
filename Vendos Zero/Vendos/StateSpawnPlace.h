#ifndef STATESPAWNPLACE_H
#define STATESPAWNPLACE_H

//Aby dodawac nowe grafiki nale�y wej�� do Game.cpp do funkcji initTextures i dopisa� dolejne textury

#include "State.h"
class StateSpawnPlace :
    public State
{
private:
    

public:
    StateSpawnPlace(GraphicsData* graphicsData, std::stack<State*>* Stat);
    ~StateSpawnPlace();

    //Functions
    void updateKeybinds(const float& dt);
    void endState();

    void initGraphics();
    void initPlayer();
    void initBlockade();
    void initEquipment(GraphicsData* graphicsData);

    void update(const float& dt);
    void render(sf::RenderTarget* Window);

};

#endif 