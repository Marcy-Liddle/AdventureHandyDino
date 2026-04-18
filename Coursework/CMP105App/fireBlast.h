#pragma once
#include "Framework/GameObject.h"
#include "Framework/Animation.h"

class fireBlast :
    public GameObject
{
public:
    fireBlast(bool flip, int level, sf::Vector2f pos);

    ~fireBlast() {};

    void update(float dt);

    void collisionResponse();
    
    int getDamage() { return m_damage; };
    bool getTravelling() { return m_isTraveling; };
    
private:
    Animation m_fireBall;
    Animation m_burst;
    Animation* m_currAnim;
    int m_damage = 10;

    bool m_isTraveling = true;
};