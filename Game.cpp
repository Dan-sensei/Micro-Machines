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
    window.setVerticalSyncEnabled(false);
     //sf::Vector2f startPos = sf::Vector2f(-2000, -20);
    sf::Vector2f startPos = sf::Vector2f(200, 1081.55);
    //sf::Vector2f startPos = sf::Vector2f(0, 0);

    
    //sf::Image Map;
    //Map.loadFromFile("Images/Mapa.jpg");
    Cool_Map = sf::Sprite (AssetManager::GetTexture("Images/New.jpg")); 

    view.setCenter(startPos);
    view.zoom(1);
    window.setView(view);   
    
    keys = new bool[256];
    for(int i = 0; i<256; i++)
        keys[i]=false;
    
    dtAsSeconds = new float[1];
    
    player = new Player(startPos);
    IA = new Enemy(startPos);
    
    player->setKeys(keys);
    player->setTime(dtAsSeconds);
    IA->setTime(dtAsSeconds);
    
    Light = sf::Color(247, 233, 212);
    Dark = sf::Color(41, 39, 34);
    
    hit = new Game::hitbox [10];
    hit[0] = createHitbox(sf::Vector2f(1000, 3000), sf::Vector2f(-1000, 800), 0);
    hit[1] = createHitbox(sf::Vector2f(1000, 2000), sf::Vector2f(474, -820), 45);   //474 o 475
    hit[2] = createHitbox(sf::Vector2f(5000, 1000), sf::Vector2f(800, -1000), 0);
    hit[3] = createHitbox(sf::Vector2f(1000, 2000), sf::Vector2f(7366, 250), 135);  //7366 o 7365
    hit[4] = createHitbox(sf::Vector2f(1000, 3200), sf::Vector2f(6403, 550), 0);
    hit[5] = createHitbox(sf::Vector2f(1000, 2000), sf::Vector2f(6800, 3128), 45);  //Cambiar la Y
    hit[6] = createHitbox(sf::Vector2f(3800, 1000), sf::Vector2f(2000, 4352), 0);
    hit[7] = createHitbox(sf::Vector2f(2200, 1200), sf::Vector2f(-78, 3286), 0);
    

    hit[1].vertex[0]=sf::Vector2f(474, -820);
    hit[1].vertex[1]=sf::Vector2f(1065,0);
    hit[1].vertex[2]=sf::Vector2f(0, 1065);
    
    std::cout << "V1: (" << hit[1].vertex[0].x << ", " << hit[1].vertex[0].y << ")" << std::endl;
    std::cout << "V2: (" << hit[1].vertex[1].x << ", " << hit[1].vertex[1].y << ")" << std::endl;
    std::cout << "V3: (" << hit[1].vertex[2].x << ", " << hit[1].vertex[2].y << ")" << std::endl;
    std::cout << "V4: (" << hit[1].vertex[3].x << ", " << hit[1].vertex[3].y << ")" << std::endl;
    
    sf::ConvexShape eight;
    eight.setPointCount(6);
    eight.setPoint(0, sf::Vector2f(583, 2702));
    eight.setPoint(1, sf::Vector2f(583, 1308));
    eight.setPoint(2, sf::Vector2f(1308, 583));
    eight.setPoint(3, sf::Vector2f(5460, 583));
    eight.setPoint(4, sf::Vector2f(5820, 943));
    eight.setPoint(5, sf::Vector2f(5820, 2702));
    eight.setFillColor(sf::Color::Cyan);    
    hit[8].convex = eight;
    hit[8].vertex = new sf::Vector2f [6];
    hit[8].vertex[0] = sf::Vector2f(583, 2702);
    hit[8].vertex[1] = sf::Vector2f(583, 1308);
    hit[8].vertex[2] = sf::Vector2f(1308, 583);
    hit[8].vertex[3] = sf::Vector2f(5460, 583);
    hit[8].vertex[4] = sf::Vector2f(5820, 943);
    hit[8].vertex[5] = sf::Vector2f(5820, 2702);
    hit[8].checkVertex = 6;
    
    sf::ConvexShape nine;
    nine.setPointCount(5);
    nine.setPoint(0, sf::Vector2f(5820, 2500));
    nine.setPoint(1, sf::Vector2f(5820, 3284));
    nine.setPoint(2, sf::Vector2f(5335, 3769));
    nine.setPoint(3, sf::Vector2f(2705, 3769));
    nine.setPoint(4, sf::Vector2f(2705, 2500));
    nine.setFillColor(sf::Color::Magenta);    
    hit[9].convex = nine;
    hit[9].vertex = new sf::Vector2f [5];
    hit[9].vertex[0] = sf::Vector2f(5820, 2500);
    hit[9].vertex[1] = sf::Vector2f(5820, 3284);
    hit[9].vertex[2] = sf::Vector2f(5335, 3769);
    hit[9].vertex[3] = sf::Vector2f(2705, 3769);
    hit[9].vertex[4] = sf::Vector2f(2705, 2500);
    hit[9].checkVertex = 5;
    
    
    
    /*
    std::cout << "Vertex 1: (" << hit[2].vertex[0].x << ", " << hit[2].vertex[0].y << ")" << std::endl;
    std::cout << "Vertex 2: (" << hit[2].vertex[1].x << ", " << hit[2].vertex[1].y << ")" << std::endl;
    std::cout << "Vertex 3: (" << hit[2].vertex[2].x << ", " << hit[2].vertex[2].y << ")" << std::endl;
    std::cout << "Vertex 4: (" << hit[2].vertex[3].x << ", " << hit[2].vertex[3].y << ")" << std::endl;
     */
    
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
    IA->logic();
    
    
        
    for(int i = 0; i<10 ; i++){
        //std::cout << "Collision! ("<<player->getCar().getPosition().x << ", "<<player->getCar().getPosition().y<<")" << std::endl;
        //std::cout << "Previous ! ("<< previousPosition.x << ", "<< previousPosition.y<<")" << std::endl;
        if(collides(hit[i].vertex, hit[i].checkVertex)){
            std::cout << "COLLIDES"<<std::endl;   
            
            float x = (hit[i].figure.getPosition().x < player->getCar().getPosition().x) ? -1 : 1;
            float y = (hit[i].figure.getPosition().y < player->getCar().getPosition().y) ? 1 : -1;
            
            mtv.axis.x *=x;
            mtv.axis.y *=y;
            
            std::cout << "MTV - Axis: " << mtv.axis.x << ", " << mtv.axis.y << std::endl;
            std::cout << "MTV - Overlap: " << mtv.distance << std::endl;
            
            player->setPos(sf::Vector2f(mtv.distance * mtv.axis.x, mtv.distance * mtv.axis.y), mtv.axis);
        }
    }
        
         
    view.setCenter(player->getCar().getPosition());
    window.setView(view);
    
    previousPosition = player->getCar().getPosition();
}

