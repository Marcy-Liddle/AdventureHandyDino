#pragma once
#include "Framework/TileMap.h"
#include <fstream>
#include <sstream>

class ScreenLoader
{
public :
	void temp();

	std::vector<int> loadScreen(std::string screen, int blank);
	

	void render(sf::RenderWindow& window);

	std::vector<GameObject>* getLevel() { return m_tilemap.getLevel() ; };

private:
	TileMap m_tilemap;
	TileMap m_bgtilemap;


};

