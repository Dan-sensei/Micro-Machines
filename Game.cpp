/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Game.cpp
 * Author: dan
 * 
 * Created on 13 de febrero de 2018, 15:36
 */

#include <SFML/Window/Event.hpp>
#include <iostream>

#include "Game.h"


Game::Game(int N, int IA):
window(sf::VideoMode(800, 800), "MicroMachines - Neon Edition")
{
    //Sat = new SAT();
    N_PLAYERS = N;
    N_IA = IA;
    
    view = sf::View(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
    window.setFramerateLimit(60);
    window.setMouseCursorVisible(false);
    
    sf::Vector2f startPos = sf::Vector2f(150, 1800);
    Cool_Map = sf::Sprite (AssetManager::GetTexture("Images/New.jpg")); 

    view.setCenter(startPos);
    view.zoom(1.3);
    window.setView(view);   
    
    keys = new bool[256];
    for(int i = 0; i<256; i++)
        keys[i]=false;
    
    dtAsSeconds = new float[1];
    //sprite_name, startPosition, MAX_SPEED, acceleration, Initial_rotation, deltaTime, rotation_speed, keyboard
    
    player = new Player("Images/HERO.jpg", startPos, 1000, 17, 0, dtAsSeconds, 220, keys);
    IAs[0] = new Enemy("Images/Enemy.jpg", sf::Vector2f(80, 1500), 1100, 20, 0, dtAsSeconds);
    IAs[1] = new Enemy("Images/Enemy.jpg", sf::Vector2f(150, 1700), 950, 30, 0, dtAsSeconds);
    IAs[2] = new Enemy("Images/Enemy.jpg", sf::Vector2f(180, 1650), 1000, 25, 0, dtAsSeconds);
    IAs[3] = new Enemy("Images/Enemy.jpg", sf::Vector2f(200, 1420), 980, 17, 0, dtAsSeconds);
    
    Light = sf::Color(247, 233, 212);
    Dark = sf::Color(41, 39, 34);

    //HITBOX DEL MAPA
                         //    TAMAÑO                    POSICION       ROTACION X  Y  FACE
    hit[0] = createHitbox(sf::Vector2f(1000, 3000), sf::Vector2f(-1000, 800), 0, 1, 1, false, 0);
    hit[1] = createHitbox(sf::Vector2f(1000, 2000), sf::Vector2f(474, -820), 45, 1, 1, false, 0);
    hit[2] = createHitbox(sf::Vector2f(5000, 1000), sf::Vector2f(800, -1000), 0, 1, 1, false, 0);
    hit[3] = createHitbox(sf::Vector2f(1000, 2000), sf::Vector2f(7366, 250), 135, -1, 1, false, 0);
    hit[4] = createHitbox(sf::Vector2f(1000, 3200), sf::Vector2f(6403, 550), 0, -1, 1, false, 0);
    hit[5] = createHitbox(sf::Vector2f(1000, 2000), sf::Vector2f(6800, 3128), 45, -1, -1, false, 0);
    hit[6] = createHitbox(sf::Vector2f(3800, 1000), sf::Vector2f(2000, 4352), 0, 1, -1, false, 0);
    hit[7] = createHitbox(sf::Vector2f(2200, 1200), sf::Vector2f(-78, 3286), 0, 1, -1, false, 0);
    hit[8] = createHitbox(sf::Vector2f(4752, 1394), sf::Vector2f(583, 1308), 0, -1, 1, false, 0);
    hit[9] = createHitbox(sf::Vector2f(1025.304833, 800), sf::Vector2f(583, 1308), -45, -1, -1, false, 0);
    hit[10] = createHitbox(sf::Vector2f(4152, 1000), sf::Vector2f(1308, 583), 0, 1, -1, false, 0); 
    hit[11] = createHitbox(sf::Vector2f(509.1168825, 800), sf::Vector2f(5460, 583), 45, 1, -1, false, 0);
    hit[12] = createHitbox(sf::Vector2f(485, 2341), sf::Vector2f(5335, 943), 0, 1, 1, false, 0); 
    hit[13] = createHitbox(sf::Vector2f(685.89357785, 500), sf::Vector2f(5820, 3284), 135, 1, 1, false, 0);   
    hit[14] = createHitbox(sf::Vector2f(2630, 1067), sf::Vector2f(2705, 2702), 0, -1, 1, false, 0);
    
    //PUNTOS DE CONTROL
    control = new item [12];
    control[0] = createHitbox(sf::Vector2f(583, 5), sf::Vector2f(291.5, 1308), 0, 1, 1, true, 45);
    control[1] = createHitbox(sf::Vector2f(5, 583), sf::Vector2f(1308, 291.5), 0, 1, 1, true, 45);
    control[2] = createHitbox(sf::Vector2f(5, 583), sf::Vector2f(5460, 291.5), 0, 1, 1, true, 45);
    control[3] = createHitbox(sf::Vector2f(583, 5), sf::Vector2f(6111.5, 943), 0, 1, 1, true, 45);
    control[4] = createHitbox(sf::Vector2f(583, 5), sf::Vector2f(6111.5, 3284), 0, 1, 1, true, 45);
    control[5] = createHitbox(sf::Vector2f(5, 583), sf::Vector2f(5335, 4060.5), 0, 1, 1, true, 45);
    control[6] = createHitbox(sf::Vector2f(5, 583), sf::Vector2f(2705, 4060.5), 0, 1, 1, true, 45);
    control[7] = createHitbox(sf::Vector2f(583, 5), sf::Vector2f(2413.5, 3769), 0, 1, 1, true, 45);
    control[8] = createHitbox(sf::Vector2f(583, 5), sf::Vector2f(2413.5, 3286), 0, 1, 1, true, -45);
    control[9] = createHitbox(sf::Vector2f(5, 583), sf::Vector2f(2121, 2994.5), 0, 1, 1, true, -45);
    control[10] = createHitbox(sf::Vector2f(5, 583), sf::Vector2f(583, 2994.5), 0, 1, 1, true, 45);
    control[11] = createHitbox(sf::Vector2f(583, 5), sf::Vector2f(291.5, 2702), 0, 1, 1, true, 45);
  
    std::string text;
    for(int i = 0; i < N_IA; i++){
        text = "IA #"+std::to_string(i+1);
        leaderboard[i].nombre = text;
        leaderboard[i].posicion = IAs[i]->getP_pos();
        leaderboard[i].target = IAs[i];
        leaderboard[i].id = sf::Text(text, AssetManager::GetFont("Fonts/LemonMilk.otf"));
    }
    
    leaderboard[4].nombre = "Player";
    leaderboard[4].posicion = player->getP_pos();
    leaderboard[4].target = player;
    leaderboard[4].id = sf::Text("Player", AssetManager::GetFont("Fonts/LemonMilk.otf"));
}

Game::~Game() {
}

void Game::go(){
    
    while(window.isOpen()){
        handleEvents();
        update();
        render();
    }
}

void Game::handleEvents(){
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type){

            case sf::Event::EventType::Closed:
                window.close();
                break;

            case sf::Event::EventType::KeyPressed:
                std::cout<< "Tecla " << event.key.code << std::endl;
                keys[event.key.code]= true;
                if(keys[16]) window.close();        //Cerrar
                break;

            case sf::Event::KeyReleased:
                keys[event.key.code]= false;
                break;

            default:
                break;
        }
    }
}

