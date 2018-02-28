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


Game::Game()
:window(sf::VideoMode(800, 800), "MicroMachines - Neon Edition")
,view(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y))
{
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
    
    player = new Player(startPos);
    IA = new Enemy(sf::Vector2f(80, 1500), 850);
    IA2 = new Enemy(sf::Vector2f(150, 1700), 800);
    IA3 = new Enemy(sf::Vector2f(180, 1650), 820);
    IA4 = new Enemy(sf::Vector2f(200, 1420), 540);
    
    player->setKeys(keys);
    player->setTime(dtAsSeconds);
    IA->setTime(dtAsSeconds);
    IA2->setTime(dtAsSeconds);
    IA3->setTime(dtAsSeconds);
    IA4->setTime(dtAsSeconds);
    
    Light = sf::Color(247, 233, 212);
    Dark = sf::Color(41, 39, 34);

    //HITBOX DEL MAPA
                         //    TAMAÑO                    POSICION       ROTACION X  Y  FACE
    hit[0] = createHitbox(sf::Vector2f(1000, 3000), sf::Vector2f(-1000, 800), 0, 1, 1, false, 0);
    hit[1] = createHitbox(sf::Vector2f(1000, 2000), sf::Vector2f(474, -820), 45, 1, 1, false, 0);   //474 o 475
    hit[2] = createHitbox(sf::Vector2f(5000, 1000), sf::Vector2f(800, -1000), 0, 1, 1, false, 0);
    hit[3] = createHitbox(sf::Vector2f(1000, 2000), sf::Vector2f(7366, 250), 135, -1, 1, false, 0);  //7366 o 7365
    hit[4] = createHitbox(sf::Vector2f(1000, 3200), sf::Vector2f(6403, 550), 0, -1, 1, false, 0);
    hit[5] = createHitbox(sf::Vector2f(1000, 2000), sf::Vector2f(6800, 3128), 45, -1, -1, false, 0);  //Cambiar la Y
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
  
    leaderboard[0].nombre = "IA 1";
    leaderboard[1].nombre = "IA 2";
    leaderboard[2].nombre = "IA 3";
    leaderboard[3].nombre = "IA 4";
    leaderboard[4].nombre = "Player";
    
    leaderboard[0].posicion = IA->getP_pos();
    leaderboard[1].posicion = IA2->getP_pos();
    leaderboard[2].posicion = IA3->getP_pos();
    leaderboard[3].posicion = IA4->getP_pos();
    leaderboard[4].posicion = player->getP_pos();
    
    leaderboard[0].target = IA;
    leaderboard[1].target = IA2;
    leaderboard[2].target = IA3;
    leaderboard[3].target = IA4;
    leaderboard[4].target = player;
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


    checkPoint(IA, control[IA->getPosition() % 12 ], IA->getPosition() % 12);
    checkPoint(IA2, control[(IA2->getPosition()) % 12 ], IA2->getPosition() % 12);
    checkPoint(IA3, control[(IA3->getPosition()) % 12 ], IA3->getPosition() % 12);
    checkPoint(IA4, control[IA4->getPosition() % 12], IA4->getPosition() % 12);

    
    int i = (int)player->getPosition() % 12;
    if(player->getCar().getGlobalBounds().intersects(control[i].figure.getGlobalBounds()) && !player->getFlag(i) && player->handleIncremenet(i)){
         std::cout << "i: " << std::endl;
         player->setCheckPoint(i, true);
         player->setVisited(i);
         player->incrementPosition(1);

     }
     else if(!(player->getCar().getGlobalBounds().intersects(control[i].figure.getGlobalBounds())))
         player->setCheckPoint(i, false); 
        
    
    
    //std::cout << "Posicion: " << player->getPosition() << std::endl;
    IA->logic();
    IA2->logic();
    IA3->logic();
    IA4->logic();
    
    for(i = 0; i<15 ; i++){
        
        if(collides(player->getVertex(), hit[i].vertex)){
            std::cout << "COLLIDES"<<std::endl;   
            
            mtv.axis.x = hit[i].sx * abs(mtv.axis.x);
            mtv.axis.y = hit[i].sy * abs(mtv.axis.y);
            
            std::cout << "MTV - Axis: " << mtv.axis.x << ", " << mtv.axis.y << std::endl;
            std::cout << "MTV - Overlap: " << mtv.distance << std::endl;
            
            player->setPos(sf::Vector2f(mtv.axis.x*mtv.distance,  mtv.axis.y*mtv.distance), mtv.axis);
        }
         
        if(collides(IA->getVertex(), hit[i].vertex)){
            mtv.axis.x = hit[i].sx * abs(mtv.axis.x);
            mtv.axis.y = hit[i].sy * abs(mtv.axis.y);
            IA->setPos(sf::Vector2f(mtv.axis.x*mtv.distance,  mtv.axis.y*mtv.distance), mtv.axis);
        }        
        if(collides(IA2->getVertex(), hit[i].vertex)){
            mtv.axis.x = hit[i].sx * abs(mtv.axis.x);
            mtv.axis.y = hit[i].sy * abs(mtv.axis.y);
            IA2->setPos(sf::Vector2f(mtv.axis.x*mtv.distance,  mtv.axis.y*mtv.distance), mtv.axis);
        }
        if(collides(IA3->getVertex(), hit[i].vertex)){
            mtv.axis.x = hit[i].sx * abs(mtv.axis.x);
            mtv.axis.y = hit[i].sy * abs(mtv.axis.y);
            IA3->setPos(sf::Vector2f(mtv.axis.x*mtv.distance,  mtv.axis.y*mtv.distance), mtv.axis);
        }
        if(collides(IA4->getVertex(), hit[i].vertex)){
            mtv.axis.x = hit[i].sx * abs(mtv.axis.x);
            mtv.axis.y = hit[i].sy * abs(mtv.axis.y);
            IA4->setPos(sf::Vector2f(mtv.axis.x*mtv.distance,  mtv.axis.y*mtv.distance), mtv.axis);
        }

    }
       
    burbuja();
    
    std::cout << "1. " << leaderboard[0].nombre << " - P: " << leaderboard[0].target->getPosition() << std::endl;
    std::cout << "2. " << leaderboard[1].nombre << " - P: " << leaderboard[1].target->getPosition() << std::endl;
    std::cout << "3. " << leaderboard[2].nombre << " - P: " << leaderboard[2].target->getPosition() << std::endl;
    std::cout << "3. " << leaderboard[3].nombre << " - P: " << leaderboard[3].target->getPosition() << std::endl;
    std::cout << "4. " << leaderboard[4].nombre << " - P: " << leaderboard[4].target->getPosition() << std::endl << std::endl;

    view.setCenter(player->getCar().getPosition());
    window.setView(view);
    
}

