#include "StateSpawnPlace.h"

StateSpawnPlace::StateSpawnPlace(GraphicsData* graphicsData, std::stack<State*>* Stat)
	: State(graphicsData, Stat)
{
	this->equipmentData = new EquipmentData;
	this->ItemsOnTheGround = new ThrownItems(graphicsData, equipmentData);
	initPlayer();
	initGraphics();
}

StateSpawnPlace::~StateSpawnPlace()
{

}

void StateSpawnPlace::updateKeybinds(const float& dt, const std::map<std::string, button*>& AllKeys)
{
	this->checkForQuit(AllKeys);
	this->playerMovement(dt, AllKeys);

}

void StateSpawnPlace::endState()
{
	std::cout << "Ending SpawnPlaceState\n";
}

void StateSpawnPlace::initGraphics()
{
	LoadBackground({ 0,2596}, "Mapka");

	initTile({ 10, 12 }, "Tree1");
	initTile({ 13, 12 }, "Tree2");
	initTile({ 15, 12 }, "Tree3");
	initTile({ 17, 12 }, "Skrzynia");
	initTile({ 19,12 }, "Stone");

	updateBlockades();
	updateTilesSprite();
	this->Camer = new Camera(this->graphicsData);
	
}

void StateSpawnPlace::initPlayer()
{
	this->entiesPointer->push_back(new EntityPlayer({ 44 * 4,44 * 20 }, "Abigail", this->graphicsData, &Tile, this->equipmentData, &ItemsThrown, ItemsOnTheGround));
}

void StateSpawnPlace::playerMovement(const float& dt, const std::map<std::string, button*>& AllKeys)
{
	//Reseting value to "nothing"
	movementData.direction = "";

	if (this->equipmentData->isEqOpened == 0)
		this->entiesPointer->at(0)->movement(dt, this->Blockade, this->BlockadeDimension, 100, movementData, AllKeys);

	entiesPointer->at(0)->Animation(dt, std::move(movementData.direction));

	if (movementData.moved)
		this->Camer->sortVector();
}

void StateSpawnPlace::update(const float& dt, const std::map<std::string, button*>& AllKeys)
{
	this->getMousePosition();
	for (auto* elem: *this->entiesPointer)
		elem->update(dt, AllKeys);

	if (this->equipmentData->needToUpdateTilesSpriteVec)
		updateTilesSprite();
	if (this->equipmentData->needToUpdateCameraAllSpr)
		Camer->updateAllSpritesVec(graphicsData, equipmentData);

	this->updateKeybinds(dt, AllKeys);

}

void StateSpawnPlace::render()
{
	Camer->render(this->graphicsData->window);

	for (auto* elem : *this->entiesPointer)
		elem->render();

}
