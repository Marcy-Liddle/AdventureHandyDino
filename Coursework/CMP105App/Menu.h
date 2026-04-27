#pragma once
#include "Scene.h"
#include "Framework/Collision.h"
#include "menuButton.h"
#include <fStream>

class Menu :
    public Scene
{
public:
    Menu(sf::RenderWindow& window, Input& input, GameState& gameState, AudioManager& audio, std::string menuType, sf::Texture& texture);
    Menu(sf::RenderWindow& window, Input& input, GameState& gameState, AudioManager& audio, std::string menuType, sf::Texture& texture, std::string song);

    void handleInput(float dt) override;
    void update(float dt) override;
    void render() override;

    void onBegin() override;

    void onEnd() override;


    void setPreviousState(std::string screen) { m_previousScreen = screen; }
    std::string getPreviousState() { return m_previousScreen; }

    void loadMenu(std::string filename, sf::Vector2u screenSize);

private:

    sf::Texture m_textures;
    std::vector<menuButton*> m_buttonList;

    sf::RectangleShape m_bookGraphic;
    std::string m_previousScreen;

    sf::Text m_title;
    sf::Font m_font;

    std::string m_menuType;
};

