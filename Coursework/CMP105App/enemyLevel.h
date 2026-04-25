#pragma once
#include "Framework/BaseLevel.h"
#include "Framework/TileMap.h"
#include "Player.h"
#include "Framework/Collision.h"
#include "Scene.h"
#include "enemy1.h"
#include "ScreenLoader.h"
#include "userInterface.h"

class enemyLevel :
    public BaseLevel
{
public:
    enemyLevel(sf::RenderWindow& window, Input& input, GameState& gameState, AudioManager& audio);

    void handleInput(float dt) override;
    void update(float dt) override;
    void render() override;

    void handleCollision();

    void updateCameraAndBackground();

private:

    ScreenLoader m_screenLoader;
    TileMap m_tilemap;
    TileMap m_bgtilemap;
    Player m_player;


    userInterface m_ui;

    const sf::Vector2i WORLD_SIZE = { 2880, 648 };
    const sf::Vector2i VIEW_SIZE = { 1296, 648 };

};

