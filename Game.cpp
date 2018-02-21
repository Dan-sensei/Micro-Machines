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

#include "Game.h"


Game::Game()
:window(sf::VideoMode(1280, 720), "MicroMachines - Neon Edition")
,view(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y))
{
    window.setFramerateLimit(60);
    window.setMouseCursorVisible(false);
     //sf::Vector2f startPos = sf::Vector2f(-2000, -20);
    sf::Vector2f startPos = sf::Vector2f(1300, 1830);
    //sf::Vector2f startPos = sf::Vector2f(0, 0);
    sf::Vector2f wallSize = sf::Vector2f(2000, 3000);
    
    sf::Image Map;
    Map.loadFromFile("Images/Mapa.jpg");
    Cool_Map = sf::Sprite (AssetManager::GetTexture("Images/Map_collision.jpg")); 
    collision.loadFromFile("Images/Map_collision.jpg");

    view.setCenter(startPos);
    view.zoom(1.3f);
    
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
    
    //std::cout<< "Coord (" << player->getCar().getPosition().x << ", "<< player->getCar().getPosition().y<< ")" << std::endl;
    if(collides()){
        //std::cout << "Collision! ("<<player->getCar().getPosition().x << ", "<<player->getCar().getPosition().y<<")" << std::endl;
        //std::cout << "Previous ! ("<< previousPosition.x << ", "<< previousPosition.y<<")" << std::endl;
        std::cout << "COLLIDES"<<std::endl;
        player->setPos(previousPosition);
    }
   
    view.setCenter(player->getCar().getPosition());
    window.setView(view);
    
    previousPosition = player->getCar().getPosition();
}

void Game::render(){
    window.clear(Light);
    window.draw(Cool_Map);
    window.draw(player->getCar());
    window.draw(IA->getCar());
    
    window.display();
}

bool Game::collides(){

    if(collision.getPixel(player->getVertex()[1].x, player->getVertex()[1].y).toInteger() == 255 )
        std::cout << "NEGRO";
    else
        std::cout << "BLANCO";
    
    std::cout << "        ";
    
    if(collision.getPixel(player->getVertex()[2].x, player->getVertex()[2].y).toInteger() == 255 )
        std::cout << "NEGRO";
    else
        std::cout << "BLANCO";
    
    std::cout << "" << std::endl;
    
    if(collision.getPixel(player->getVertex()[0].x, player->getVertex()[0].y).toInteger() == 255 )
        std::cout << "NEGRO";
    else
        std::cout << "BLANCO";
    
     std::cout << "        ";
    
    if(collision.getPixel(player->getVertex()[3].x, player->getVertex()[3].y).toInteger() == 255 )
        std::cout << "NEGRO";
    else
        std::cout << "BLANCO";
    
    std::cout << "" << std::endl << std::endl;
    
    //std::cout << collision.getPixel(player->getVertex()[1].x, player->getVertex()[1].y).toInteger() << std::endl;
    /*
    if(collision.getPixel(player->getVertex()[0].x, player->getVertex()[0].y-60).toInteger() == 255)
        return true;
    if(collision.getPixel(player->getVertex()[1].x, player->getVertex()[1].y-60).toInteger() == 255)
        return true;
    if(collision.getPixel(player->getVertex()[2].x, player->getVertex()[2].y-60).toInteger() == 255)
        return true;
    if(collision.getPixel(player->getVertex()[3].x, player->getVertex()[3].y-60).toInteger() == 255)
        return true;
     */
    
    return false;
}