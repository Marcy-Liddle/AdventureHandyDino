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

private:

    sf::Texture spr_idleSheet;
    sf::Texture spr_activeSheet;
    
    
    Animation anim_idle;
    Animation anim_active;
    Animation* anim_current;

    std::vector<sf::Vector2f> m_idlePoints;
    int m_pointIndex;
    float m_waitAtPoint = 0;
    bool m_isWaiting;

    sf::Vector2f m_spawnPoint = { 1382.97,301.5 };

    GameObject* m_playerPointer;

    const float ACCELERATION = 200.f;
    const float CLOSE_ENOUGH = 10.0f;
    const float IDLE_DISTANCE = 150.0f;
    const float IDLE_WAIT = 3.f;
    const float GRAVITY = 50.0f;

};

