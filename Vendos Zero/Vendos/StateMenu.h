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
    StateMenu(sf::RenderWindow* window, std::stack<State*>* Stat, std::map<std::string, sf::Texture*>* TexturesMap, std::vector<sf::Texture*>* GraphicsTxtVec);
    ~StateMenu();

    //Functions
    void updateKeybinds(const float& dt);
    void endState();

    void initGraphics();
    void update(const float& dt);
    void render(sf::RenderTarget* Window);
};

#endif // !STATEMENU_H