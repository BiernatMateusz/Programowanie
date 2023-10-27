#ifndef STATESPAWNPLACE_H
#define STATESPAWNPLACE_H

//Aby dodawac nowe grafiki nale¿y wejœæ do Game.cpp do funkcji initTextures i dopisaæ dolejne textury

#include "State.h"
class StateSpawnPlace :
    public State
{
private:
    

public:
    StateSpawnPlace(sf::RenderWindow* window, std::stack<State*>* Stat, std::map<std::string, sf::Texture*>* TexturesMap, std::vector<sf::Texture*>* GraphicsTxtVec);
    ~StateSpawnPlace();

    //Functions
    void updateKeybinds(const float& dt);
    void endState();

    void initGraphics();
    void initPlayer();
    void initBlockade();

    void update(const float& dt);
    void render(sf::RenderTarget* Window);

};

#endif 