#pragma once
#include "enemy1.h"
#include "fireBlast.h"
#include "Utils.h"

class boss :
    public enemy1
{

public:
    boss();
    ~boss();

    void update(float dt, Player* player);
  
    void reset();

    bool getActive() { return m_isActive; };
    void setActive(bool set) { m_isActive = set; };

    int getImunity() { return LEVEL_NOT_IMMUNE; };

    std::vector<fireBlast*> m_projectiles;

private:

    sf::Texture m_fireballTexture;
    
    float m_fireCooldown;
    bool m_isActive;

   
    std::vector<sf::Vector2f> m_fireOrigins = { {28,228}, {270, 228} };

    const int LEVEL = 3;
    const float FIRE_COOLDOWN = 1.5f;
    const int LEVEL_NOT_IMMUNE = 4;

};

