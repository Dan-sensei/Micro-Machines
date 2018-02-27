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

     //sf::Vector2f startPos = sf::Vector2f(-2000, -20);
    sf::Vector2f startPos = sf::Vector2f(150, 1800);
    //sf::Vector2f startPos = sf::Vector2f(0, 0);

    
    //sf::Image Map;
    //Map.loadFromFile("Images/Mapa.jpg");
    Cool_Map = sf::Sprite (AssetManager::GetTexture("Images/New.jpg")); 

    view.setCenter(startPos);
    view.zoom(1.2);
    window.setView(view);   
    
    keys = new bool[256];
    for(int i = 0; i<256; i++)
        keys[i]=false;
    
    dtAsSeconds = new float[1];
    
    player = new Player(startPos);
    IA = new Enemy(sf::Vector2f(80, 1500), 750);
    IA2 = new Enemy(sf::Vector2f(150, 1700), 700);
    IA3 = new Enemy(sf::Vector2f(180, 1650), 680);
    IA4 = new Enemy(sf::Vector2f(200, 1420), 500);
    
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
    hit[13] = createHitbox(sf::Vector2f(685.8935778, 500), sf::Vector2f(5820, 3284), 135, 1, 1, false, 0);   
    hit[14] = createHitbox(sf::Vector2f(2630, 1067), sf::Vector2f(2705, 2702), 0, -1, 1, false, 0);
    
    //PUNTOS DE CONTROL
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
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
                    window.close();
                keys[event.key.code]= true;             
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

    for(int i=0; i< 12; i++){
        
        if(IA->getCar().getGlobalBounds().intersects(control[i].figure.getGlobalBounds()) && !IA->getFlag(i)){
            IA->setDesiredRotation(control[i].newRotation);
            IA->setCheckPoint(i, true);
            std::cout << "IA COLLISION!" <<std::endl;
            break;
        }
        else if(!(IA->getCar().getGlobalBounds().intersects(control[i].figure.getGlobalBounds())))
            IA->setCheckPoint(i, false);
        
        if(IA2->getCar().getGlobalBounds().intersects(control[i].figure.getGlobalBounds()) && !IA2->getFlag(i)){
            IA2->setDesiredRotation(control[i].newRotation);
            IA2->setCheckPoint(i, true);
            std::cout << "IA COLLISION!" <<std::endl;
            break;
        }
        else if(!(IA2->getCar().getGlobalBounds().intersects(control[i].figure.getGlobalBounds())))
            IA2->setCheckPoint(i, false);
        
        if(IA3->getCar().getGlobalBounds().intersects(control[i].figure.getGlobalBounds()) && !IA3->getFlag(i)){
            IA3->setDesiredRotation(control[i].newRotation);
            IA3->setCheckPoint(i, true);
            std::cout << "IA COLLISION!" <<std::endl;
            break;
        }
        else if(!(IA3->getCar().getGlobalBounds().intersects(control[i].figure.getGlobalBounds())))
            IA3->setCheckPoint(i, false);
        
        if(IA4->getCar().getGlobalBounds().intersects(control[i].figure.getGlobalBounds()) && !IA4->getFlag(i)){
            IA4->setDesiredRotation(control[i].newRotation);
            IA4->setCheckPoint(i, true);
            std::cout << "IA COLLISION!" <<std::endl;
            break;
        }
        else if(!(IA4->getCar().getGlobalBounds().intersects(control[i].figure.getGlobalBounds())))
            IA4->setCheckPoint(i, false);
    }

    IA->logic();
    IA2->logic();
    IA3->logic();
    IA4->logic();
    
    for(int i = 0; i<15 ; i++){
        //std::cout << "Collision! ("<<player->getCar().getPosition().x << ", "<<player->getCar().getPosition().y<<")" << std::endl;
        //std::cout << "Previous ! ("<< previousPosition.x << ", "<< previousPosition.y<<")" << std::endl;
        if(collides(player->getVertex(), hit[i].vertex)){
            std::cout << "COLLIDES"<<std::endl;   
            
            mtv.axis.x = hit[i].sx * abs(mtv.axis.x);
            mtv.axis.y = hit[i].sy * abs(mtv.axis.y);
            
            std::cout << "MTV - Axis: " << mtv.axis.x << ", " << mtv.axis.y << std::endl;
            std::cout << "MTV - Overlap: " << mtv.distance << std::endl;
            
            player->setPos(sf::Vector2f(mtv.axis.x*mtv.distance,  mtv.axis.y*mtv.distance), mtv.axis);
        }
    }
       
   
    view.setCenter(player->getCar().getPosition());
    window.setView(view);
    
    previousPosition = player->getCar().getPosition();
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
        pPlayer = projection(*edge, player->getVertex());
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
    std::cout << "Origin: "<< h.figure.getPosition().x << ", "<<h.figure.getPosition().y << std::endl;
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