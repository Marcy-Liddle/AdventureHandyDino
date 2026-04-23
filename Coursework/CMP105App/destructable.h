#pragma once
#include "Framework/GameObject.h"
#include "Framework/Collision.h"
class destructable :
    public GameObject
{

public:

    destructable()
    {
        //m_strenght = grade;
    }

   // ~destructable();

    void collisionResponse(GameObject& collider, int damage) { if (damage >= m_strenght) setAlive(false); };
    
    int getStrength() { return m_strenght; };
    void setStrenght(int strenght) { m_strenght = strenght; };

private:
    int m_strenght;

};

