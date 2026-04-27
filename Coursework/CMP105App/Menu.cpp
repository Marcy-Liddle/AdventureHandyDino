#include "Menu.h"

Menu::Menu(sf::RenderWindow& hwnd, Input& in, GameState& gs, AudioManager& aud, std::string menuType, sf::Texture& texture, std::string song) :
	Scene(hwnd, in, gs, aud), m_title(m_font)
{
	m_audio.addMusic(menuType + "MenuTheme", song);
	m_audio.getMusic(menuType + "MenuTheme")->setLooping(true);


	m_textures = texture;
	m_bookGraphic.setTexture(&m_textures);
	m_bookGraphic.setTextureRect({ {300,415},{226,162} });
	m_bookGraphic.setSize({ 1130, 810});
	

	sf::Vector2u screenSize = m_window.getSize();
	sf::Vector2i screen = m_window.getPosition();

	float radius = screenSize.x / 2.f;
	sf::Vector2f centre = { screen.x + radius, screen.y + radius };
	sf::Vector2f diff = { screen.x - m_bookGraphic.getSize().x , screen.y - m_bookGraphic.getSize().y };
	m_bookGraphic.setPosition({ 10 ,10});
	loadMenu(menuType, screenSize);
}


Menu::Menu(sf::RenderWindow& hwnd, Input& in, GameState& gs, AudioManager& aud, std::string menuType, sf::Texture& texture)  :
	Scene(hwnd, in, gs, aud), m_title(m_font)
{
	m_menuType = menuType;
	m_textures = texture;
	m_bookGraphic.setTexture(&m_textures);
	m_bookGraphic.setTextureRect({ {300,415},{226,162} });
	m_bookGraphic.setSize({ 1130, 810 });
	m_bookGraphic.setPosition({ 5,5 });


	sf::Vector2u screenSize = m_window.getSize();
	sf::Vector2i screen = m_window.getPosition();

	float radius = screenSize.x / 2.f;
	sf::Vector2f centre = { screen.x + radius, screen.y + radius };
	sf::Vector2f diff = { screen.x - m_bookGraphic.getSize().x , screen.y - m_bookGraphic.getSize().y };
	m_bookGraphic.setPosition({ 10,10 });

	loadMenu(menuType, screenSize);
}


void Menu::onBegin()
{
	if (m_menuType == "Main")
		m_audio.playMusicbyName("title");
	else if (m_menuType == "Credits")
		m_audio.playMusicbyName("victory");
}

void Menu::onEnd()
{
	m_audio.stopAllMusic();
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
				m_gameState.setCurrentState(State::LEVEL);
				//m_audio.getMusic("GameTheme")->play();
				break;
			case 'M':
				m_gameState.setCurrentState(State::MENU);
				//m_audio.playMusicbyName("MainMenuTheme");
				break;
			case 'R':
				m_gameState.setCurrentState(State::LEVEL);
				break;
			case 'C':
				m_gameState.setCurrentState(State::CREDITS);
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

	m_window.draw(m_bookGraphic);

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
		m_title.setString("Adventure Of A Handy Dino");
		m_title.setPosition({ screenSize.x * .5f - 550.f, screenSize.y * .5f - 125.f });
		m_title.setScale({ 1.5f, 1.5f });

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
	else if (menuName == "Credits")
	{

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
			m_buttonList[i]->setTexture(&m_textures);

			i += 1;

		}

	}

}