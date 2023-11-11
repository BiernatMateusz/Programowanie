#ifndef ENTITYPLAYER_H
#define ENTITYPLAYER_H


#include "Entity.h"
class EntityPlayer :
    public Entity
{
private:

protected:

public:
    EntityPlayer(std::string NameOfTxt, std::vector<sf::Sprite*>* Entit);
    ~EntityPlayer();

    void initTexture(std::string& NameOfTxt);
    void update(const float& dt);
    void movement(const float& dt);
};

#endif // !ENTITYPLAYER_H