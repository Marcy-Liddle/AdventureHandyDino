#include "Player.h"

Player::Player()
{
	if (!m_dinoTexture.loadFromFile("gfx/dino1.png"))
		std::cerr << "No dino texture. sad \n";
	if (!m_fireballTexture.loadFromFile("gfx/fireBall.png"))
		std::cerr << "Fire texture got put out\n";

	setTexture(&m_dinoTexture);
	// Dino is 24x24, tiles are 18x18
	// LCM(18,24) = 72.
	setSize({ 72,72 });		
	setPosition({ 24, 100 });

	for (int i = 0; i < 4; i++)
		m_idle.addFrame({{ i * 24, 0 }, { 24, 24} });

	for (int i = 4; i < 10; ++i)
		m_walk.addFrame({{ i * 24, 0 }, { 24, 24}});

	for (int i = 10; i < 14; i++)
		m_kick.addFrame({ { i * 24, 0 }, { 24, 24} });

	for (int i = 14; i < 16; i++)
		m_hazardKick.addFrame({ { i * 24, 0 }, { 24, 24} });

	for(int i = 16; i < 24; i++)
		m_sprint.addFrame({ { i * 24, 0 }, { 24, 24} });


	
	m_currAnim = &m_walk;
	m_walk.setFrameSpeed(1.f / 10.f);
	m_idle.setFrameSpeed(1.f / 4.f);
	m_sprint.setFrameSpeed(1.4 / 15.0f);
	m_kick.setFrameSpeed(1.f / 8.f);
	 m_kick.setLooping(false);
	
	m_normalHurtBox = sf::FloatRect({ {12,12}, { 45,51} });
	setCollisionBox(m_normalHurtBox);
	m_meleeHitBox.setSize(getSize());

	m_kickHitBox[0] = sf::FloatRect({0,39}, {23,19});
	m_kickHitBox[1] = sf::FloatRect({ 49,39 }, { 23,19 });

	m_meleeHurtBox[0] = sf::FloatRect({23,12}, {39,51});
	m_meleeHurtBox[1] = sf::FloatRect({ 12,12 }, { 39,51 });
	
	m_isGrounded = false;

	float radius = getSize().x / 2.f;
	sf::Vector2f centre = { getPosition().x + radius, getPosition().y + radius };

	m_aggroRange.setSize({ 360.f , 360.f });
	radius = m_aggroRange.getSize().x /2;
	m_aggroRange.setPosition({ centre.x - radius, centre.y - radius });
	m_aggroRange.setFillColor(sf::Color::Magenta); //debug

	setCurrentHealth(getMaxHealth());

}

void Player::handleInput(float dt)
{
	m_accel = { 0,0 };
	if (m_input->isKeyDown(sf::Keyboard::Scancode::H))
		m_isKicking = true;
	if (m_input->isKeyDown(sf::Keyboard::Scancode::A))
		m_accel.x -= SPEED;
	if (m_input->isKeyDown(sf::Keyboard::Scancode::D))
		m_accel.x += SPEED;
	if (m_input->isPressed(sf::Keyboard::Scancode::Space) && m_isGrounded)
	{
		m_velocity.y = - JUMP_FORCE;
		m_isGrounded = false;	// can't be jumping if we're in the air
		m_audio->playSoundbyName("jump");
	}
	else if (m_input->isPressed(sf::Keyboard::Scancode::Space) && !m_isGrounded && m_canDoubleJump && !m_hasDoubleJumped)
	{
		m_velocity.y = - JUMP_FORCE;
		m_hasDoubleJumped = true;
		m_audio->playSoundbyName("jump");
	}
	if (m_input->isKeyDown(sf::Keyboard::Scancode::R))	// Reset (for debugging)
	{
		reset();
	}
	if (m_input->isPressed(sf::Keyboard::Scancode::LControl) && m_sprintTimer <= 0)
	{
		if (!m_currAnim->getFlipped())
			m_velocity.x = SPEED * SPRINT_SPEED_MULT;
		else
			m_velocity.x = -SPEED * SPRINT_SPEED_MULT;
		m_sprintTimer = SPRINT_COOLDOWN;
	}
	if (m_input->isPressed(sf::Keyboard::Scancode::F))
	{
		fireBlast* newFire = new fireBlast(m_currAnim->getFlipped(), m_fireLevel, getPosition());
		newFire->setTexture(&m_fireballTexture);
		m_projectiles.push_back(newFire);
	}

	// for debugging: "Where am I?"
	if (m_input->isPressed(sf::Keyboard::Scancode::T))
	{
		std::cout << getPosition().x << "/" << getPosition().y << "\n";
	}
	
}

