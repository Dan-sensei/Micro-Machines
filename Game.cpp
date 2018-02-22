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
    sf::Vector2f startPos = sf::Vector2f(-1900, 1500);
    //sf::Vector2f startPos = sf::Vector2f(0, 0);
    sf::Vector2f wallSize = sf::Vector2f(2000, 3000);
    
    //sf::Image Map;
    //Map.loadFromFile("Images/Mapa.jpg");
    //sf::Sprite Cool_Map = sf::Sprite (AssetManager::GetTexture("Images/Mapa.jpg")); 
    
    view.setCenter(startPos);
    
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
    
    hit = new Game::hitbox [6];
    hit[0] = createHitbox(wallSize, sf::Vector2f(0, 0));                         //Derecha
    hit[1] = createHitbox(wallSize, sf::Vector2f(-2000, -3000));                 //Arriba
    hit[2] = createHitbox(wallSize, sf::Vector2f(-4000, 0));                     //Izq
    hit[3] = createHitbox(wallSize, sf::Vector2f(-2000, 3000));                 //Abajo
    hit[4] = createHitbox(wallSize, sf::Vector2f(-2000,0));
    hit[4].figure.setFillColor(Light);
    hit[5] = createHitbox(sf::Vector2f(1000, 2000), sf::Vector2f(-1500, 500));   //Centro
    
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
    
    if(collides()){
        //std::cout << "Collision! ("<<player->getCar().getPosition().x << ", "<<player->getCar().getPosition().y<<")" << std::endl;
        //std::cout << "Previous ! ("<< previousPosition.x << ", "<< previousPosition.y<<")" << std::endl;
        std::cout << "COLLIDES"<<std::endl;
        //player->setPos(previousPosition);
    }
   
    view.setCenter(player->getCar().getPosition());
    window.setView(view);
    
    previousPosition = player->getCar().getPosition();
}

void Game::render(){
    window.clear(Dark);
    window.draw(hit[0].figure);
    window.draw(hit[1].figure);
    window.draw(hit[2].figure);
    window.draw(hit[3].figure);
    window.draw(hit[4].figure);
    window.draw(hit[5].figure);
    
    window.draw(player->getCar());
    window.draw(IA->getCar());
    
    window.display();
}

//Separation Axis Algorithm - Guía seguida: http://www.dyn4j.org/2010/01/sat/
bool Game::collides(){

    double THE_OVERLAP = 1000000;
    sf::Vector2f MINIMUM;
    double tmp;
    std::vector<sf::Vector2f> finalEdges;
    getNormals(finalEdges, player->getVertex());
    getNormals(finalEdges, hit[2].vertex);
    
    sf::Vector2<double> pPlayer;
    sf::Vector2<double> pHitbox;
    
    for(std::vector<sf::Vector2f>::iterator edge = finalEdges.begin(); edge != finalEdges.end(); ++edge){
        pPlayer = projection(*edge, player->getVertex());
        pHitbox = projection(*edge, hit[2].vertex);
        
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

    return true;;
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

Game::hitbox Game::createHitbox(sf::Vector2f wallSize, sf::Vector2f pos){
    Game::hitbox h;
    h.figure.setSize(wallSize);
    h.figure.setFillColor(Dark);
    h.figure.setPosition(pos);
    
    h.vertex = new sf::Vector2f [4];
    h.vertex[0]=pos;
    h.vertex[1]=sf::Vector2f(h.vertex[0].x + wallSize.x, h.vertex[0].y);
    h.vertex[2]=sf::Vector2f(h.vertex[0].x + wallSize.x, h.vertex[0].y + wallSize.y);
    h.vertex[3]=sf::Vector2f(h.vertex[0].x, h.vertex[0].y + wallSize.y);
    
    return h;
}