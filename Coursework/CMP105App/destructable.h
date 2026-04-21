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

    void collisionResponse(GameObject& collider) override { setAlive(false); };
    
    int getStrength() { return m_strenght; };


private:
    int m_strenght;

};

