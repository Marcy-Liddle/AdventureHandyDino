#include "enemyLevel.h"
#include <iostream>

enemyLevel::enemyLevel(sf::RenderWindow& window, Input& input, GameState& gameState, AudioManager& audio) 
	: BaseLevel(window, input, gameState, audio)
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

	m_player.handleInput(dt);
}


void enemyLevel::update(float dt)
{
	m_player.update(dt);
	

	for (auto& t : m_screenLoader.m_enemies)
	{
		t->update(dt);
	}


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
				e->collisionResponse(t);
			}
		}
		

		for (int i = 0; i < m_player.m_projectiles.size(); i++)
		{
			if (t.isCollider() && Collision::checkBoundingBox(t, *m_player.m_projectiles[i]))
			{
				m_player.m_projectiles[i]->collisionResponse();
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
				}

			}

			if (m_player.isAttacking() && Collision::checkBoundingBox(m_player.m_meleeHitBox, *e))
			{
				e->healAndDeal(-5.f * m_player.getKickLevel());
			}

		}
		else
		{
			e->clearPlayerPointer();
		}

		for (auto d : m_screenLoader.m_destructables)
		{
		
		}

		for (auto c : m_screenLoader.m_checkPoints)
		{
		
		}


		for (auto c : m_screenLoader.m_consumables)
		{
			if (c->isAlive() && Collision::checkBoundingBox(m_player, *c))
			{
				c->consume(&m_player);
			}
		}

	}



	
	updateCameraAndBackground();
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

	m_bgtilemap.setPosition({ player_pos.x - halfViewWidth, 0 });
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


	endDraw();
}