void Game::render(){
    window.clear(Dark);
    window.draw(Cool_Map);
    rendercontrol();
    
    window.draw(player->getCar());
    window.draw(IA->getCar());
    window.draw(IA2->getCar());
    window.draw(IA3->getCar());
    window.draw(IA4->getCar());
    
    window.display();
}

void Game::rendercontrol(){
    for(int i=0; i< 12; i++)
        window.draw(control[i].figure);
}

void Game::checkPoint(Enemy* npc, item checkbox, int i){
    if(npc->getCar().getGlobalBounds().intersects(checkbox.figure.getGlobalBounds()) && !npc->getFlag(i) && npc->handleIncremenet(i)){
        npc->setDesiredRotation(checkbox.newRotation);
        npc->setCheckPoint(i, true);
        npc->setVisited(i);
        npc->incrementPosition(1);
    }
    else if(!(npc->getCar().getGlobalBounds().intersects(checkbox.figure.getGlobalBounds()))){
        //std::cout << "ELSE IF" <<std::endl;
        npc->setCheckPoint(i, false);
    }
    std::cout << std::endl;
}

//Separation Axis Algorithm - Guía seguida: http://www.dyn4j.org/2010/01/sat/
bool Game::collides(sf::Vector2f* target, sf::Vector2f* vertex){
    mtv.axis = sf::Vector2f(0, 0);
    mtv.distance = 0;

    double THE_OVERLAP = 1000000;
    sf::Vector2f MINIMUM;
    double tmp;
    std::vector<sf::Vector2f> finalEdges;
    getNormals(finalEdges, target);
    getNormals(finalEdges, vertex);
    sf::Vector2<double> pPlayer;
    sf::Vector2<double> pHitbox;
    
    for(std::vector<sf::Vector2f>::iterator edge = finalEdges.begin(); edge != finalEdges.end(); ++edge){
        pPlayer = projection(*edge, target);
        pHitbox = projection(*edge, vertex);
        
        if(!ItOverlaps(pPlayer, pHitbox)){
           // std::cout << "NOPE" << std::endl;
            return false;
        }
        else{
            tmp = overlapDistance(pPlayer, pHitbox);
            if(tmp < THE_OVERLAP){
                THE_OVERLAP = tmp;
                MINIMUM = *edge;
            }
        }
    }
    
    mtv.axis = MINIMUM;
    mtv.distance = THE_OVERLAP;
    
    return true;
}

