#pragma once
#include "Character.h"

class enemy1 :
    public Character
{

public:
    enemy1();

    ~enemy1();

    void update(float dt) override;
    void collisionResponse(GameObject& collider) override;

    void setPlayerPointer(GameObject* pcPoint) { m_playerPointer = pcPoint; };
    void clearPlayerPointer() { m_playerPointer = nullptr;  };
    GameObject* getPlayerPointer() { return m_playerPointer; };

    void setSpawnPoint(sf::Vector2f pos) { m_spawnPoint = pos; };
    void respawn() { setPosition(m_spawnPoint); setAlive(true); };
    void setDamage(int dmg) { m_damage = dmg; }
    int getDamage() { return m_damage; };

    Animation m_idle;
    Animation m_active;

private:

    sf::Texture m_idleSheet;

    
    

    Animation* m_currAnim;

    std::vector<sf::Vector2f> m_idlePoints;
    int m_pointIndex;
    float m_waitAtPoint = 0;
    bool m_isWaiting;
      
    int m_damage;
    sf::Vector2f m_spawnPoint;

    GameObject* m_playerPointer;

    const float ACCELERATION = 200.f;
    const float CLOSE_ENOUGH = 10.0f;
    const float IDLE_DISTANCE = 150.0f;
    const float IDLE_WAIT = 3.f;
    const float GRAVITY = 50.0f;

};

