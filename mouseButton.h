#ifndef MOUSEBUTTONH
#define MOUSEBUTTONH

#include "button.h"

class mouseButton :
    public button
{
public:
    mouseButton(sf::Mouse::Button MouseButton);
    void update(sf::RenderWindow *window, sf::Sprite* backGround);
   

    //getters
    const sf::Vector2i& mousePosGet() const;
    const sf::Vector2i& mousePosPrevGet() const;
    const sf::Vector2i& mouseTileGet() const;


private:
    void setMouseStates(sf::RenderWindow* window);
    void setMouseTile(sf::RenderWindow* window, sf::Sprite* BackGround);

    sf::Mouse::Button MouseButton;

    sf::Vector2i mousePos{};
    sf::Vector2i mousePosPrev{};
    sf::Vector2i mouseTile{};
    sf::RenderWindow* window{};
};

#endif // !MOUSEBUTTONH