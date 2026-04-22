#pragma once
#include "Framework/GameObject.h"
#include "Framework/Animation.h"
#include "Player.h"

class consumable1 : public GameObject
{
	protected:

	//gives the player something ie ability / health increase
	virtual void consume(Player* player) = 0;
	void collisionResponse(GameObject& collider) { setAlive(false); };
	std::string m_gift;

};

class healthPickup : public consumable1
{
public:
	void consume(Player* player) { player->healAndDeal(std::stof(m_gift)); };

};


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
			player->healAndDeal(std::stof(m_gift));
			break;
		default: break;
		}

		collisionResponse();
	};

	void collisionResponse() { setAlive(false); };

	std::string m_gift;
	char m_id;

};