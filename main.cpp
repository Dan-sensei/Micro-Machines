/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: dan
 *
 * Created on 2 de febrero de 2018, 11:47
 */

#include <cstdlib>
#include <iostream>
#include <math.h> 
#include <SFML/Graphics.hpp>

#include "AssetManager.h"
#include "Enemy.h"
#include "Player.h"

using namespace std;

const float AC = 20;
const float MAXSPEED = 800;
const float ROTATION = 300;
const float PI = 3.14159265;
/*
 * 
 */
void initShape(sf::RectangleShape& shape, sf::Vector2f const& pos, sf::Color const& color){
    shape.setFillColor(color);
    shape.setPosition(pos);
    shape.setOrigin(shape.getSize()*0.5f);
}


int main(int argc, char** argv) {

    sf::RenderWindow window(sf::VideoMode(800, 800), "MicroMachines - Neon Edition");
    window.setFramerateLimit(60);
    AssetManager manager;
    sf::Clock clock;
    sf::Time deltaTime;
    sf::Time elapsedTime;
    
    sf::Vector2f startPos = sf::Vector2f(800, 500);

   
    bool* keys = new bool [256];
    
    for(int i = 0; i<256; i++)
        keys[i]=false;
    
    auto wSize = window.getSize();
    sf::View view(sf::FloatRect(0, 0, wSize.x, wSize.y));
    
    view.setCenter(startPos);
    window.setView(view);
    
    Player* player = new Player(startPos, manager);
    Enemy* IA = new Enemy(startPos, manager);
    
    sf::Sprite PISTA = sf::Sprite(AssetManager::GetTexture("Images/RACE.jpeg"));
    PISTA.setScale(3, 3);
    
    player->setKeys(keys);
    
    sf::Event event;
    float* dtAsSeconds = new float[1];
    player->setTime(dtAsSeconds);
    
    while (window.isOpen())
    {
        //Eventos
        deltaTime = clock.restart();
        elapsedTime += deltaTime;
        
        dtAsSeconds[0] = deltaTime.asSeconds();
        
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
        
        //Actualizar escena
                    
        player->movement();
        IA->logic();
        
        view.setCenter(player->getCar().getPosition());
        window.setView(view);
        //Renderizar ciclo
        
        //Renderizar objetos
            
        window.clear();
        window.draw(PISTA);
        window.draw(player->getCar());
        window.draw(IA->getCar());
        
        window.display();
        window.setMouseCursorVisible(false);
    }
    return 0;
}

