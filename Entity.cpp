#include "Entity.h"

Entity::Entity(sf::Vector2f position, std::string NameOfTxt, GraphicsData* graphicsData)
{
	
	this->graphicsData = graphicsData;
	initTexture(std::move(NameOfTxt),std::move(position));
	
}

Entity::~Entity()
{

}

void Entity::initTexture(std::string &&NameOfTxt, sf::Vector2f &&position)
{
	this->graphicsData->EntitiesSprite->push_back(new sf::Sprite);
	this->graphicsData->EntitiesSprite->back()->setTexture(*this->graphicsData->TexturesMap->at(NameOfTxt));
	this->graphicsData->EntitiesSprite->back()->setOrigin(7, 76); //18 76
	this->graphicsData->EntitiesSprite->back()->setPosition(position.x, position.y);

	if (this->graphicsData->player != nullptr)
		delete this->graphicsData->player;

	this->graphicsData->player = this->graphicsData->EntitiesSprite->back();
}

sf::Vector2f Entity::Center()
{

	centerOfGame.x = (float)this->graphicsData->window->getSize().x / 2;
	centerOfGame.y = (float)this->graphicsData->window->getSize().y / 2;
	return centerOfGame;
}

void Entity::moveEntity(sf::Sprite* SpriteToMove, const float& dt, float speedX, float speedY)
{
	SpriteToMove->move(dt * speedX, dt * speedY);
}

void Entity::moveEntitesWithoutExcluded(sf::Sprite* Excluded, const float& dt, float speedX, float speedY)
{

	for (auto* elem : *this->graphicsData->AllSpritesPointer)
	{
		if (elem != Excluded)
			elem->move(dt * speedX, dt * speedY);
	}
	
	if (ItemsThrown!=nullptr)
		for (auto* elem : *ItemsThrown)
		{
			elem->getAndChangeDestinationOfItem({ dt * speedX,dt * speedY });
		}

}

bool Entity::checkIfBackGroundMoveable(std::string direction)
{
	if (direction == "left")
	{
		if (this->graphicsData->backGround->getPosition().x >= 0)
			return false;
		else { return true; }
	}
	else if (direction == "right")
	{
		if (this->graphicsData->backGround->getPosition().x <= this->graphicsData->window->getSize().x - this->graphicsData->backGround->getGlobalBounds().width)
			return false;
		else { return true; }
	}
	else if (direction == "top")
	{
		if (this->graphicsData->backGround->getPosition().y >= this->graphicsData->backGround->getGlobalBounds().height)
			return false;
		else { return true; }
	}
	else if (direction == "bot")
	{
		if (this->graphicsData->backGround->getPosition().y <= this->graphicsData->window->getSize().y)
			return false;
		else { return true; }
	}
}

