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
    Enemy* IA2;
    Enemy* IA3;
    Enemy* IA4;
    
    AssetManager manager;
    sf::Clock clock;
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
    
    struct MTV{
        sf::Vector2f axis;
        double distance;
        bool check;
    };
    MTV mtv;
    
    struct namepos{
        std::string nombre;
        int* posicion;
        Car* target;
    };
    namepos leaderboard[5];
    
public:
    Game();
    Game(const Game& orig);
    virtual ~Game();
    
    void go();   
    
private:
    void handleEvents();
    void update();
    void render();
    void rendercontrol();
    
    /*  SAT  */
    bool collides(sf::Vector2f* target, sf::Vector2f* vertex);
    void getNormals(std::vector<sf::Vector2f>& finalEdges, sf::Vector2f* vertex);
    sf::Vector2<double> projection(sf::Vector2f edge, sf::Vector2f* vertex);
    bool ItOverlaps(sf::Vector2<double> p1, sf::Vector2<double> p2);
    float overlapDistance(sf::Vector2<double> p1, sf::Vector2<double> p2);
    
    void checkPoint(Enemy* npc, item checkbox, int i);
    void burbuja();
    
    /* CREATE MAP */
    item createHitbox(sf::Vector2f wallSize, sf::Vector2f pos, float rotation, int sx, int sy, bool center, float rot);
};

#endif /* GAME_H */

