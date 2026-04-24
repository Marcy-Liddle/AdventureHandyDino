#include "ScreenLoader.h"


ScreenLoader::ScreenLoader()
{

	if (!m_tileSpritesheet.loadFromFile("gfx/tilemap.png"))
		Utils::printMsg("No bg texture. sad", MessageType::ERROR);


	if (!m_bgSpritesheet.loadFromFile("gfx/tilemap-backgrounds.png"))
		Utils::printMsg("No bg texture. sad", MessageType::ERROR);

	if (!m_slimeSpritesheet.loadFromFile("gfx/characters/enemies/slime/slime_idle.png"))
		Utils::printMsg("No slime texture. sad", MessageType::ERROR);

	if (!m_vultureSpritesheet.loadFromFile("gfx/characters/enemies/vulture/spritesheets/vulture.png"))
		Utils::printMsg("No vulture texture. sad", MessageType::ERROR);
}


ScreenLoader::~ScreenLoader()
{

}

void ScreenLoader::create(std::string screen)
{
	

	sf::Vector2u mapDimensions{ 40, 11 };

	m_tileSet = createTileset(20, 9, 18,1,4, false);
	
	m_tilemap.setTexture(m_tileSpritesheet);
	m_tilemap.setTileSet(m_tileSet);
	m_tilemap.setTileMap(
		loadScreen("screen1") ,mapDimensions);
	m_tilemap.setPosition({ 0, 0 });
	m_tilemap.buildLevel();


	mapDimensions = { 14,5 };

	m_bgTileSet = createTileset(8, 3, 24, 1, 9, true);
	//loadScreen("screen1bg", b);
	m_bgtilemap.setTexture(m_bgSpritesheet);
	m_bgtilemap.setTileSet(m_bgTileSet);
	m_bgtilemap.setTileMap(loadScreen("screen1bg"), mapDimensions);
	m_bgtilemap.setPosition({ 0, -200 });
	m_bgtilemap.buildLevel();


	loadEntities(screen, "Enemy");

	loadEntities(screen, "Consumable");

	loadEntities(screen, "CheckPoint");

	loadEntities(screen, "Obstacle");

	
}

std::vector<GameObject>  ScreenLoader::createTileset( int num_columns, int num_rows, int size, int spacing, int scale, bool isBackground)
{
	GameObject tile;
	std::vector<GameObject> tileSet;


	// Set GameObject size (Scaling up 4x for visibility)
	// 4 * 18 = 3 * 24 = 72 (dino size is 24).
	tile.setSize(sf::Vector2f(size * scale, size * scale));
	tile.setCollisionBox({ { 0,0 }, tile.getSize() });

	for (int i = 0; i < num_columns * num_rows; i++)
	{
		int row = i / num_columns;
		int col = i % num_columns;
		tile.setTextureRect({
			{(size + spacing) * col, (size + spacing) * row},
			{size, size} });
		if (!isBackground && (col <= 4 || col >= 12))
			tile.setCollider(true);
		else tile.setCollider(false);
		tileSet.push_back(tile);

	}
	if (!isBackground)
	{
		tile.setTextureRect({ {0, 0}, {-24, -24} }); // Empty rect for blank
		m_blank = tileSet.size();
		tile.setCollider(false);
		tileSet.push_back(tile);
	}

	return tileSet;

}

std::vector<int> ScreenLoader::loadScreen(std::string screen)
{
	std::vector<int> loadedTileMap;
	std::ifstream levelFile("data/screens.csv");

	std::string line, tile;

	if (!levelFile.is_open())
	{
		std::cerr << "cant't read level file";
		return {0};
	}

	bool levelFound;

	while (std::getline(levelFile, line))
	{
		levelFound = false;
		std::stringstream lineStream(line);

		int i = 0;
		while (std::getline(lineStream, tile, ','))
		{
			if (tile == screen || levelFound == true)
			{
				
				levelFound = true;
				if (i > 0)
				{
					if (tile == "b")
						loadedTileMap.push_back(m_blank);
					else
						loadedTileMap.push_back(std::stoi(tile));
				}
				i += 1;
				
			}
		}
	}


	levelFile.close();

	if (loadedTileMap.empty()) {
		std::cerr << "Could not find " << screen << " in level file." << std::endl;
	
	}
	return loadedTileMap;

}


