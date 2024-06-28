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
		graphicsData->CenterOfMap = &this->CenterOfMap;
		AllSpritesPointer->insert(AllSpritesPointer->end(), graphicsData->EntitiesSprite->begin(), graphicsData->EntitiesSprite->end());
	}

	if (graphicsData->TilesSprite->size() > 0)
		AllSpritesPointer->insert(AllSpritesPointer->end(), graphicsData->TilesSprite->begin(), graphicsData->TilesSprite->end());

	if (graphicsData->ItemsThrownSprite->size() > 0)
		AllSpritesPointer->insert(AllSpritesPointer->end(), graphicsData->ItemsThrownSprite->begin(), graphicsData->ItemsThrownSprite->end());


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
	graphicsData->AllSpritesPointer =this->AllSpritesPointer;
}

//Functions

void Camera::updateAllSpritesVec(GraphicsData* graphicsData, EquipmentData* equipmentData)
{
	graphicsData->AllSpritesPointer->clear();
	*graphicsData->AllSpritesPointer = *graphicsData->GraphicsSprite;

	if (graphicsData->EntitiesSprite->size() > 0)
		AllSpritesPointer->insert(AllSpritesPointer->end(), graphicsData->EntitiesSprite->begin(), graphicsData->EntitiesSprite->end());

	if (graphicsData->TilesSprite->size() > 0)
		AllSpritesPointer->insert(AllSpritesPointer->end(), graphicsData->TilesSprite->begin(), graphicsData->TilesSprite->end());
	
	if (graphicsData->ItemsThrownSprite->size() > 0)
		AllSpritesPointer->insert(AllSpritesPointer->end(), graphicsData->ItemsThrownSprite->begin(), graphicsData->ItemsThrownSprite->end());

	sortVector();
	
	equipmentData->needToUpdateCameraAllSpr = 0;
	
}

void Camera::sortVector()
{
	std::sort(this->AllSpritesPointer->begin(), this->AllSpritesPointer->end(), 
		[*this]( sf::Sprite *&y,  sf::Sprite *&x) -> bool 
			{
			return *y>*x; 
			}
		);
}

void Camera::render(sf::RenderWindow* window)
{
	//Function enables us to draw background at the beggining then all sprites
	window->draw(*this->AllSpritesPointer->back());
	for (int i=0;i<this->AllSpritesPointer->size()-1;++i)
	window->draw(*this->AllSpritesPointer->at(i));
	

}
