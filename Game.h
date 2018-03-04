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
#include <math.h>
#include "SAT.h"

class Game {
private:
    int N_IA;
    int N_PLAYERS;
    sf::RenderWindow window;
    sf::View view;
    sf::Sprite Cool_Map;
    
    bool* keys;
    float* dtAsSeconds;
    
    Enemy* IAs[4];
    Player* player;
    
    struct State{
        sf::Vector2f position;
        float Speed;
        float rotation;
    };
    State previous[5];
    State actual[5];
    
    SAT Sat;
    SAT::MTV Sat_result;;
    
    AssetManager manager;
    sf::Clock masterClock;
    sf::Time deltaTime;
    sf::Time elapsedTime;
    
    //sf::RectangleShape* hitbox;
    sf::Color Dark;
    sf::Color Light;
    
    const float PI = 3.14159265;
    
    struct item{
        sf::RectangleShape figure;
        sf::Vector2f* vertex;
        int sx;
        int sy;
        float newRotation;
    };
    
    item hit [15];
    item* control;
    
    struct namepos{
        sf::Text id;
        std::string nombre;
        int* posicion;
        Car* target;
    };
    namepos leaderboard[5];
    
public:
    Game(int N, int IA);
    Game(const Game& orig);
    virtual ~Game();
    
    void go();   
    
private:
    void handleEvents();
    void update();
    void render(float tick);
    void rendercontrol();
    void renderEnemies(float tick);
    
    
    void checkPoints();
    void checkCollisionsBetweeenHitbox();
    void checkCollisionsBetweeenPlayers();
    void burbuja();
    
    /* CREATE MAP */
    item createHitbox(sf::Vector2f wallSize, sf::Vector2f pos, float rotation, int sx, int sy, bool center, float rot);
};

#endif /* GAME_H */

