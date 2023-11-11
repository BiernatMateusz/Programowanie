#ifndef STATE_H
#define STATE_H

//Aby dodawac nowe grafiki nale¿y wejœæ do Game.cpp do funkcji initTextures i dopisaæ dolejne textury

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include "EntityPlayer.h"
#include "Camera.h"
#include "Equipment.h"
#include "StructuresOfData.h"


class State
{
private:
	
	bool quit;
	
protected:

	GraphicsData* graphicsData;

	std::stack<State*> *stat;

	std::vector<Entity*> entities;
	std::vector<Entity*> *entiesPointer;
	
	std::vector<std::vector<bool>>Blockade;
	std::vector<std::vector<sf::Vector2f>>BlockadeDimension;

	Entity* NewEntity;
	Camera* Camer;

	std::vector<sf::Sprite*> GraphicsSprite;

	std::vector<sf::Sprite*> SpritesEnti;
	std::vector<sf::Sprite*> *SpritesEntiPointer;

	

	Equipment* equipmentPtr;
	
public:
	State(GraphicsData* graphicsData, std::stack<State*>* Stat);

	virtual ~State();

	const bool& getQuit() const;

	//Function
	virtual void updateKeybinds(const float& dt) = 0;
	virtual void getMousePosition();
	virtual bool checkExactPosition(int x, int offsetX, int y, int offsetY);

	virtual void initGraphics()=0;
	virtual void initEquipment(GraphicsData *graphicsData) = 0;
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* Window = nullptr)=0; 
	virtual void checkForQuit();
	virtual void endState()=0;

	void LoadNewGraph(sf::Vector2f&& position, std::string&& NameOfTxt);
};

#endif 