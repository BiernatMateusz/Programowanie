#ifndef STATE_H
#define STATE_H

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include "EntityPlayer.h"
#include "Camera.h"

class State
{
private:
	
	bool quit;
	
	
protected:
	sf::Vector2i mousePosition;

	sf::RenderWindow* window;

	std::stack<State*> *stat;

	std::vector<Entity*> entities;
	std::vector<Entity*> *entiesPointer;
	
	Entity* NewEntity;
	Camera* Camer;

	std::vector<sf::Sprite*> GraphicsSprite;

	std::vector<sf::Sprite*> SpritesEnti;
	std::vector<sf::Sprite*> *SpritesEntiPointer;

	sf::Texture GraphicsTxt;
	std::vector<sf::Texture*>GraphicsTxtVec;
public:
	State(sf::RenderWindow* Window, std::stack<State*> *Stat);

	virtual ~State();

	const bool& getQuit() const;

	//Function
	virtual void updateKeybinds(const float& dt) = 0;
	virtual void getMousePosition();
	virtual bool checkExactPosition(int x, int offsetX, int y, int offsetY);

	virtual void initGraphics()=0;
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* Window = nullptr)=0; 
	virtual void checkForQuit();
	virtual void endState()=0;
};

#endif 