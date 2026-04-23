#pragma once
#include "Framework/GameObject.h"
class obstacle :
    public GameObject
{
    obstacle(char id, std::string effect)
    {
        m_id = id;
        m_effect = effect;

    };

    


    char m_id;
    std::string m_effect;
};