void Game::update(){
    
    deltaTime = clock.restart();
    elapsedTime += deltaTime;
    dtAsSeconds[0] = deltaTime.asSeconds();
    //std::cout<< "Vertex 1: " << player->getVertex()[1].x << ", " << player->getVertex()[1].y << std::endl;
    
    player->movement(); 
    for(int i= 0; i<4; i++)
        IAs[i]->logic();
   

    checkPoints();
    checkCollisionsBetweeenHitbox();
    checkCollisionsBetweeenPlayers();
    burbuja();
    //std::cout << "Posicion: " << player->getPosition() << std::endl;
     
    
    leaderboard[0].id.setPosition(player->getCar().getPosition() - sf::Vector2f(450, 450));
    leaderboard[1].id.setPosition(player->getCar().getPosition() - sf::Vector2f(450, 400));
    leaderboard[2].id.setPosition(player->getCar().getPosition() - sf::Vector2f(450, 350));
    leaderboard[3].id.setPosition(player->getCar().getPosition() - sf::Vector2f(450, 300));
    leaderboard[4].id.setPosition(player->getCar().getPosition() - sf::Vector2f(450, 250));
    
    view.setCenter(player->getCar().getPosition());
    window.setView(view);
    
    if(player->getVueltas() == 2){
        window.close();
    }
    
}

