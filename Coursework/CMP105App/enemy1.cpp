#include "enemy1.h"
#include <iostream>

enemy1::enemy1()
{
	clearPlayerPointer();
	setPosition(m_spawnPoint);

	m_idlePoints =
	{
		m_spawnPoint, 
		{-IDLE_DISTANCE, m_spawnPoint.y} , 
		{IDLE_DISTANCE, m_spawnPoint.y}
	};

	if(!spr_idleSheet.loadFromFile("gfx/slime_idle.png"))
		std::cerr << "No slime texture. sad";

	setTexture(&spr_idleSheet);
	// Dino is 24x24, tiles are 18x18
	// LCM(18,24) = 72.
	setSize({ 72,72 });


	for(int i = 0; i < 8; i++)
		anim_idle.addFrame({ { i * 26, 0 }, { 26, 21} });
	
	anim_idle.setFrameSpeed(1.f / 8.f);


	setCollisionBox({ {12,12}, { 45,51 } });
	anim_current = &anim_idle;
	setTextureRect(anim_current->getCurrentFrame());
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
		anim_current->animate(dt);
		setTextureRect(anim_current->getCurrentFrame());
	}
}

void enemy1::collisionResponse(GameObject& collider)
{

}