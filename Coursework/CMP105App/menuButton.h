#pragma once
#include "Framework/GameObject.h"
#include "Framework/Collision.h"
#include "Framework/Input.h"
#include "Framework/AudioManager.h"

#include <SFML/Graphics.hpp>
#include <string>

//gameObject-based button class for use in the main & pause menu 
class menuButton :public GameObject
{
public:
    menuButton(sf::Vector2f pos, sf::Vector2f size, sf::String lbl, float labelOffset, char ID, AudioManager* audio);
    ~menuButton();

    void update(float dt) override;
    void handleInput(float dt);


    enum class buttonState { ACTIVE, HOVER, SELECTED };
    
    buttonState m_state = buttonState::ACTIVE;
    GameObject m_buttonObject;

  
    sf::Text m_label;
    sf::Font m_font;

    char m_buttonID;

    sf::Color m_activeColour{ sf::Color::Blue };
    sf::Color m_hoverColour{ sf::Color::Cyan };
    sf::Color m_selectedColour{ sf::Color::Green };
    sf::Color m_disabledColour{ sf::Color(100,100,100) };

    AudioManager* m_audio;
};

