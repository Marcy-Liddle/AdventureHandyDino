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

	GameObject tile;
	std::vector<GameObject> tileSet;

	int num_columns = 20;
	int num_rows = 9;
	int tile_size = 18;      // Visual size of the tile
	int sheet_spacing = 1;   // Gap between tiles

	// Set GameObject size (Scaling up 4x for visibility)
	// 4 * 18 = 3 * 24 = 72 (dino size is 24).
	tile.setSize(sf::Vector2f(tile_size * 4, tile_size * 4));
	tile.setCollisionBox({ { 0,0 }, tile.getSize() });

	for (int i = 0; i < num_columns * num_rows; i++)
	{
		int row = i / num_columns;
		int col = i % num_columns;
		tile.setTextureRect({
			{(tile_size + sheet_spacing) * col, (tile_size + sheet_spacing) * row},
			{tile_size, tile_size} });
		if (col <= 4 || col >= 12) tile.setCollider(true);
		else tile.setCollider(false);
		tileSet.push_back(tile);

	}

	// Add Blank
	tile.setTextureRect({ {0, 0}, {-24, -24} }); // Empty rect for blank
	int b = tileSet.size();
	tile.setCollider(false);
	tileSet.push_back(tile);

	sf::Vector2u mapDimensions{ 40, 8 };
	std::vector<int> tileMap = {
		b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b,   b ,  b,   b,   b,   b,   b,   b,   b,   b,   b,   b,   b,   b,   b  , 
		b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b,   b,   b,   b,   b,   b,   b,   b,   b,   b,   b,   b,   b,   b  , b  , 
		b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b,   b,   b,   b,   b,   b,   b,   b,   b,   b,   b  , b  , b  , b  , b  , 
		b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b,   b,   b,   b,   b,   b,   b,   b,   b,   b ,  b  , b  , b  , b  , b  , 
		b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b,   b,   b,   b,   b,   b,   b,   b,   b,   b,   b  , b  , b  , b  , b  , 
		b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b	,  b  , b,	 b,	  b,   b,   b,   b,   b,   b,   b,   b,   b  , b  , b  , b  , b  , 
		21 , 22 , 22 , 22 , 22 , 22 , 22 , 22 , 22 , 22 , 22 , 22 , 25 , 122, 122, 122, 122, 24 , 22 , 22 , 22 , 23 , 21 , 22 , 22 , 22 , 22 , 22 , 22 , 22 , 23 ,
		141, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 143, 141, 142, 142, 142, 142, 142, 142, 142, 143
	};


	m_tilemap.loadTexture("gfx/tilemap.png");
	m_tilemap.setTileSet(tileSet);
	m_tilemap.setTileMap(tileMap, mapDimensions);
	m_tilemap.setPosition({ 0, 0 });
	m_tilemap.buildLevel();

	tileSet.clear();

	// setup background
	tile_size = 24;
	num_columns = 8;
	num_rows = 3;
	// 24 * 9 = 216, a multiple of 72, the LCM of the player and tile size.
	tile.setSize(sf::Vector2f(tile_size * 9, tile_size * 9));

	for (int i = 0; i < num_columns * num_rows; i++)
	{
		int row = i / num_columns;
		int col = i % num_columns;

		tile.setTextureRect({
			{(tile_size + sheet_spacing) * col, (tile_size + sheet_spacing) * row},
			{tile_size, tile_size} });
		tile.setCollider(false);		// don't collide with background
		tileSet.push_back(tile);
	}

	mapDimensions = { 14,5 };
	tileMap = {
		2,2,2,2,2,2,2,2,2,2,2,2,2,2,
		2,2,2,2,2,2,2,2,2,2,2,2,2,2,
		10,10,10,10,10,10,10,10,10,10,10,10,10,10,
		18,18,18,18,18,18,18,18,18,18,18,18,18,18,
		18,18,18,18,18,18,18,18,18,18,18,18,18,18
	};

	m_bgtilemap.loadTexture("gfx/tilemap-backgrounds.png");
	m_bgtilemap.setTileSet(tileSet);
	m_bgtilemap.setTileMap(tileMap, mapDimensions);
	m_bgtilemap.setPosition({ 0, -200 });
	m_bgtilemap.buildLevel();



	m_enemy.setPosition({ 1082.97,300.5 });
}

void enemyLevel::handleInput(float dt) 
{

	m_player.handleInput(dt);
}


void enemyLevel::update(float dt)
{

	m_player.update(dt);
	m_enemy.update(dt);

	// handle collisions
	std::vector<GameObject>& level = *m_tilemap.getLevel();
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
	}

	if (Collision::checkBoundingCircle(m_player.m_aggroRange, m_enemy))
	{
		if (m_enemy.getPlayerPointer() == nullptr)
			m_enemy.setPlayerPointer(&m_player);

		if (Collision::checkBoundingBox(m_player, m_enemy))
		{
			m_player.setCurrentHealth(-5.f );
			std::cout << m_player.getCurrentHealth() << "\n";
			m_player.collisionResponse(m_enemy);
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

	m_bgtilemap.render(m_window);
	m_tilemap.render(m_window);
	//m_window.draw(m_player.m_aggroRange);
	m_window.draw(m_player);
	m_window.draw(m_enemy);
	endDraw();
}