void Game::render(){
    window.clear(Dark);
    window.draw(Cool_Map);
    
    window.draw(leaderboard[0].id);
    window.draw(leaderboard[1].id);
    window.draw(leaderboard[2].id);
    window.draw(leaderboard[3].id);
    window.draw(leaderboard[4].id);
    rendercontrol();
    renderEnemies();
    window.draw(player->getCar());
    
    
    
    window.display();
}

void Game::rendercontrol(){
    for(int i=0; i< 12; i++)
        window.draw(control[i].figure);
}

void Game::renderEnemies(){
    for(int i=0; i< 4; i++)
        window.draw(IAs[i]->getCar());
}

void Game::checkPoints(){
   
    int j;
    for(int i=0; i<4; i++){

        j = IAs[i]->getPosition() % 12;
        if(IAs[i]->getCar().getGlobalBounds().intersects(control[j].figure.getGlobalBounds()) && !IAs[i]->getFlag(j) && IAs[i]->handleIncremenet(j)){
            
            IAs[i]->setDesiredRotation(control[j].newRotation);
            IAs[i]->setCheckPoint(j, true);
            IAs[i]->setVisited(j);
            IAs[i]->incrementPosition(1);
        }
        else if(!(IAs[i]->getCar().getGlobalBounds().intersects(control[j].figure.getGlobalBounds()))){
            IAs[i]->setCheckPoint(j, false);
        }
    }
    
    j = player->getPosition() % 12;
    if(player->getCar().getGlobalBounds().intersects(control[j].figure.getGlobalBounds()) && !player->getFlag(j) && player->handleIncremenet(j)){
         player->setCheckPoint(j, true);
         player->setVisited(j);
         player->incrementPosition(1);

     }
     else if(!(player->getCar().getGlobalBounds().intersects(control[j].figure.getGlobalBounds())))
         player->setCheckPoint(j, false);    
}

void Game::checkCollisionsBetweeenHitbox(){
    
    for(int i=0; i< N_IA; i++){
        for(int j = 0; j<15 ; j++){
            if((Sat_result = Sat.collides(IAs[i]->getVertex(), hit[j].vertex)).collides){
                Sat_result.mtv.x = hit[j].sx * abs(Sat_result.mtv.x);
                Sat_result.mtv.y = hit[j].sy * abs(Sat_result.mtv.y);
                IAs[i]->setPos(sf::Vector2f(Sat_result.mtv.x,  Sat_result.mtv.y), Sat_result.mtv);
            }  
        }
    }
    
    for(int i = 0; i < 15; i++)
        if((Sat_result = Sat.collides(player->getVertex(), hit[i].vertex)).collides){
            Sat_result.mtv.x = hit[i].sx * abs(Sat_result.mtv.x);
            Sat_result.mtv.y = hit[i].sy * abs(Sat_result.mtv.y);
            player->setPos(sf::Vector2f(Sat_result.mtv.x,  Sat_result.mtv.y), Sat_result.mtv);
        }
}

void Game::checkCollisionsBetweeenPlayers(){
    float x;
    float y;
    for(int i=0; i< N_IA; i++){
        for(int j = 0; j<15 && i!=j; j++){
            if((Sat_result = Sat.collides(IAs[i]->getVertex(), IAs[j]->getVertex())).collides){
                x = (IAs[i]->getCar().getPosition().x > IAs[j]->getCar().getPosition().x) ? 1 : -1;
                y = (IAs[i]->getCar().getPosition().y > IAs[j]->getCar().getPosition().y) ? 1 : -1;

                IAs[i]->setPos(sf::Vector2f(Sat_result.mtv.x*x,  Sat_result.mtv.y*y), Sat_result.mtv);
            }
            if((Sat_result = Sat.collides(IAs[i]->getVertex(), player->getVertex())).collides){
                x = (IAs[i]->getCar().getPosition().x > player->getCar().getPosition().x) ? 1 : -1;
                y = (IAs[i]->getCar().getPosition().y > player->getCar().getPosition().y) ? 1 : -1;

                IAs[i]->setPos(sf::Vector2f(Sat_result.mtv.x*x,  Sat_result.mtv.y*y), Sat_result.mtv);
            }
            
        }
    }
    
    for(int i=0; i< N_IA; i++){
        if((Sat_result = Sat.collides(player->getVertex(), IAs[i]->getVertex())).collides){
            x = (player->getCar().getPosition().x > IAs[i]->getCar().getPosition().x) ? 1 : -1;
            y = (player->getCar().getPosition().y > IAs[i]->getCar().getPosition().y) ? 1 : -1;
            
            player->setPos(sf::Vector2f(Sat_result.mtv.x*x,  Sat_result.mtv.y*y), Sat_result.mtv);
        }
    }
    
}


