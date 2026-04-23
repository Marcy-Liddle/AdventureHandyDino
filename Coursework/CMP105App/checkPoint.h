#pragma once
#include "Player.h"
class checkPoint : public GameObject
{
public: 
	checkPoint(sf::Vector2f pos) {setPosition(pos);}
	~checkPoint() {};

	void setSpawn(Player* player) { player->setRespawn(getPosition()); };

};

