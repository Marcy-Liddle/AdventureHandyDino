#include "enemyLevel.h"
#include <iostream>

enemyLevel::enemyLevel(sf::RenderWindow& window, Input& input, GameState& gameState, AudioManager& audio) 
	: BaseLevel(window, input, gameState, audio)
{
	// setup player 
	m_player.setInput(&m_input);
	m_player.setEdges(0, WORLD_SIZE.x);
	m_player.setPosition({ 100, 100 });
	m_player.setAudio(&m_audio);


	m_screenLoader.create("screen1");

	m_test.setPosition({300,300});
	m_test.setSize({ 72,72 });
	m_test.setCollisionBox({ {0,0}, {72,72} });
	m_test.setFillColor(sf::Color::Green);
	
	//m_enemy.setPosition({  });
}

void enemyLevel::handleInput(float dt) 
{

	m_player.handleInput(dt);
}


void enemyLevel::update(float dt)
{
	m_player.update(dt);
	m_enemy.update(dt);

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

		else if (t.isCollider() && Collision::checkBoundingBox(m_enemy, t))
		{
			m_enemy.collisionResponse(t);
		}

		for (int i = 0; i < m_player.m_projectiles.size(); i++)
		{
			if (t.isCollider() && Collision::checkBoundingBox(t, *m_player.m_projectiles[i]))
			{
				m_player.m_projectiles[i]->collisionResponse();
			}
			if (m_test.isAlive() && Collision::checkBoundingBox(m_test, *m_player.m_projectiles[i]))
			{
				m_test.collisionResponse(*m_player.m_projectiles[i], m_player.getFireLevel());
			}
		}
	}



	if (Collision::checkBoundingCircle(m_player.m_aggroRange, m_enemy))
	{
		if (m_enemy.getPlayerPointer() == nullptr)
			m_enemy.setPlayerPointer(&m_player);

		if (!m_player.getInvincible() && Collision::checkBoundingBox(m_player, m_enemy))
		{
			m_player.healAndDeal(-5.f );
			//std::cout << m_player.getCurrentHealth() << "\n";
			m_player.collisionResponse(m_enemy);
			m_player.setInvincible(true);
			m_player.knockBack({ 10,10 });
		 }

		if (m_player.isAttacking() && Collision::checkBoundingBox(m_player.m_meleeHitBox, m_enemy))
			{
				m_enemy.healAndDeal(-5.f * m_player.getKickLevel());
			}
		
			
	}
	else 
	{
		m_enemy.clearPlayerPointer();
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

	//m_bgtilemap.render(m_window);
	//m_tilemap.render(m_window);
	//m_window.draw(m_player.m_aggroRange);
	m_window.draw(m_player);

	if (m_enemy.isAlive())
		m_window.draw(m_enemy);

	for (auto f : m_player.m_projectiles)
	{
		if (f->isAlive()) m_window.draw(*f);
	}
	if (m_test.isAlive())
		m_window.draw(m_test);

	endDraw();
}