bool Entity::CheckingPossibleMove(sf::Sprite* SprMovable, std::string&& direction, sf::Vector2i offsetForOrigin, std::vector<std::vector<bool>>& blockade, std::vector<std::vector<sf::Vector2f>>& BlockadeDimension, const float& dt, float& speed)
{
	bool possible = 1;

	int xleft = (SprMovable->getPosition().x - this->graphicsData->backGround->getPosition().x) / 44;									//player x left (border) calculated to array dim
	int xright = (SprMovable->getPosition().x + offsetForOrigin.x - this->graphicsData->backGround->getPosition().x) / 44;				//Player x right (border) calculated to array dim
	int ytop = ((((SprMovable->getPosition().y + offsetForOrigin.y - (this->graphicsData->backGround->getPosition().y)) + 2596) / 44));	//player y top (border) calculated to array dim
	int ybot = ((((SprMovable->getPosition().y - (this->graphicsData->backGround->getPosition().y)) + 2596) / 44));						//Player y bot (border) calculated to array dim


	float xleftRealPos = SprMovable->getPosition().x - this->graphicsData->backGround->getPosition().x;
	float xrightRealPos = SprMovable->getPosition().x + offsetForOrigin.x - this->graphicsData->backGround->getPosition().x;
	float ytopRealPos = (SprMovable->getPosition().y + offsetForOrigin.y - (this->graphicsData->backGround->getPosition().y)) + 2596;
	float ybotRealPos = (SprMovable->getPosition().y - (this->graphicsData->backGround->getPosition().y)) + 2596;

	//check possible positions for different blocks

	//Done

	if (direction == "left") //DONE
	{//right points of blocks on the left side
		int yC = (ybot) * 44 + ((44 - BlockadeDimension[xleft][ybot].y) / 2) + BlockadeDimension[xleft][ybot].y;
		int yD = (ybot) * 44 + ((44 - BlockadeDimension[xleft][ybot].y) / 2);
		int yE = (ybot - 1) * 44 + ((44 - BlockadeDimension[xleft][ybot - 1].y) / 2) + BlockadeDimension[xleft][ybot - 1].y;
		int yF = (ybot - 1) * 44 + ((44 - BlockadeDimension[xleft][ybot - 1].y) / 2);

		if (blockade[xleft][ybot] == 1 and blockade[xleft][ytop] == 1)
		{
			if (!(ybotRealPos<yD and ytopRealPos>yE))
			{
				if ((xleftRealPos - (dt * speed)) < (xleft * 44 + ((44 - BlockadeDimension[xleft][ybot].x) / 2) + BlockadeDimension[xleft][ybot].x))
					possible = 0;
			}
		}

		if (blockade[xleft][ybot] == 1 and blockade[xleft][ytop] == 0)
		{
			if (!(ybotRealPos < yD))
			{
				if ((xleftRealPos - (dt * speed)) < (xleft * 44 + ((44 - BlockadeDimension[xleft][ybot].x) / 2) + BlockadeDimension[xleft][ybot].x))
					possible = 0;
			}


		}
		if (blockade[xleft][ybot] == 0 and blockade[xleft][ytop] == 1)
		{
			if (!(ytopRealPos > yE))
			{
				if ((xleftRealPos - (dt * speed)) < (xleft * 44 + ((44 - BlockadeDimension[xleft][ytop].x) / 2) + BlockadeDimension[xleft][ytop].x))
					possible = 0;
			}
		}
	}

	//Done
	if (direction == "right")
	{
		//right points of blocks on the left side
		int yC = (ybot) * 44 + ((44 - BlockadeDimension[xright][ybot].y) / 2) + BlockadeDimension[xright][ybot].y;
		int yD = (ybot) * 44 + ((44 - BlockadeDimension[xright][ybot].y) / 2);
		int yE = (ybot - 1) * 44 + ((44 - BlockadeDimension[xright][ybot - 1].y) / 2) + BlockadeDimension[xright][ybot - 1].y;
		int yF = (ybot - 1) * 44 + ((44 - BlockadeDimension[xright][ybot - 1].y) / 2);

		if (blockade[xright][ybot] == 1 and blockade[xright][ytop] == 1)
		{
			if (!(ybotRealPos<yD and ytopRealPos>yE))
			{
				if ((xrightRealPos + (dt * speed)) > (xright * 44 + ((44 - BlockadeDimension[xright][ybot].x) / 2)))
					possible = 0;
			}
		}

		if (blockade[xright][ybot] == 1 and blockade[xright][ytop] == 0)
		{
			if (!(ybotRealPos < yD))
			{
				if ((xrightRealPos + (dt * speed)) > (xright * 44 + ((44 - BlockadeDimension[xright][ybot].x) / 2)))
					possible = 0;
			}


		}

		if (blockade[xright][ybot] == 0 and blockade[xright][ytop] == 1)
		{
			if (!(ytopRealPos > yE))
			{
				if ((xrightRealPos + (dt * speed)) > (xright * 44 + ((44 - BlockadeDimension[xright][ytop].x) / 2)))
					possible = 0;
			}
		}
	} //Done


	if (direction == "top")
	{
		//bottom points of blocks on the top side
		int xC = (xleft) * 44 + ((44 - BlockadeDimension[xleft][ytop].x) / 2);
		int xD = (xleft) * 44 + ((44 - BlockadeDimension[xleft][ytop].x) / 2) + BlockadeDimension[xleft][ytop].x;
		int xE = (xleft + 1) * 44 + ((44 - BlockadeDimension[xleft + 1][ytop].x) / 2);
		int xF = (xleft + 1) * 44 + ((44 - BlockadeDimension[xleft + 1][ytop].x) / 2) + BlockadeDimension[xleft + 1][ytop].x;

		if (blockade[xleft][ytop] == 1 and blockade[xright][ytop] == 1)
		{
			if (!(xleftRealPos > xD and xrightRealPos < xE))
			{
				if ((ytopRealPos - (dt * speed)) < (ytop * 44 + ((44 - BlockadeDimension[xleft][ytop].y) / 2) + BlockadeDimension[xleft][ytop].y))
					possible = 0;
			}
		}

		if (blockade[xleft][ytop] == 1 and blockade[xright][ytop] == 0)
		{
			if (!(xleftRealPos > xD))
			{
				if ((ytopRealPos - (dt * speed)) < (ytop * 44 + ((44 - BlockadeDimension[xleft][ytop].y) / 2) + BlockadeDimension[xleft][ytop].y))
					possible = 0;
			}
		}
		if (blockade[xleft][ytop] == 0 and blockade[xright][ytop] == 1)
		{
			if (!(xrightRealPos < xE))
			{
				if ((ytopRealPos - (dt * speed)) < (ytop * 44 + ((44 - BlockadeDimension[xright][ytop].y) / 2) + BlockadeDimension[xright][ytop].y))
					possible = 0;
			}
		}
	} //Done


	if (direction == "bot")
	{
		//top points of blocks on the bottom side
		int xC = (xleft) * 44 + ((44 - BlockadeDimension[xleft][ybot].x) / 2);
		int xD = (xleft) * 44 + ((44 - BlockadeDimension[xleft][ybot].x) / 2) + BlockadeDimension[xleft][ybot].x;
		int xE = (xleft + 1) * 44 + ((44 - BlockadeDimension[xleft + 1][ybot].x) / 2);
		int xF = (xleft + 1) * 44 + ((44 - BlockadeDimension[xleft + 1][ybot].x) / 2) + BlockadeDimension[xleft + 1][ybot].x;

		if (blockade[xleft][ybot] == 1 and blockade[xright][ybot] == 1)
		{
			if (!(xleftRealPos > xD and xrightRealPos < xE))
			{
				if ((ybotRealPos + (dt * speed)) > (ybot * 44 + ((44 - BlockadeDimension[xleft][ybot].y) / 2)))
					possible = 0;
			}
		}

		if (blockade[xleft][ybot] == 1 and blockade[xright][ybot] == 0)
		{
			if (!(xleftRealPos > xD))
			{
				if ((ybotRealPos + (dt * speed)) > (ybot * 44 + ((44 - BlockadeDimension[xleft][ybot].y) / 2)))
					possible = 0;
			}

		}
		if (blockade[xleft][ybot] == 0 and blockade[xright][ybot] == 1)
		{
			if (!(xrightRealPos < xE))
			{
				if ((ybotRealPos + (dt * speed)) > (ybot * 44 + ((44 - BlockadeDimension[xright][ybot].y) / 2)))
					possible = 0;
			}
		}
	}

	return possible;
}

void Entity::pickUpThrownItem()
{

}
