#pragma once
#include "Framework/BaseLevel.h"
class Scene :
    public BaseLevel
{
public:
    Scene(sf::RenderWindow& hwnd, Input& in, GameState& gs, AudioManager& aud) : BaseLevel(hwnd, in, gs, aud) {};

    // Paired with state transitions in Main.cpp. Called once on open
    virtual void onBegin() = 0;

    // Paired with strate transitions in Main.cpp. Called once on close
    virtual void onEnd() = 0;
};

