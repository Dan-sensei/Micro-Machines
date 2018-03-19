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
#include <SFML/Audio.hpp>
#include <memory>
#include "Player.h"
#include "Enemy.h"
#include <math.h>
#include "SAT.h"
#include "Animator.h"

class Game {
private:
    const float PI = 3.14159265;
    
    int N_IA;
    int N_PLAYERS;
    int VUELTAS;
    
    sf::Sprite winner;
    bool finisher;
    sf::Sprite sprite;
    sf::RectangleShape turboPos[6];
    
    Animator animator;
    Animator::Animation* turbo;
    sf::RenderWindow window;
    sf::View view;
    sf::View view2;
    sf::View UI;
    sf::Sprite Cool_Map;
    sf::Sprite BACKGROUND;
    
    bool* keys;
    float* dtAsSeconds;
    
    Enemy* IAs[4];
    Player* player[2];
    
    struct State{
        sf::Vector2f position;
        float rotation;
        float scale;
    };
    State previous[6];
    State actual[6];
    
    SAT Sat;
    
    AssetManager manager;
    sf::Clock masterClock;
    sf::Clock normalClock;
    sf::Time deltaTime;
    sf::Time elapsedTime;
    
    sf::Sound TURBO_SOUND;
    sf::Music NIGHT_OF_FIRE;
    sf::Music AHH_BITCONNEEEEEECT;
    sf::Music MRKRAB_VIOLIN;
    
    sf::Color Dark;
    sf::Color Light;

    struct item{
        sf::RectangleShape figure;
        sf::Vector2f* vertex;
        int sx;
        int sy;
        float newRotation;
    };
    
    item hit [15];
    item* control;
    sf::RectangleShape JUMP;
    
    struct namepos{
        sf::Sprite picture;
        int* posicion;
        Car* target;
    };
    sf::Text endMessage;
    namepos leaderboard[6];
    
public:
    Game(int N, int nVueltas);
    Game(const Game& orig);
    virtual ~Game();
    
    void go();   
    
private:
    void handleEvents();
    void update();
    void render(float tick);
    void render_init();
    void rendercontrol();
    void renderPlayers(float tick, int camera);
    void renderEnemies(float tick);
    
    void checkPoints();
    void checkCollisionsBetweeenHitbox();
    void checkCollisionsBetweeenPlayers();
    void checkSpecialInteractions();
    void burbuja();
    
    /* CREATE MAP */
    item createHitbox(sf::Vector2f wallSize, sf::Vector2f pos, float rotation, int sx, int sy, bool center, float rot);
    sf::RectangleShape createTurbo(sf::Vector2f size, sf::Vector2f pos, float rotation);
};

#endif /* GAME_H */

