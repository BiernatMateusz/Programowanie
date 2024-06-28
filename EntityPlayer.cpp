#include "EntityPlayer.h"

EntityPlayer::EntityPlayer(sf::Vector2f position, std::string NameOfTxt, GraphicsData *graphicsData, std::vector<std::vector<TilesOnMap*>>* Tile, EquipmentData *equipmentData, std::vector<ThrownItems*>* ItemsThrown, ThrownItems* ItemsOnTheGround)
	: Entity(position, NameOfTxt, graphicsData)
{	
	changeTexture();
	initEquipment(graphicsData, Tile, equipmentData, ItemsThrown, ItemsOnTheGround);

}

EntityPlayer::~EntityPlayer()
{

}

void EntityPlayer::changeTexture()
{
	this->graphicsData->player->setTextureRect(sf::IntRect(21, 20, this->PlayerSpriteSize.x , this->PlayerSpriteSize.y));
	
	getCenterOfPlayer();

	this->graphicsData->player->setPosition(this->centerOfGame);
}

void EntityPlayer::update(const float& dt, const std::map<std::string, button*>& AllKeys)
{
	this->equipmentPtr->update(dt, AllKeys);
}

void EntityPlayer::render()
{
	this->equipmentPtr->render();
}

void EntityPlayer::Animation(const float& dt, std::string&& direction)
{
	if (direction != "left" and direction != "right" and direction != "top" and direction != "bot")
	{
		time = 0;
	}
	else time += dt;

	int timeUsed = time * 100;

	float WhichAnimation = timeUsed % 30;
	WhichAnimation = (timeUsed - WhichAnimation) / 30;

	if (WhichAnimation > 3)
	{
		time = 0;
		WhichAnimation = 0;
	}

	int WhichAnimationN = WhichAnimation + 1;
	if (WhichAnimationN == 4)
		WhichAnimationN = 0;

	if (direction == "left")
	{
		this->graphicsData->player->setTextureRect(sf::IntRect(22 + this->PlayerSpriteSize.x * WhichAnimationN, 20 + 234, this->PlayerSpriteSize.x, this->PlayerSpriteSize.y));
		lastDir = 3;
	}
	if (direction == "right")
	{
		this->graphicsData->player->setTextureRect(sf::IntRect(22 + this->PlayerSpriteSize.x * WhichAnimationN, 20 + 78, this->PlayerSpriteSize.x, this->PlayerSpriteSize.y));
		lastDir = 1;
	}
	if (direction == "top")
	{
		this->graphicsData->player->setTextureRect(sf::IntRect(22 + this->PlayerSpriteSize.x * WhichAnimationN, 20 + 156, this->PlayerSpriteSize.x, this->PlayerSpriteSize.y));
		lastDir = 2;
	}
	if (direction == "bot")
	{
		this->graphicsData->player->setTextureRect(sf::IntRect(22 + this->PlayerSpriteSize.x * WhichAnimationN, 20 + 0, this->PlayerSpriteSize.x, this->PlayerSpriteSize.y));
		lastDir = 0;
	}

	if (direction != "left" and direction != "right" and direction != "top" and direction != "bot")
	{
		this->graphicsData->player->setTextureRect(sf::IntRect(22 + this->PlayerSpriteSize.x * WhichAnimation, 20 + 78 * lastDir, this->PlayerSpriteSize.x, this->PlayerSpriteSize.y));
	}
}

void EntityPlayer::movement(const float& dt, std::vector<std::vector<bool>>& Blockade, std::vector<std::vector<sf::Vector2f>>& BlockadeDimension, float&& speed, MovementData& movData, 
	const std::map<std::string, button*>& AllKeys)
{
	if (AllKeys.at("W")->isButtonPressed())
	{
		if (CheckingPossibleMove(this->graphicsData->player, "top", { 30,-15 }, Blockade, BlockadeDimension, dt, speed))
		{
			if (checkIfBackGroundMoveable("top") and this->graphicsData->player->getPosition().y < this->graphicsData->CenterOfMap->y)
			{
				moveEntitesWithoutExcluded(this->graphicsData->player, dt, 0, speed);
			}
			else moveEntity(this->graphicsData->player, dt, 0, -speed);

			movData.moved = 1;


		}
		movData.direction = "top";
		this->graphicsData->directionOfPlayer = movData.direction;
	}
	if (AllKeys.at("S")->isButtonPressed())
	{
		if (CheckingPossibleMove(this->graphicsData->player, "bot", { 30,-15 }, Blockade, BlockadeDimension, dt, speed))
		{
			if (checkIfBackGroundMoveable("bot") and this->graphicsData->player->getPosition().y > this->graphicsData->CenterOfMap->y)
			{
				moveEntitesWithoutExcluded(this->graphicsData->player, dt, 0, -speed);
			}
			else moveEntity(this->graphicsData->player, dt, 0, speed);

			movData.moved = 1;
		}
		movData.direction = "bot";
		this->graphicsData->directionOfPlayer = movData.direction;
	}
	if (AllKeys.at("A")->isButtonPressed())
	{
		if (CheckingPossibleMove(this->graphicsData->player, "left", {30,-15}, Blockade, BlockadeDimension, dt, speed))
		{
			if (checkIfBackGroundMoveable("left") and this->graphicsData->player->getPosition().x < this->graphicsData->CenterOfMap->x)
			{
				moveEntitesWithoutExcluded(this->graphicsData->player, dt, speed, 0);
			}
			else moveEntity(this->graphicsData->player,dt, -speed, 0);

			movData.moved = 1;

		}
		movData.direction = "left";
		this->graphicsData->directionOfPlayer = movData.direction;
	}
	if (AllKeys.at("D")->isButtonPressed())
	{
		if (CheckingPossibleMove(this->graphicsData->player, "right", { 30,-15 }, Blockade, BlockadeDimension, dt, speed))
		{
			if (checkIfBackGroundMoveable("right") and this->graphicsData->player->getPosition().x > this->graphicsData->CenterOfMap->x)
			{
				moveEntitesWithoutExcluded(this->graphicsData->player, dt, -speed, 0);
			}
			else moveEntity(this->graphicsData->player,dt, speed, 0);

			movData.moved = 1;

		}
		movData.direction = "right";
		this->graphicsData->directionOfPlayer = movData.direction;
	}
	
}

void EntityPlayer::getCenterOfPlayer()
{
	centerOfGame.x = (float)this->graphicsData->window->getSize().x / 2 - 40 / 2;
	centerOfGame.y = (float)this->graphicsData->window->getSize().y / 2 - 85 / 2;
}

void EntityPlayer::initEquipment(GraphicsData* graphicsData, std::vector<std::vector<TilesOnMap*>>* Tile, EquipmentData* equipmentData, std::vector<ThrownItems*>*ItemsThrown, ThrownItems* ItemsOnTheGround)
{
	this->equipmentPtr = new Equipment(graphicsData, Tile, equipmentData, ItemsThrown, ItemsOnTheGround);
}

sf::Vector2f EntityPlayer::Center()
{
	return centerOfGame;
}




