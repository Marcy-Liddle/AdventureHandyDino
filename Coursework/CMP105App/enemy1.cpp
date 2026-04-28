#include "enemy1.h"
#include <iostream>

enemy1::enemy1()
{
	clearPlayerPointer();
	

	m_idlePoints =
	{
		{m_spawnPoint.x - IDLE_DISTANCE, m_spawnPoint.y} , 
		m_spawnPoint,
		{m_spawnPoint.x + IDLE_DISTANCE, m_spawnPoint.y}
	};


	// Dino is 24x24, tiles are 18x18
	// LCM(18,24) = 72.
	setSize({ 72,72 });

	m_standardColour = getFillColor();
	
	setCollisionBox({ {3,3}, { 70,70 } });
	m_currAnim = &m_idle;
	setTextureRect(m_currAnim->getCurrentFrame());

}

enemy1::~enemy1()
{


}


void enemy1::update(float dt)
{


	if (m_currentHealth <= 0)
		setAlive(false);

	else 
	{

		if (m_isInvincible)
			invincibiltyFrames(dt);


		sf::Vector2f to_target;
		if (m_playerPointer)
		{
			sf::Vector2 player_loc = m_playerPointer->getPosition() + (m_playerPointer->getSize() * 0.5f);
			to_target = player_loc - getPosition();
		}
		else
		{
			
			to_target = m_idlePoints[m_pointIndex] - getPosition();

			if (to_target.length() < CLOSE_ENOUGH )
			{
				m_isWaiting = true;
				m_pointIndex += 1;
				if (m_pointIndex >= m_idlePoints.size())
					m_pointIndex = 0;
			}
		}
		if (!m_isWaiting)
		{

			m_velocity.x += to_target.normalized().x * dt * ACCELERATION;
			m_velocity.y += GRAVITY * dt;

			m_velocity *= 0.95f;


			move(m_velocity * dt);
		}
		else
		{

			m_waitAtPoint += dt;
			if (m_waitAtPoint >= IDLE_WAIT)
			{
				m_waitAtPoint = 0;
				m_isWaiting = false;
			}

		}

		if (m_velocity.x > 0 && !m_currAnim->getFlipped() || m_velocity.x < 0 && m_currAnim->getFlipped())
			// if we gotta flip, flip.
			m_currAnim->setFlipped(!m_currAnim->getFlipped());
		
		m_currAnim->animate(dt);
		setTextureRect(m_currAnim->getCurrentFrame());

	}

}



void enemy1::reset()
{

	setAlive(true);
	setPosition(m_spawnPoint);
	clearPlayerPointer();
	m_waitAtPoint = 0;
	m_isWaiting = false;

	m_currentHealth = MAX_HEALTH;
}