Game::item Game::createHitbox(sf::Vector2f wallSize, sf::Vector2f pos, float rotation, int sx, int sy, bool center, float rot){
    Game::item h;
    h.figure.setSize(wallSize);
    h.figure.setRotation(rotation);
    h.figure.setPosition(pos);
    
    if(center)   
        h.figure.setOrigin(wallSize.x/2, wallSize.y/2);
    
    h.vertex = new sf::Vector2f [4];
    h.vertex[0]=pos;
    if(rotation == 0){   
        h.vertex[1]=sf::Vector2f(h.vertex[0].x + wallSize.x, h.vertex[0].y);
        h.vertex[2]=sf::Vector2f(h.vertex[0].x + wallSize.x, h.vertex[0].y + wallSize.y);
        h.vertex[3]=sf::Vector2f(h.vertex[0].x, h.vertex[0].y + wallSize.y);
    }
    else{
        h.vertex[1] = sf::Vector2f(h.vertex[0].x+cos(rotation*PI/180)*wallSize.x, h.vertex[0].y + sin(rotation*PI/180)*wallSize.x);
        h.vertex[2] = sf::Vector2f(h.vertex[0].x+cos(rotation*PI/180)*wallSize.x - sin(rotation*PI/180)*wallSize.y , h.vertex[0].y +cos(rotation*PI/180)*wallSize.y + sin(rotation*PI/180)*wallSize.x);
        h.vertex[3] = sf::Vector2f(h.vertex[0].x-sin(rotation*PI/180)*wallSize.y, h.vertex[0].y + cos(rotation*PI/180)*wallSize.y);
    }
    
    h.sx = sx;
    h.sy = sy;
    h.newRotation = rot;
    return h;
}

void Game::burbuja(){
    namepos tmp;
    int pro1;
    int pro2;
    sf::Vector2f axis;
    for (int i=1; i<5; i++)
        for (int j=0 ; j<5 - 1; j++){

            if (*leaderboard[j].posicion < *leaderboard[j+1].posicion){  
                
                tmp = leaderboard[j];
                leaderboard[j] = leaderboard[j+1];
                leaderboard[j+1] = tmp;
            }
            else if(*leaderboard[j].posicion == *leaderboard[j+1].posicion){
                
                int prev = *leaderboard[j].posicion % 12 -1;
                if(*leaderboard[j].posicion % 12 ==0){
                    prev = 11;
                }
                
                axis = control[(*leaderboard[j].posicion) % 12].figure.getPosition() - control[prev].figure.getPosition();
                axis = Sat.normalize(axis);
                //std::cout << "EJE: " << axis.x << ", " << axis.y << std:: endl;
                if(axis.x == 0){
                    pro1 = leaderboard[j].target->getCar().getPosition().y * axis.y;
                    pro2 = leaderboard[j+1].target->getCar().getPosition().y * axis.y;
                }
                else if(axis.y == 0){      
                    pro1 = leaderboard[j].target->getCar().getPosition().x * axis.x;
                    pro2 = leaderboard[j+1].target->getCar().getPosition().x * axis.x;
                }
                else{
                    pro1 = axis.x * (leaderboard[j].target->getCar().getPosition().x) + axis.y * (leaderboard[j].target->getCar().getPosition().y);
                    pro2 = axis.x * (leaderboard[j+1].target->getCar().getPosition().x) + axis.y * (leaderboard[j+1].target->getCar().getPosition().y);
                }
               
                if(pro1 < pro2){
                    tmp = leaderboard[j];
                    leaderboard[j] = leaderboard[j+1];
                    leaderboard[j+1] = tmp;
                }
            }
        }
}
