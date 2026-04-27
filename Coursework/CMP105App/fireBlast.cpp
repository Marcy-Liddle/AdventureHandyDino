#include "fireBlast.h"



fireBlast::fireBlast(bool flip, int level, sf::Vector2f pos)
{

    for (int i = 0; i < 5; i++)
        m_fireBall.addFrame({ { i * 24, (level-1) * 24 }, {24,24} });
    for (int i = 5; i < 12; i++)
        m_burst.addFrame({ {i * 24, (level-1) * 24}, {24,24} });

    m_currAnim = &m_fireBall;
    m_currAnim->setFlipped(flip);

    m_fireBall.setFrameSpeed(1.f / 8.f);
    
    m_burst.setFrameSpeed(1.f / 8.f);
    m_burst.setLooping(false);

    setPosition(pos);
    setSize({ 48,48 });
    setCollisionBox({ {17,9},{27,30} });

    m_damage *= level;

    float fraction = 1 + level / 2 ;

    if (flip)
        setVelocity({ -500 * fraction ,0 });
    else
        setVelocity({ 500 * fraction , 0});
};



void fireBlast::update(float dt)
{

    move(m_velocity * dt);

    m_currAnim->animate(dt);
    setTextureRect(m_currAnim->getCurrentFrame());

    if (!m_isTraveling && !m_currAnim->getPlaying())
        setAlive(false);
};

void fireBlast::collisionResponse()
{
    m_velocity = { 0,0 };
    m_currAnim = &m_burst;
    m_isTraveling = false;
}