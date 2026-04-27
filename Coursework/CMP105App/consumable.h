#pragma once
#include "Framework/GameObject.h"
#include "Framework/Animation.h"
#include "Player.h"

class consumable : public GameObject
{
public:

	consumable(char id, std::string gift)
	{
		m_id = id;
		m_gift = gift;
	};

	//gives the player something ie ability / health increase
	void consume(Player* player)
	{
		switch (m_id)
		{
			case 'h':
				Utils::printMsg("Player health = " + std::to_string(player->getCurrentHealth()) , MessageType::SUCCESS);
				player->healAndDeal(std::stof(m_gift));
				Utils::printMsg("Healed Player for " + m_gift + ", player health = " + std::to_string(player->getCurrentHealth()) , MessageType::SUCCESS);
				break;
			case 'p':
				player->addAbility(m_gift);
				break;
			default: break;
		}

		collisionResponse();
	};

	void collisionResponse() { setAlive(false); };

	std::string m_gift;
	char m_id;
	
};