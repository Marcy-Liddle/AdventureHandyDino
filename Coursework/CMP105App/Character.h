#pragma once
#include "Framework/GameObject.h"
#include "Framework/Animation.h"
#include "Framework/Collision.h"
#include <iostream>
//If time allows, transform into components
class Character :
    public GameObject
{
public:
    void setCurrentHealth(float hp) { m_currentHealth = hp; };
    float getCurrentHealth() { return m_currentHealth; };
    void healAndDeal(float hp) { m_currentHealth += hp; };

    void resetHealth()
    {
        m_currentHealth = MAX_HEALTH;
        setAlive(true);
    }


    void setMaxHealth(float hp) { MAX_HEALTH = hp; };
    float getMaxHealth() { return MAX_HEALTH; };
    void worldCollision(GameObject& collider);
    void invincibiltyFrames(float dt);

    void setInvincible(bool set) { m_isInvincible = set; };
    bool getInvincible() { return m_isInvincible; }

    void knockBack(sf::Vector2f distance) 
    { 
        move({ m_velocity.x + -distance.x, m_velocity.y + -distance.y }); 
    }

protected:
    float MAX_HEALTH = 25.f;
    float m_currentHealth = MAX_HEALTH;

    bool m_isInvincible = false;
    float m_invulnerableTimer = 0.f;
    const float INVINCIBILITY_TIME = 2.f;

};