void Game::getNormals(std::vector<sf::Vector2f>& finalEdges, sf::Vector2f* vertex){
    
    sf::Vector2f normal;
    sf::Vector2f first;
    sf::Vector2f next;
    sf::Vector2f edge;
    
    /* METODOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO */
    double unit;
    for (int i = 0; i < 2; i++){
        first = vertex[i];
        next = vertex[i+1==4 ? 0 : i+1];
        edge = sf::Vector2f(next.x - first.x, next.y - first.y);
        normal = sf::Vector2f(-edge.y, edge.x);
        unit = sqrt(normal.x * normal.x + normal.y * normal.y);
        normal = sf::Vector2f(normal.x/unit, normal.y/unit);
        finalEdges.push_back(normal);
    }
}

sf::Vector2<double> Game::projection(sf::Vector2f edge, sf::Vector2f* vertex){
    sf::Vector2<double> p;
    
    double min;
    double max;
    double tmp;
    min = edge.x * vertex[0].x + edge.y * vertex[0].y;
    max= min;
    //std::cout << "NV: " << nv << std::endl;
    for(int i=1; i< 4; i++){   
        tmp = edge.x * vertex[i].x + edge.y * vertex[i].y;
        if(tmp>=max)
            max = tmp;
        else if(tmp < min)
            min = tmp;
    }
    p= sf::Vector2<double>(min, max);

    return p;
}

bool Game::ItOverlaps(sf::Vector2<double> p1, sf::Vector2<double> p2){
    if(p1.x > p2.y || p2.x > p1.y)
        return false;
    return true;
}

float Game::overlapDistance(sf::Vector2<double> p1, sf::Vector2<double> p2){
    float x;  
    x = (p1.y < p2.y) ? p1.y -p2.x : p2.y - p1.x;
    return x;
}

Game::item Game::createHitbox(sf::Vector2f wallSize, sf::Vector2f pos, float rotation, int sx, int sy, bool center, float rot){
    Game::item h;
    h.figure.setSize(wallSize);
    
    
    h.figure.setRotation(rotation);
    h.figure.setPosition(pos);
    
    if(center){
        
        h.figure.setOrigin(wallSize.x/2, wallSize.y/2);
    //std::cout << "Origin: "<< h.figure.getPosition().x << ", "<<h.figure.getPosition().y << std::endl;
    }
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
    double unit;
    sf::Vector2f axis;
    for (int i=1; i<5; i++)
        for (int j=0 ; j<5 - 1; j++){
            std::cout << "Waaaa incial" << std:: endl;
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
                
                std::cout << "PREV---- : " << prev << std:: endl;
                
                axis = control[(*leaderboard[j].posicion) % 12].figure.getPosition() - control[prev].figure.getPosition();
                unit = sqrt(axis.x * axis.x + axis.y * axis.y);
                axis = sf::Vector2f(axis.x/unit, axis.y/unit);
                std::cout << "EJE: " << axis.x << ", " << axis.y << std:: endl;
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
                
                std::cout << "WAAAAAAAAAfinal" << std:: endl;
                if(pro1 < pro2){
                    tmp = leaderboard[j];
                    leaderboard[j] = leaderboard[j+1];
                    leaderboard[j+1] = tmp;
                }
            }
        }
}
