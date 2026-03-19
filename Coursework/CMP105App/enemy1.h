#pragma once
#include "Framework/GameObject.h"
#include "Framework//Animation.h"
#include "Framework/Collision.h"

class enemy1 :
    public GameObject
{

public:
    enemy1();

    ~enemy1();

    void update(float dt) override;
    void collisionResponse(GameObject& collider) override;

    void setPlayerPointer(GameObject* pcPoint) { m_playerPointer = pcPoint; };
    void clearPlayerPointer() { m_playerPointer = nullptr;  };

private:

    sf::Texture spr_idleSheet;
    sf::Texture spr_activeSheet;
    
    Animation anim_idle;
    Animation anim_active;
    Animation* anim_current;

    std::vector<sf::Vector2f> m_idlePoints;
    sf::Vector2f m_spawnPoint = { 1382.97,301.5 };

    GameObject* m_playerPointer;

    const float ACCELERATION = 350.f;
    const float CLOSE_ENOUGH = 50.0f;
    const float IDLE_DISTANCE = 50.0f;
};

