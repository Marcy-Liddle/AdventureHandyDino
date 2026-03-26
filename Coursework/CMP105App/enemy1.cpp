#include "enemy1.h"
#include <iostream>

enemy1::enemy1()
{
	clearPlayerPointer();
	setPosition(m_spawnPoint);

	m_idlePoints =
	{
		{m_spawnPoint.x - IDLE_DISTANCE, m_spawnPoint.y} , 
		m_spawnPoint,
		{m_spawnPoint.x + IDLE_DISTANCE, m_spawnPoint.y}
	};

	if(!spr_idleSheet.loadFromFile("gfx/characters/enemies/slime/slimer-idle1.png"))
		std::cerr << "No slime texture. sad";
	
	setTexture(&spr_idleSheet);
	// Dino is 24x24, tiles are 18x18
	// LCM(18,24) = 72.
	setSize({ 36,36 });


	for(int i = 0; i < 8; i++)
		anim_idle.addFrame({ { i * 24, 0 }, { 24, 24} });
	
	anim_idle.setFrameSpeed(1.f / 4.f);


	setCollisionBox({ {12,12}, { 45,51 } });
	anim_current = &anim_idle;
	//setTextureRect(anim_current->getCurrentFrame());

}

enemy1::~enemy1()
{


}


void enemy1::update(float dt)
{
	if (!isAlive())
		setPosition(m_spawnPoint);
	else 
	{
	//	anim_current->animate(dt);
		//setTextureRect(anim_current->getCurrentFrame());
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
			m_velocity += to_target.normalized() * dt * ACCELERATION;
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

	}


}

void enemy1::collisionResponse(GameObject& collider)
{

}