/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Game.h
 * Author: dan
 *
 * Created on 13 de febrero de 2018, 15:36
 */

#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>
#include "Player.h"
#include "Enemy.h"

class Game {
private:
    sf::RenderWindow window;
    sf::View view;
    
    bool* keys;
    float* dtAsSeconds;
    Player* player;
    Enemy* IA;
    
    AssetManager manager;
    sf::Clock clock;
    sf::Time deltaTime;
    sf::Time elapsedTime;
    
    sf::RectangleShape* hitbox;
    sf::Color Dark;
    sf::Color Light;
    
public:
    Game();
    Game(const Game& orig);
    virtual ~Game();
    
    void go();    
    
private:
    void handleEvents();
    void update();
    void render();
    
};

#endif /* GAME_H */

