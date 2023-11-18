#include "Camera.h"
//Operators
bool operator>(const sf::Sprite &x,const sf::Sprite &y)
{
	return (y.getPosition().y ) > (x.getPosition().y);
}


//Constructors


Camera::Camera(GraphicsData *graphicsData)
{
	
	initGraphicsBasics(graphicsData);
	
	if (graphicsData->EntitiesSprite->size() > 0)
	{
		this->Player = *graphicsData->EntitiesSprite->begin();
		this->CenterOfMap = graphicsData->EntitiesSprite->front()->getPosition();
		AllSpritesPointer->insert(AllSpritesPointer->end(), graphicsData->EntitiesSprite->begin(), graphicsData->EntitiesSprite->end());
	}
	if (graphicsData->TilesSprite->size() > 0)
	{
		AllSpritesPointer->insert(AllSpritesPointer->end(), graphicsData->TilesSprite->begin(), graphicsData->TilesSprite->end());
	}
	sortVector();
	
}
//Destructors
Camera::~Camera()
{

}




void Camera::initGraphicsBasics(GraphicsData* graphicsData)
{
	this->BackGround = graphicsData->backGround;
	this->Window = graphicsData->window;
	this->AllSpritesPointer = &this->AllSprites;
	*this->AllSpritesPointer = *graphicsData->GraphicsSprite;
}

//Functions
bool Camera::checkIfBackGroundMoveable(std::string direction)
{
	if (direction == "left")
	{
		if (this->AllSpritesPointer->back()->getPosition().x >= 0)
			return false;
		else { return true; }
	}
	else if (direction == "right")
	{
		if (this->AllSpritesPointer->back()->getPosition().x <= Window->getSize().x - this->AllSpritesPointer->back()->getGlobalBounds().width)
			return false;
		else { return true; }
	}
	else if (direction == "top")
	{
		if (this->AllSpritesPointer->back()->getPosition().y >= this->AllSpritesPointer->back()->getGlobalBounds().height)
			return false;
		else { return true; }
	}
	else if (direction == "bot")
	{
		if (this->AllSpritesPointer->back()->getPosition().y <= Window->getSize().y)
			return false;
		else { return true; }
	}
}

void Camera::moveAllObjects(sf::Sprite* Excluded, const float& dt, float speedX,float speedY)
{
	for (auto* elem : *this->AllSpritesPointer)
	{
		if (elem!=Excluded)
		elem->move(dt * speedX, dt * speedY);
	}
}

void Camera::movePlayer(const float& dt, float speedX, float speedY)
{
	this->Player->move(dt * speedX, dt * speedY);
}

bool Camera::CheckingPossibleMove(std::string&& direction, std::vector<std::vector<bool>>& blockade, std::vector<std::vector<sf::Vector2f>>& BlockadeDimension,
	const float& dt, float& speed)
{
	bool possible = 1;

	int xleft = (this->Player->getPosition().x - 11 - BackGround->getPosition().x) / 44;					//player x left (border) calculated to array dim
	int xright = (this->Player->getPosition().x - 11 + 30 - BackGround->getPosition().x) / 44;			//Player x right (border) calculated to array dim
	int ytop = (((this->Player->getPosition().y - 15 - (BackGround->getPosition().y)) + 2596) / 44);		//player y top (border) calculated to array dim
	int ybot = (((this->Player->getPosition().y - (BackGround->getPosition().y)) + 2596) / 44);			//Player y bot (border) calculated to array dim

	float xleftRealPos = this->Player->getPosition().x - 11 - BackGround->getPosition().x;
	float xrightRealPos = this->Player->getPosition().x - 11 + 30 - BackGround->getPosition().x;
	float ybotRealPos = (this->Player->getPosition().y - (BackGround->getPosition().y)) + 2596;
	float ytopRealPos = (this->Player->getPosition().y - 15 - (BackGround->getPosition().y)) + 2596;

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
				if ((xrightRealPos+(dt*speed)) > (xright * 44 + ((44 - BlockadeDimension[xright][ybot].x) / 2)))
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
			if (!(xleftRealPos>xD and xrightRealPos<xE))
			{
				if ((ytopRealPos-(dt*speed)) < (ytop * 44 + ((44 - BlockadeDimension[xleft][ytop].x) / 2) + BlockadeDimension[xleft][ytop].x))
					possible = 0;
			}
		}

		if (blockade[xleft][ytop] == 1 and blockade[xright][ytop] == 0)
		{
			if (!(xleftRealPos > xD)) 
			{
				if ((ytopRealPos - (dt * speed)) < (ytop * 44 + ((44 - BlockadeDimension[xleft][ytop].x) / 2) + BlockadeDimension[xleft][ytop].x))
					possible = 0;
			}
		}
		if (blockade[xleft][ytop] == 0 and blockade[xright][ytop] == 1)
		{
			if (!(xrightRealPos < xE)) 
			{
				if ((ytopRealPos - (dt * speed)) < (ytop * 44 + ((44 - BlockadeDimension[xright][ytop].x) / 2) + BlockadeDimension[xright][ytop].x))
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
				if ((ybotRealPos+(dt*speed)) > (ybot * 44 + ((44 - BlockadeDimension[xleft][ybot].x) / 2) ))
					possible = 0;
			}
		}

		if (blockade[xleft][ybot] == 1 and blockade[xright][ybot] == 0)
		{
			if (!(xleftRealPos > xD))
			{
				if ((ybotRealPos + (dt * speed)) > (ybot * 44 + ((44 - BlockadeDimension[xleft][ybot].x) / 2) ))
					possible = 0;
			}

		}
		if (blockade[xleft][ybot] == 0 and blockade[xright][ybot] == 1)
		{
			if (!(xrightRealPos < xE))
			{
				if ((ybotRealPos + (dt * speed)) > (ybot * 44 + ((44 - BlockadeDimension[xright][ybot].x) / 2) ))
					possible = 0;
			}
		}
	}

	return possible;
	
}

