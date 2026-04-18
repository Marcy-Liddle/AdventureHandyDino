#include "menuButton.h"
#include <iostream>

menuButton::menuButton(sf::Vector2f size, sf::Vector2f pos, sf::String lbl, float labelOffset, char ID, AudioManager* audio) : m_label(m_font)
{
	m_buttonID = ID;
	setPosition(pos);
	setSize(size);


	if (!m_font.openFromFile("gfx/fonts/PermanentMarker-Regular.ttf")) std::cerr << "no font";
	m_label.setFont(m_font);
	m_label.setString(lbl);
	m_label.setPosition({ pos.x + labelOffset ,pos.y });

	setFillColor(m_disabledColour);

	m_buttonObject.setCollisionBox(pos.x, pos.y, size.x, size.y);

	m_audio = audio;
}


menuButton::~menuButton()
{


}


void menuButton::handleInput(float dt)
{

	sf::Vector2i mousePos{ m_input->getMouseX(), m_input->getMouseY() };

	bool isHovering = Collision::checkBoundingBox(m_buttonObject, mousePos);

	if (isHovering)
	{
		m_state = buttonState::HOVER;

		if (m_input->isLeftMousePressed())
		{
			if (m_state == buttonState::ACTIVE || m_state == buttonState::HOVER)
			{
				m_state = buttonState::SELECTED;
				int randSound = (rand() % 3) + 1;
				std::cout << randSound;
				std::string clickSound = "Button" + std::to_string(randSound);
				m_audio->playSoundbyName(clickSound);

			}
			else
			{
				m_state = buttonState::ACTIVE;
			}

		}
	}
	else
	{
		if (m_state == buttonState::HOVER)
			m_state = buttonState::ACTIVE;
	}
}


void menuButton::update(float dt) 
{
	switch (m_state)
	{
	case buttonState::ACTIVE:
		setFillColor(m_activeColour);
		break;

	case buttonState::HOVER:
		setFillColor(m_hoverColour);
		break;

	case buttonState::SELECTED:
		setFillColor(m_selectedColour);
		break;
	}
}

