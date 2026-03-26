#pragma once
#include "Framework/GameObject.h"
#include "Framework/Animation.h"
#include "Framework/Collision.h"

class Character :
    public GameObject
{
public:
    void setCurrentHealth(float hp) { m_currentHealth += hp; };
    float getCurrentHealth() { return m_currentHealth; };

    void setMaxHealth(float hp) { MAX_HEALTH = hp; };
    float getMaxHealth() { return MAX_HEALTH; };

protected:
    float MAX_HEALTH = 25.f;
    float m_currentHealth;
};

