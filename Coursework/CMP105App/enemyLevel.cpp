#include "enemyLevel.h"
#include <iostream>

enemyLevel::enemyLevel(sf::RenderWindow& window, Input& input, GameState& gameState, AudioManager& audio) 
	: Scene(window, input, gameState, audio)
{
	// setup player 
	m_player.setInput(&m_input);
	m_player.setEdges(0, WORLD_SIZE.x);
	m_player.setPosition({ 100, 400 });
	m_player.setAudio(&m_audio);
	
	m_screenLoader.create("screen1");

	
}

void enemyLevel::handleInput(float dt) 
{
	if (m_input.isPressed(sf::Keyboard::Scancode::Escape))
		m_gameState.setCurrentState(State::PAUSE);
	else
		m_player.handleInput(dt);

	
}

void enemyLevel::onBegin()
{
	m_audio.playMusicbyName("bgm");

	if (m_won)
		reset();
}

void enemyLevel::onEnd()
{
	m_audio.stopAllMusic();
}

void enemyLevel::update(float dt)
{
	m_player.update(dt);
	

	for (auto& t : m_screenLoader.m_enemies)
	{
		t->update(dt);
	}


	m_screenLoader.m_boss->update(dt, &m_player);
	if (!m_screenLoader.m_boss->isAlive())
	{
		m_screenLoader.m_winTrigger.setAlive(true);
	
	}

	handleCollision();

	updateCameraAndBackground();
}


