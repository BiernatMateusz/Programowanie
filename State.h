#ifndef STATE_H
#define STATE_H

//Aby dodawac nowe grafiki nale¿y wejœæ do Game.cpp do funkcji initTextures i dopisaæ dolejne textury

#include <stack>
#include "EntityPlayer.h"
#include "Camera.h"
#include "Equipment.h"
#include "StructuresOfData.h"
#include "itemChest.h"
#include "ThrownItems.h"

class State
{

public:
	//Constructors
	State(GraphicsData* graphicsData, std::stack<State*>* Stat);

	//Destructor
	virtual ~State();

	//Update and render functions
	virtual void update(const float& dt, const std::map<std::string, button*> &AllKeys) = 0;
	virtual void render() = 0;

	void updateTilesSprite();
	void updateBlockades();

	virtual void updateKeybinds(const float& dt, const std::map<std::string, button*>& AllKeys) = 0;

	//Ending state
	const bool& getQuit() const;
	virtual void checkForQuit(const std::map<std::string, button*>& AllKeys);
	virtual void endState() = 0;

	//Init functions
	void initTile(sf::Vector2i&& position2i, std::string&& NameOfTxt);
	void initChest(sf::Vector2i position2i);
	void initTileAndBlockade();
	virtual void initGraphics() = 0;

	//Functions
	virtual void getMousePosition();
	virtual bool checkExactPosition(int x, int offsetX, int y, int offsetY);

	//Graphics function
	void LoadBackground(sf::Vector2f&& position, std::string&& NameOfTxt);



private:
	
	bool quit;
	
protected:

	//Graphics data
	GraphicsData* graphicsData;

	//States
	std::stack<State*> *stat;

	//Blockade
	std::vector<std::vector<bool>>Blockade;
	std::vector<std::vector<sf::Vector2f>>BlockadeDimension;

	//Tiles
	std::vector<std::vector<TilesOnMap*>>Tile;

	//Items thrown
	std::vector<ThrownItems*>ItemsThrown;

	ThrownItems* ItemsOnTheGround;

	//Equipment
	EquipmentData* equipmentData;

	//Camera
	Camera* Camer;

	//Entities
	std::vector<Entity*>* entiesPointer;
	std::vector<sf::Sprite*> *SpritesEntiPointer;
};


#endif 