#pragma once
#include "Framework/GameObject.h"

#include "Utils.h"
#include "Framework/AudioManager.h"
#include "Character.h"
#include "fireBlast.h"



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
    void setCanDoubleJump(bool value) { m_canDoubleJump = value; };
    bool canDoubleJump() { return m_canDoubleJump; };
    void setAudio(AudioManager* audio) { m_audio = audio; };
    bool isAttacking() { return m_isKicking; };

    int getKickLevel() { return m_kickLevel; };
    void kickLevelUp(int level) { m_kickLevel = level; };

    int getFireLevel() { return m_fireLevel; };
    void fireLevelUp(int level) { m_fireLevel = level; };

    void setRespawn(sf::Vector2f respawn) { m_spawnPoint = respawn; };

    GameObject m_aggroRange;
    GameObject m_meleeHitBox;

    std::vector<fireBlast*> m_projectiles;

private:
    sf::Texture m_dinoTexture;
    sf::Texture m_fireballTexture;


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

    int m_kickLevel = 1;
    int m_fireLevel = 1;

    bool m_canDoubleJump;
    bool m_hasDoubleJumped;
    bool m_isKicking = false;

    sf::FloatRect m_normalHurtBox;

    //different kick hitbox/hurtbox for facing l/r (0,1)
    sf::FloatRect m_kickHitBox[2];
    sf::FloatRect m_meleeHurtBox[2];


    AudioManager* m_audio;


    const float SPRINT_COOLDOWN = 2.0f;
    const float SPRINT_SPEED_MULT = 2.5f;
    const float SPEED = 10.0f;
    const float GRAVITY = 50.0f;
    const float COEFF_OF_REST = 0.8f;
    const float DRAG_FACTOR = 0.9f;
    const float AIR_DRAG_FACTOR = 0.99f;
    const float TURN_DRAG = 0.6f;       // allow snappy decel for turning
    const float JUMP_FORCE = 15.0f;
    const float SPRINT_ANIM_THRESHOLD = 1.2f * SPEED;
    const float ACTIVATE_RANGE_SQUARED = 700.0f;
    
};