void Game::render(){
    window.clear(Dark);
    window.draw(Cool_Map);
    //window.draw(hit[0].figure);
    window.draw(hit[1].figure);
    //window.draw(hit[2].figure);
    window.draw(hit[3].figure);
    window.draw(hit[4].figure);
    window.draw(hit[5].figure);
    window.draw(hit[6].figure);
    window.draw(hit[7].figure);
    window.draw(hit[8].convex);
    window.draw(hit[9].convex);
    
    window.draw(player->getCar());
    window.draw(IA->getCar());
    
    window.display();
}

//Separation Axis Algorithm - Guía seguida: http://www.dyn4j.org/2010/01/sat/
bool Game::collides(sf::Vector2f* vertex, int n){
    
    mtv.axis = sf::Vector2f(0, 0);
    mtv.distance = 0;

    double THE_OVERLAP = 1000000;
    sf::Vector2f MINIMUM;
    double tmp;
    std::vector<sf::Vector2f> finalEdges;
    getNormals(finalEdges, player->getVertex(), 3);
    getNormals(finalEdges, vertex, n);
    
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

void Game::getNormals(std::vector<sf::Vector2f>& finalEdges, sf::Vector2f* vertex, int n){
    
    sf::Vector2f normal;
    sf::Vector2f first;
    sf::Vector2f next;
    sf::Vector2f edge;
    
    double unit;
    for (int i = 0; i < n; i++){
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

Game::hitbox Game::createHitbox(sf::Vector2f wallSize, sf::Vector2f pos, float rotation){
    Game::hitbox h;
    h.figure.setSize(wallSize);
    h.figure.setRotation(rotation);
    h.figure.setFillColor(sf::Color::Red);
    h.figure.setPosition(pos);
    
    h.vertex = new sf::Vector2f [4];
    if(rotation == 0){   
        h.vertex[0]=pos;
        h.vertex[1]=sf::Vector2f(h.vertex[0].x + wallSize.x, h.vertex[0].y);
        h.vertex[2]=sf::Vector2f(h.vertex[0].x + wallSize.x, h.vertex[0].y + wallSize.y);
        h.vertex[3]=sf::Vector2f(h.vertex[0].x, h.vertex[0].y + wallSize.y);
    }

    
    
    h.checkVertex = 3;
    return h;
}