#include "ScreenLoader.h"

void ScreenLoader::create()
{
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



	m_tilemap.loadTexture("gfx/tilemap.png");
	m_tilemap.setTileSet(tileSet);
	m_tilemap.setTileMap(
		loadScreen("screen1", b) ,mapDimensions);
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

	//loadScreen("screen1bg", b);
	m_bgtilemap.loadTexture("gfx/tilemap-backgrounds.png");
	m_bgtilemap.setTileSet(tileSet);
	m_bgtilemap.setTileMap(loadScreen("screen1bg", b), mapDimensions);
	m_bgtilemap.setPosition({ 0, -200 });
	m_bgtilemap.buildLevel();

}

void loadSpriteSheet()
{
	//"C:\Users\Marcy\105_solo_project\Coursework\CMP105App\gfx\environment\Layers\back.png"
	//"C:\Users\Marcy\105_solo_project\Coursework\CMP105App\gfx\environment\Layers\middle.png"
	//


}


std::vector<int> ScreenLoader::loadScreen(std::string screen, int blank)
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
						loadedTileMap.push_back(blank);
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

void ScreenLoader::render(sf::RenderWindow& window)
{
	m_bgtilemap.render(window);
	m_tilemap.render(window);

}