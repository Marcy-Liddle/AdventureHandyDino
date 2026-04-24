#pragma once
#include "Player.h"
class obstacle :
    public GameObject
{

public:

    obstacle(char id, std::string effect)
    {
        m_id = id;
        m_effect = effect;

    };



    void obstacleInteract(Player* player)
    {
        switch (m_id)
        {
        case 't':
            if (!player->getInvincible())
            {

                Utils::printMsg("Player health = " + std::to_string(player->getCurrentHealth()), MessageType::SUCCESS);

                player->healAndDeal(-std::stof(m_effect));
                player->setInvincible(true);
                Utils::printMsg("Hurt Player for " + m_effect + ", player health = " + std::to_string(player->getCurrentHealth()), MessageType::SUCCESS);

            }
            break;

        case 'b':
                if (!player->isDashing())
                    player->collisionResponse(*this);
            break;


        default:
            break;
        }
    }
  

private:
    char m_id;
    std::string m_effect;
};

