#include "Menu.h"

Menu::Menu(sf::RenderWindow& hwnd, Input& in, GameState& gs, AudioManager& aud, std::string menuType, std::string song) :
	BaseLevel(hwnd, in, gs, aud), m_title(m_font)
{
	m_audio.addMusic(menuType + "MenuTheme", song);
	m_audio.getMusic(menuType + "MenuTheme")->setLooping(true);


	sf::Vector2u screenSize = m_window.getSize();

	loadMenu(menuType, screenSize);
}


Menu::Menu(sf::RenderWindow& hwnd, Input& in, GameState& gs, AudioManager& aud, std::string menuType) :
	BaseLevel(hwnd, in, gs, aud), m_title(m_font)
{


	sf::Vector2u screenSize = m_window.getSize();

	loadMenu(menuType, screenSize);
}


void Menu::update(float dt)
{
	for (auto b : m_buttonList)
	{
		b->update(dt);

		if (b->m_state == menuButton::buttonState::SELECTED)
		{
			b->m_state = menuButton::buttonState::ACTIVE;
			m_audio.stopAllMusic();
			switch (b->m_buttonID)
			{
			case 'L':
				//m_gameState.setCurrentState(State::LEVEL);
				//m_audio.getMusic("GameTheme")->play();
				break;
			case 'M':
				m_gameState.setCurrentState(State::MENU);
				//m_audio.playMusicbyName("MainMenuTheme");
				break;
			case 'R':
				break;
			case 'C':
				m_gameState.setCurrentState(State::CREDITS);

				m_audio.playMusicbyName("BuilderTheme");
				
				break;
			case 'Q':
				m_window.close();
				break;

			}
		}
	}

}

void Menu::handleInput(float dt)
{

	for (auto b : m_buttonList)
	{
		b->handleInput(dt);
	}

}


void Menu::render()
{
	beginDraw();

	m_window.setView(m_window.getDefaultView());

	m_window.draw(m_title);
	for (auto b : m_buttonList)
	{
		m_window.draw(*b);
		m_window.draw(b->m_label);
	}

	endDraw();
}


void Menu::loadMenu(std::string menuName, sf::Vector2u screenSize)
{

	if (!m_font.openFromFile("font/antiquity-print.ttf")) std::cerr << "no font";
	m_title.setFont(m_font);
	
	if (menuName == "Main")
	{
		m_title.setString("Shepherd of the Cryptid");
		m_title.setPosition({ screenSize.x * .5f - 350.f, screenSize.y * .5f - 125.f });
		m_title.setScale({ 2.f, 2.f });

	}
	else if (menuName == "Pause")
	{
		m_title.setString("Paused");
		m_title.setPosition({ screenSize.x * .5f - 70.f, screenSize.y * .5f - 125.f });
		m_title.setScale({ 1.5f, 1.5f });
	}
	else if (menuName == "Win")
	{
		m_title.setString("You Did It!!!");
		m_title.setPosition({ screenSize.x * .5f - 70.f, screenSize.y * .5f - 125.f });
		m_title.setScale({ 2.f, 2.f });
	}
	else if (menuName == "Death")
	{
		m_title.setString("Game Over...");
		m_title.setPosition({ screenSize.x * .5f - 70.f, screenSize.y * .5f - 125.f });
		m_title.setScale({ 1.5f, 1.5f });
	}


	std::ifstream menuFile("data/menu.txt");

	if (!menuFile.is_open())
	{
		std::cerr << "menu layout file cannot be located." << std::endl;
		return;
	}


	float sizeX, sizeY, posOffX, posOffY, labelOff;

	std::string type, label;

	char ID;
	int i = 0;

	while (menuFile >> type)
	{

		if (type == menuName)
		{

			menuFile >> sizeX >> sizeY >> posOffX >> posOffY >> label >> labelOff >> ID;

			m_buttonList.push_back(new menuButton({ sizeX,sizeY }, { screenSize.x * 0.5f - posOffX , screenSize.y * 0.5f + posOffY }, label, labelOff, ID, &m_audio));
			m_buttonList[i]->setInput(&m_input);

			i += 1;

		}

	}

}