void Camera::PlayerAnimation(const float& dt, std::string&& direction)
{
	if (direction != "left" and direction != "right" and direction != "top" and direction != "bot")
	{
		time = 0;
	}
	else time += dt;

	int timeUsed = time * 100;

	float WhichAnimation = timeUsed % 30;
	WhichAnimation = (timeUsed - WhichAnimation)/30;

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
		this->Player->setTextureRect(sf::IntRect(22+40*WhichAnimationN, 20+234, 40, 85));
		lastDir = 3;
	}
	if (direction == "right")
	{
		this->Player->setTextureRect(sf::IntRect(22+40 * WhichAnimationN,20+ 78, 40, 85));
		lastDir = 1;
	}
	if (direction == "top")
	{
		this->Player->setTextureRect(sf::IntRect(22+40 * WhichAnimationN, 20+156, 40, 85));
		lastDir = 2;
	}
	if (direction == "bot")
	{
		this->Player->setTextureRect(sf::IntRect(22+40 * WhichAnimationN, 20+0, 40, 85));
		lastDir = 0;
	}

	if (direction != "left" and direction != "right" and direction != "top" and direction != "bot")
	{
		this->Player->setTextureRect(sf::IntRect(22 + 40 * WhichAnimation, 20 + 78*lastDir, 40, 85));
	}

}

void Camera::sortVector()
{
	std::sort(this->AllSpritesPointer->begin(), this->AllSpritesPointer->end(), 
		[this]( sf::Sprite *&y,  sf::Sprite *&x) -> bool 
			{
			return *y>*x; 
			}
		);
}

bool Camera::movementAll(const float& dt, std::vector<std::vector<bool>>& Blockade, std::vector<std::vector<sf::Vector2f>>& BlockadeDimension, float&& speed)
{
	bool moved = 0;
	std::string direction{};


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		if (CheckingPossibleMove("left", Blockade, BlockadeDimension, dt, speed))
		{
			if (checkIfBackGroundMoveable("left") and Player->getPosition().x < CenterOfMap.x)
			{
				moveAllObjects(this->Player, dt, speed, 0);
			}
			else movePlayer(dt, -speed, 0);

			moved = 1;
			
		}
		direction = "left";
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		if (CheckingPossibleMove("right", Blockade, BlockadeDimension, dt, speed))
		{
			if (checkIfBackGroundMoveable("right") and Player->getPosition().x > CenterOfMap.x)
			{
				moveAllObjects(this->Player, dt, -speed, 0);
			}
			else movePlayer(dt, speed, 0);

			moved = 1;
			
		}
		direction = "right";
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		if (CheckingPossibleMove("top", Blockade, BlockadeDimension, dt, speed))
		{
			if (checkIfBackGroundMoveable("top") and Player->getPosition().y < CenterOfMap.y)
			{
				moveAllObjects(this->Player, dt, 0, speed);
			}
			else movePlayer(dt, 0, -speed);

			moved = 1;
			

		}
		direction = "top";
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		if (CheckingPossibleMove("bot", Blockade, BlockadeDimension, dt, speed))
		{
			if (checkIfBackGroundMoveable("bot") and Player->getPosition().y > CenterOfMap.y)
			{
				moveAllObjects(this->Player, dt, 0, -speed);
			}
			else movePlayer(dt, 0, speed);
			
			moved = 1;
		}
		direction = "bot";
	}

	PlayerAnimation(dt, std::move(direction));

	return moved;
}

void Camera::render(sf::RenderWindow* window)
{
	//Function enables us to draw background at the beggining then all sprites
	window->draw(*this->AllSpritesPointer->back());
	for (int i=0;i<this->AllSpritesPointer->size()-1;++i)
	window->draw(*this->AllSpritesPointer->at(i));

}