void ScreenLoader::loadEntities(std::string screen, std::string entityType)
{
	std::ifstream levelFile("data/screens.csv");

	std::string line, tile;

	if (!levelFile.is_open())
	{
		std::cerr << "cant't read level file";
		return;
	}

	bool levelFound;

	while (std::getline(levelFile, line))
	{
		levelFound = false;
		std::stringstream lineStream(line);

		int i = 0;
		std::vector<std::string> entityData;

		while (std::getline(lineStream, tile, ','))
		{

			if (tile == screen + entityType || levelFound == true)
			{
				levelFound = true;
				entityData.push_back(tile);
			}
		}


		if (!entityData.empty())
		{

			if (entityType == "Enemy" && entityData[3] == "slime")
			{
				enemy1* newEnemy = new enemy1;
				newEnemy->setSpawnPoint({ std::stof(entityData[1]) , std::stof(entityData[2]) });
				newEnemy->respawn();

				newEnemy->setTexture(&m_slimeSpritesheet);

				for (int i = 0; i < 8; i++)
					newEnemy->m_idle.addFrame({ { i * 24, 0 }, { 24, 24} });

				newEnemy->m_idle.setFrameSpeed(1.f / 4.f);

				m_enemies.push_back(newEnemy);
			}

			else if (entityType == "CheckPoint")
			{
				checkPoint* newCheckPoint = new checkPoint({ std::stof(entityData[1]) , std::stof(entityData[2]) });
				newCheckPoint->setFillColor(sf::Color::Yellow);
				newCheckPoint->setSize({ 72,72 });
				newCheckPoint->setCollisionBox({ {0,0 }, { 72,72 } });
				m_checkPoints.push_back(newCheckPoint);
			}
			else if (entityType == "Consumable")
			{
				if (entityData[1] == "health")
				{
					consumable* newHealthPickup = new consumable('h', entityData[2]);
					newHealthPickup->setPosition({ std::stof(entityData[3]) , std::stof(entityData[4]) });
					newHealthPickup->setFillColor(sf::Color::Red);
					newHealthPickup->setSize({ 72,72 });

					m_consumables.push_back(newHealthPickup);
				}
				else if (entityData[1] == "power")
				{
					consumable* newPowerUp = new consumable('p', entityData[2]);
					newPowerUp->setPosition({ std::stof(entityData[3]) , std::stof(entityData[4]) });
					newPowerUp->setFillColor(sf::Color(211, 3, 252));
					newPowerUp->setSize({ 72,72 });
					newPowerUp->setCollisionBox({ {0,0} ,{72,72} });

					m_consumables.push_back(newPowerUp);
				}

			}
			else if (entityType == "Obstacle")
			{
				if (entityData[1] == "destructable")
				{
					//assume obstacle = destructable for now
					destructable* newDistructable = new destructable;
					newDistructable->setStrenght(std::stoi(entityData[2]));
					newDistructable->setPosition({ std::stof(entityData[3]), std::stof(entityData[4]) });
					newDistructable->setFillColor(sf::Color::Green);
					newDistructable->setSize({ 72,72 });

					m_destructables.push_back(newDistructable);
				}
				else if (entityData[1] == "barrier")
				{
					obstacle* newObstacle = new obstacle('b', entityData[1]);
					newObstacle->setPosition({ std::stof(entityData[2]) , std::stof(entityData[3]) });
					newObstacle->setSize({ 72 * std::stof(entityData[4]),  72 * std::stof(entityData[5]) });
					newObstacle->setCollisionBox({ {0,0}, newObstacle->getSize() });
					newObstacle->setFillColor(sf::Color(255, 0, 140));

					m_obstacles.push_back(newObstacle);
				}



			}



		}
		

	}

	levelFile.close();


}

void ScreenLoader::render(sf::RenderWindow& window)
{
	m_bgtilemap.render(window);
	m_tilemap.render(window);


	for (auto d : m_destructables)
	{
		if (d->isAlive()) window.draw(*d);
	}
	
	for (auto c : m_checkPoints)
	{
		if (c->isAlive()) window.draw(*c);
	}


	for (auto c : m_consumables)
	{
		if (c->isAlive()) window.draw(*c);
	}

	for (auto e : m_enemies)
	{
		if (e->isAlive()) window.draw(*e);
	}

	for (auto o : m_obstacles)
	{
		if (o->isAlive()) window.draw(*o);
	}

}