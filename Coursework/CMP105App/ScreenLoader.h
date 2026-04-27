#pragma once
#include "Framework/TileMap.h"
#include "Utils.h"
#include <fstream>
#include <sstream>

#include "destructable.h"
#include "checkPoint.h"
#include "consumable.h"
#include "enemy1.h"
#include "obstacle.h"
#include "boss.h"

class ScreenLoader
{
public:

	ScreenLoader();
	~ScreenLoader();
	void create(std::string screen);

	std::vector<int> loadScreen(std::string screen);
	std::vector<GameObject>  createTileset(int num_columns, int num_rows, int size, int spacing, int scale, bool isBackground);

	void loadEntities(std::string screen, std::string entityType);

	void render(sf::RenderWindow& window);

	std::vector<GameObject>* getLevel() { return m_tilemap.getLevel(); };


	std::vector<checkPoint*> m_checkPoints;
	std::vector<destructable*> m_destructables;
	std::vector<consumable*> m_consumables;
	std::vector<enemy1*> m_enemies;
	std::vector<obstacle*> m_obstacles;

	boss* m_boss;
	GameObject m_bossTrigger;

private:

	std::vector<GameObject> m_tileSet;
	std::vector<GameObject> m_bgTileSet;

	std::map <int, sf::IntRect> m_tileTable;
	std::map <int, sf::IntRect> m_bgTileTable;


	TileMap m_tilemap;
	TileMap m_bgtilemap;

	int m_blank;

	sf::Texture m_bgSpritesheet;
	sf::Texture m_tileSpritesheet;
	sf::Texture m_slimeSpritesheet;
	sf::Texture m_vultureSpritesheet;

};