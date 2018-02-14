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
    sf::Vector2f startPos = sf::Vector2f(-1800, 1500);
    sf::Vector2f wallSize = sf::Vector2f(2000, 3000);
    
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
 
    hitbox = new sf::RectangleShape [9];
    hitbox[0].setSize(wallSize);
    hitbox[1].setSize(wallSize);
    hitbox[2].setSize(wallSize);
    hitbox[3].setSize(wallSize);
    hitbox[4].setSize(wallSize);
    hitbox[5].setSize(sf::Vector2f(1000, 2000));
    
    Light = sf::Color(247, 233, 212);
    Dark = sf::Color(41, 39, 34);
    
    hitbox[0].setPosition(0,0);
    hitbox[1].setPosition(sf::Vector2f(-2000, -3000));
    hitbox[2].setPosition(sf::Vector2f(-4000, 0));
    hitbox[3].setPosition(sf::Vector2f(-2000, 3000));
    hitbox[4].setPosition(sf::Vector2f(-2000,0));
    hitbox[5].setPosition(sf::Vector2f(-1500, 500));
    
    hitbox[0].setFillColor(Game::Dark);
    hitbox[1].setFillColor(Game::Dark);
    hitbox[2].setFillColor(Game::Dark);
    hitbox[3].setFillColor(Game::Dark);
    
    hitbox[4].setFillColor(Game::Light);
    hitbox[5].setFillColor(Game::Dark);
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
    
    player->movement();
    IA->logic();
    
    if(){
        
    }
    view.setCenter(player->getCar().getPosition());
    window.setView(view);
}

void Game::render(){
    window.clear(Dark);
    window.draw(hitbox[0]);
    window.draw(hitbox[1]);
    window.draw(hitbox[2]);
    window.draw(hitbox[3]);
    window.draw(hitbox[4]);
    window.draw(hitbox[5]);
    
    window.draw(player->getCar());
    window.draw(IA->getCar());
    
    window.display();
}