void enemyLevel::handleCollision()
{
	// handle collisions
	std::vector<GameObject>& level = *m_screenLoader.getLevel();
	for (auto& t : level)
	{
		if (t.isCollider() && Collision::checkBoundingBox(m_player, t))
		{
			m_player.collisionResponse(t);
		}

		for (auto& e : m_screenLoader.m_enemies)
		{
			if (t.isCollider() && Collision::checkBoundingBox(*e, t))
			{
				e->worldCollision(t);
			}
		}


		for (int i = 0; i < m_player.m_projectiles.size(); i++)
		{
			if (t.isCollider() && m_player.m_projectiles[i]->isAlive() && Collision::checkBoundingBox(t, *m_player.m_projectiles[i]))
			{
				m_player.m_projectiles[i]->collisionResponse();
			}

		}

		if (t.isCollider() && m_screenLoader.m_boss->getActive() && Collision::checkBoundingBox(t, *m_screenLoader.m_boss))
		{
			m_screenLoader.m_boss->worldCollision(t);
		}

		for (int i = 0; i < m_screenLoader.m_boss->m_projectiles.size(); i++)
		{
			if (t.isCollider() && m_screenLoader.m_boss->m_projectiles[i]->isAlive() && Collision::checkBoundingBox(t, *m_screenLoader.m_boss->m_projectiles[i]))
			{
				m_screenLoader.m_boss->m_projectiles[i]->collisionResponse();
			}

		}
	}

	for (auto& e : m_screenLoader.m_enemies)
	{
		if (Collision::checkBoundingCircle(m_player.m_aggroRange, *e))
		{
			if (e->getPlayerPointer() == nullptr)
				e->setPlayerPointer(&m_player);

			if (!m_player.getInvincible() && e->isAlive())
			{
				if (Collision::checkBoundingBox(m_player, *e))
				{
					m_player.healAndDeal(-5.f);
					//std::cout << m_player.getCurrentHealth() << "\n";
					m_player.collisionResponse(*e);
					m_player.setInvincible(true);
					m_player.knockBack({ 10,10 });
					m_audio.playSoundbyName("hit");
				}

			}

			if (m_player.isAttacking() && Collision::checkBoundingBox(m_player.m_meleeHitBox, *e))
			{
				e->healAndDeal(-5.f * m_player.getLevel());
				m_audio.playSoundbyName("softImpact");
			}


		}
		else
		{
			e->clearPlayerPointer();
		}


	}


	for (int i = 0; i < m_player.m_projectiles.size(); i++)
	{
		if (m_player.m_projectiles[i]->isAlive())
		{
			for (auto& e : m_screenLoader.m_enemies)
			{
				if (e->isAlive() && Collision::checkBoundingBox(*e, *m_player.m_projectiles[i]))
				{
					e->healAndDeal(-7.5f * m_player.getLevel());
					e->invincibiltyFrames(true);
					m_player.m_projectiles[i]->collisionResponse();

					m_audio.playSoundbyName("explosion2");
				}
			}


			for (auto d : m_screenLoader.m_destructables)
			{

				if (d->isAlive() && Collision::checkBoundingBox(*d, *m_player.m_projectiles[i]))
				{
					m_player.m_projectiles[i]->collisionResponse();
					d->collisionResponse(m_player.m_projectiles[i]->getDamage());
					if (!d->isAlive())
						m_audio.playSoundbyName("impact");
				}

			}

			if (m_screenLoader.m_boss->isAlive() && Collision::checkBoundingBox(*m_player.m_projectiles[i], *m_screenLoader.m_boss))
			{
				m_player.m_projectiles[i]->collisionResponse();
				if (m_player.getLevel() >= m_screenLoader.m_boss->getImunity())
				{
					m_screenLoader.m_boss->healAndDeal(-m_player.m_projectiles[i]->getDamage());
					m_screenLoader.m_boss->setInvincible(true);
					m_audio.playSoundbyName("impact");
				}
				else
				{
					m_audio.playSoundbyName("weak");
				}


			}


		}
	}

	for (int i = 0; i < m_screenLoader.m_boss->m_projectiles.size(); i++)
	{
		if (m_screenLoader.m_boss->m_projectiles[i]->isAlive() && Collision::checkBoundingBox(m_player  , *m_screenLoader.m_boss->m_projectiles[i]))
		{
			m_screenLoader.m_boss->m_projectiles[i]->collisionResponse();
			m_player.healAndDeal(-m_screenLoader.m_boss->m_projectiles[i]->getDamage());
		}
		
	}

	for (auto d : m_screenLoader.m_destructables)
	{

		if (d->isAlive() && Collision::checkBoundingBox(*d, m_player))
		{
			m_player.collisionResponse(*d);
		}

	}

	for (auto c : m_screenLoader.m_checkPoints)
	{
		if (c->isAlive() && Collision::checkBoundingBox(m_player, *c))
		{
			c->setSpawn(&m_player);
		}
	}


	for (auto o : m_screenLoader.m_obstacles)
	{
		if (o->isAlive() && Collision::checkBoundingBox(m_player, *o))
		{
			o->obstacleInteract(&m_player);
		}

	}

	for (auto c : m_screenLoader.m_consumables)
	{

		if (c->isAlive() && Collision::checkBoundingBox(m_player, *c))
		{
			c->consume(&m_player);
			if (!c->isAlive())
			{
				switch (c->m_id)
				{
					case 'h': m_audio.playSoundbyName("heal"); break;
					default: m_audio.playSoundbyName("fanfare"); break;
				}

				}
		}
	}

	if (Collision::checkBoundingBox(m_player, m_screenLoader.m_bossTrigger))
	{
		m_screenLoader.m_boss->setActive(true);
		m_screenLoader.m_boss->setAudio(&m_audio);
	}
	
	if (m_screenLoader.m_winTrigger.isAlive() && Collision::checkBoundingBox(m_player, m_screenLoader.m_winTrigger) && m_input.isPressed(sf::Keyboard::Scancode::Enter))
	{
		m_won = true;
		m_gameState.setCurrentState( State::CREDITS);
	}
	
}



void enemyLevel::updateCameraAndBackground()
{
	auto view = m_window.getView();
	auto player_pos = m_player.getPosition() + m_player.getSize() * 0.5f;

	float halfViewWidth = VIEW_SIZE.x / 2.0f;
	float halfViewHeight = VIEW_SIZE.y / 2.0f;

	player_pos.x = std::clamp(player_pos.x, halfViewWidth, WORLD_SIZE.x - halfViewWidth);
	player_pos.y = std::clamp(player_pos.y, halfViewHeight, WORLD_SIZE.y - halfViewHeight);

	view.setCenter(player_pos);
	m_window.setView(view);

	m_bgtilemap.setPosition({ player_pos.x - halfViewWidth, 72 });
}




void enemyLevel::render()
{
	beginDraw();

	m_screenLoader.render(m_window);

	//m_window.draw(m_player.m_aggroRange);
	m_window.draw(m_player);


	for (auto f : m_player.m_projectiles)
	{
		if (f->isAlive()) m_window.draw(*f);
	}

	m_ui.drawUI(m_window, m_player);


	endDraw();
}


void enemyLevel::reset()
{
	m_player.reset();
	m_screenLoader.reset();
	m_won = false;
}