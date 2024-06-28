#ifndef ENTITYPLAYER_H
#define ENTITYPLAYER_H


#include "Entity.h"
#include "Equipment.h"

class EntityPlayer :
    public Entity
{
private:
    const sf::Vector2i PlayerSpriteSize{ 40,85 };
protected:
    Equipment* equipmentPtr;
public:
    EntityPlayer(sf::Vector2f position, std::string NameOfTxt, GraphicsData* graphicsData, std::vector<std::vector<TilesOnMap*>>* Tile, EquipmentData* equipmentData, std::vector<ThrownItems*>* ItemsThrown, ThrownItems* ItemsOnTheGround);
    ~EntityPlayer();

    void changeTexture();
    void update(const float& dt, const std::map<std::string, button*>& AllKeys);
    void render();
    void Animation(const float& dt, std::string&& direction);
    void movement(const float& dt, std::vector<std::vector<bool>>& Blockade, std::vector<std::vector<sf::Vector2f>>& BlockadeDimension, float&& speed,MovementData& movData, 
        const std::map<std::string, button*>& AllKeys);
    void getCenterOfPlayer();

    void initEquipment(GraphicsData* graphicsData, std::vector<std::vector<TilesOnMap*>>*Tile, EquipmentData* equipmentData, std::vector<ThrownItems*>*ItemsThrown, ThrownItems* ItemsOnTheGround);

    sf::Vector2f Center();
};

#endif // !ENTITYPLAYER_H