void Player::update(float dt)
{
	m_prevAnim = m_currAnim;
	if (getCurrentHealth() <= 0)
		reset();

	if (m_isInvincible)
		invincibiltyFrames(dt);


	for (fireBlast* f : m_projectiles)
	{
		if (f->isAlive()) f->update(dt);
	}


	float radius = getSize().x / 2.f;
	sf::Vector2f centre = { getPosition().x + radius, getPosition().y + radius };

	m_aggroRange.setSize({ 540.f , 540.f });
	radius = m_aggroRange.getSize().x / 2;
	m_aggroRange.setPosition({ centre.x - radius, centre.y - radius });


	// newtonian model
	m_accel.y += GRAVITY;
	m_velocity += dt * m_accel;
	if (m_isGrounded && abs(m_accel.x) < 1.f) m_velocity *= DRAG_FACTOR;
	else if (!m_isGrounded) m_velocity *= AIR_DRAG_FACTOR;
	else if (m_accel.x * m_velocity.x < 0) m_velocity *= TURN_DRAG;

	m_isGrounded = false;	// every frame we are falling unless proved otherwise by floor collision

	if (m_sprintTimer > 0) m_sprintTimer -= dt;	// tick down the sprint cooldown

	// handle animation
	if (m_isKicking)
	{
		setCollisionBox(m_meleeHurtBox[!m_currAnim->getFlipped()]);
		
		m_meleeHitBox.setPosition(getPosition());
		m_meleeHitBox.setCollisionBox(m_kickHitBox[!m_currAnim->getFlipped()]);;
	

		if (m_currAnim != &m_kick)
			m_currAnim = &m_kick;

		if (!m_kick.getPlaying())
		{
			m_isKicking = false;
			m_kick.reset();
			m_kick.setPlaying(true);
			setCollisionBox(m_normalHurtBox);
			m_meleeHitBox.setCollisionBox({ { 0,0 }, { 0,0 } });
		}

	}
	else
	{
		
		float speed = std::abs(m_velocity.x);	// sideways speed
		if (speed < 1.0)
			m_currAnim = &m_idle;
		else if (speed > SPRINT_ANIM_THRESHOLD)
			m_currAnim = &m_sprint;
		else
			m_currAnim = &m_walk;
}
		// face direction
		if (m_velocity.x > 0 && m_currAnim->getFlipped() || m_velocity.x < 0 && !m_currAnim->getFlipped())
			// if we gotta flip, flip.
			m_currAnim->setFlipped(!m_currAnim->getFlipped());
	
	move(m_velocity);


	// keep within L/R bounds
	if (getPosition().x < m_leftEdge)
	{
		setPosition({ m_leftEdge, getPosition().y });
	}
	if (getPosition().x > m_rightEdge - getSize().x)
	{
		setPosition({ m_rightEdge - getSize().x, getPosition().y});
	}

	m_currAnim->animate(dt);
	setTextureRect(m_currAnim->getCurrentFrame());
}




// only used on tiles for now.
// collider confirmed to be tile with .isCollider=true
void Player::collisionResponse(GameObject& collider)
{
	sf::FloatRect playerCollider = getCollisionBox();
	sf::FloatRect wallBounds = collider.getCollisionBox();
	auto overlap = playerCollider.findIntersection(wallBounds);
	if (!overlap) return; // if there is no overlap, then leave.
	if (overlap->size.x < overlap->size.y)
	{
		// taller than wide -> collision is side-on
		if (playerCollider.position.x < wallBounds.position.x)
			move({ -overlap->size.x, 0 });
		else
			move({ overlap->size.x, 0 });
	}
	else
	{
		if (playerCollider.position.y < wallBounds.position.y)
		{
			// We are above the wall (Landing)
			move({ 0, -overlap->size.y });
			m_velocity.y = 0;       // Stop falling
			m_isGrounded = true;    // Enable jumping
			m_hasDoubleJumped = false;	// more jumping possible
		}
		else
		{
			// We hit the ceiling (Bonk)
			move({ 0, overlap->size.y });
			m_velocity.y = 0;       // Stop moving up
		}
	}
}


void Player::reset()
{
	setPosition({ 0, 50 });
	m_velocity = { 0,0 };

	m_currentHealth = MAX_HEALTH;

}