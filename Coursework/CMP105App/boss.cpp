#include "boss.h"


boss::boss()
{
	if (!m_idleSheet.loadFromFile("gfx/dragon.png"))
		Utils::printMsg("Dragon image already slain", MessageType::ERROR);

	setTexture(&m_idleSheet);


	for (int i = 0; i < 6; i++)
		m_idle.addFrame({ { i * 72, 0 }, { 72, 72} });

	m_idle.setFrameSpeed(0.6);

	setSize({ 288.f, 288.f });
	setCollisionBox({ {68,172} , {140,100} });
	m_currAnim = &m_idle;
	
	if (!m_fireballTexture.loadFromFile("gfx/fireBall.png"))
		Utils::printMsg("Fire texture got put out.", MessageType::ERROR);


	MAX_HEALTH = 150.f;
	m_currentHealth = MAX_HEALTH;

	m_fireCooldown = 0.f;
}

boss::~boss()
{

}


void boss::update(float dt, Player* player)
{


	if (m_currentHealth <= 0)
		setAlive(false);

	if (!isAlive() || !m_isActive)
		return;

	if (m_isInvincible)
		invincibiltyFrames(dt);


	if (m_fireCooldown == 0)
	{
		fireBlast* newFire = new fireBlast(!m_currAnim->getFlipped(), LEVEL, getPosition() + m_fireOrigins[m_currAnim->getFlipped()]);
		newFire->setTexture(&m_fireballTexture);
		m_projectiles.push_back(newFire);
		m_audio->playSoundbyName("dragonRoar");
		m_fireCooldown += dt;
	
	}
	else if (m_fireCooldown > FIRE_COOLDOWN)
	{
		m_fireCooldown = 0;
	}
	else
	{
		m_fireCooldown += dt;
	}

	for (fireBlast* f : m_projectiles)
	{
		if (f->isAlive()) f->update(dt);

	}

	m_velocity.y += GRAVITY * dt ;
	move(m_velocity);


	bool playerXDistance = {player->getPosition().x > getPosition().x};

	if (playerXDistance && !m_currAnim->getFlipped() || !playerXDistance && m_currAnim->getFlipped())
		// if we gotta flip, flip.
		m_currAnim->setFlipped(!m_currAnim->getFlipped());

	m_currAnim->animate(dt);
	setTextureRect(m_currAnim->getCurrentFrame());


}


void boss::reset()
{

	m_projectiles.clear();
	setAlive(true);
	setActive(false);

}