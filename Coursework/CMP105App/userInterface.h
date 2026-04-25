#pragma once
#include "Player.h"
class userInterface :
    public GameObject
{

public:

    userInterface();

    void drawUI(sf::RenderWindow& window, Player& player);

private:

    sf::Texture m_UITexture;

    sf::RectangleShape m_banner;


    std::vector<sf::RectangleShape> m_heartIcons;
    std::vector<sf::RectangleShape> m_energyIcons;
    std::vector<sf::RectangleShape> m_levelIcons;
    

};

