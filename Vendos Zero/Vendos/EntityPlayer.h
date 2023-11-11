#ifndef ENTITYPLAYER_H
#define ENTITYPLAYER_H


#include "Entity.h"
class EntityPlayer :
    public Entity
{
private:
    
protected:

public:
    EntityPlayer(sf::Vector2f position, std::string NameOfTxt, std::vector<sf::Sprite*>* Entit, std::map<std::string, sf::Texture*>* TexturesMap, sf::RenderWindow* Window);
    ~EntityPlayer();

    void changeTexture();
    void update(const float& dt);
    void movement(const float& dt);
    void getCenterOfPlayer();
    sf::Vector2f Center();
};

#endif // !ENTITYPLAYER_H