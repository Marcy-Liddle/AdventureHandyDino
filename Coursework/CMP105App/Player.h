#pragma once
#include "Framework/GameObject.h"

#include "Utils.h"
#include "Framework/AudioManager.h"
#include "Character.h"
#include "fireBlast.h"
#include <map>

enum class playerState
{
    NEUTRAL,
    JUMPING,
    DASHING,
    CLIMBING

};

class Player :
    public Character
{

public:
    Player();

    void handleInput(float dt) override;
    void update(float dt) override;
    void collisionResponse(GameObject& collider) override;
    
    void setEdges(float left, float right) { m_leftEdge = left; m_rightEdge = right; };
   
   
    void reset();
  


    bool isAttacking() { return m_isKicking; };

    
    int getLevel() { return m_level; };
    void levelUp() { m_level += 1; };
    void levelUP(int lvl) { m_level = lvl; };

    void setRespawn(sf::Vector2f respawn) { m_spawnPoint = respawn; };

    GameObject m_aggroRange;
    GameObject m_meleeHitBox;

    std::vector<fireBlast*> m_projectiles;

    void addAbility(std::string ability) 
    { 
        m_abilities.insert({ ability, true }); 
        m_abilities[ability] = true;
    };

    bool isDashing() { return m_isDashing; };
    int dashAmount() { return m_numberOfDashes; };

private:
    sf::Texture m_dinoTexture;
    sf::Texture m_fireballTexture;

    std::map<std::string, bool> m_abilities;

    Animation* m_currAnim;
    Animation* m_prevAnim;

    Animation m_idle;
    Animation m_walk;
    Animation m_sprint;
    Animation m_kick;
    Animation m_hazardKick;

    sf::Vector2f m_spawnPoint;

    sf::Vector2f m_accel;
    float m_sprintTimer = 0.f;
    bool m_isGrounded;
    float m_leftEdge;
    float m_rightEdge;

    int m_level = 1;

    bool m_isKicking;
 
    int m_numberOfDashes;
    bool m_isDashing = false;
    float m_dashCooldown = 0.f;

    sf::FloatRect m_normalHurtBox;

    //different kick hitbox/hurtbox for facing l/r (0,1)
    sf::FloatRect m_kickHitBox[2];
    sf::FloatRect m_meleeHurtBox[2];



    

    const float SPRINT_COOLDOWN = 2.0f;
    const float SPRINT_SPEED_MULT = 1.5f;
    const float SPEED = 10.0f;
    const float GRAVITY = 50.0f;
    const float COEFF_OF_REST = 0.8f;
    const float DRAG_FACTOR = 0.9f;
    const float AIR_DRAG_FACTOR = 0.99f;
    const float TURN_DRAG = 0.6f;       // allow snappy decel for turning
    const float JUMP_FORCE = 15.0f;
    const float SPRINT_ANIM_THRESHOLD = 1.2f * SPEED;
    const float ACTIVATE_RANGE_SQUARED = 700.0f;
    const float DASH_SPEED = 25.0f;
    const float DASH_COOLDOWN = 0.35f;
};



