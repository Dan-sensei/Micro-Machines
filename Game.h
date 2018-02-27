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

class Game {
private:
    sf::RenderWindow window;
    sf::View view;
    sf::Sprite Cool_Map;
    
    bool* keys;
    float* dtAsSeconds;
    Player* player;
    Enemy* IA;
    
    AssetManager manager;
    sf::Clock clock;
    sf::Time deltaTime;
    sf::Time elapsedTime;
    
    //sf::RectangleShape* hitbox;
    sf::Color Dark;
    sf::Color Light;
    
    sf::Vector2f previousPosition;
    
    struct hitbox{
        sf::RectangleShape figure;
        sf::ConvexShape convex;
        sf::Vector2f* vertex;
        int checkVertex;
    };
    
    hitbox* hit;
    
    struct MTV{
        sf::Vector2f axis;
        double distance;
        bool check;
    };
    MTV mtv;
    
public:
    Game();
    Game(const Game& orig);
    virtual ~Game();
    
    void go();   
    
private:
    bool collides(sf::Vector2f* vertex, int n);
    void handleEvents();
    void update();
    void render();
    void getNormals(std::vector<sf::Vector2f>& finalEdges, sf::Vector2f* vertex, int n);
    sf::Vector2<double> projection(sf::Vector2f edge, sf::Vector2f* vertex);
    bool ItOverlaps(sf::Vector2<double> p1, sf::Vector2<double> p2);
    hitbox createHitbox(sf::Vector2f wallSize, sf::Vector2f pos, float rotation);
    float overlapDistance(sf::Vector2<double> p1, sf::Vector2<double> p2);
};

#endif /* GAME_H */

