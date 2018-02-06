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
#include <SFML/Graphics.hpp>

#include "AssetManager.h"

using namespace std;

/*
 * 
 */
void initShape(sf::RectangleShape& shape, sf::Vector2f const& pos, sf::Color const& color){
    shape.setFillColor(color);
    shape.setPosition(pos);
    shape.setOrigin(shape.getSize()*0.5f);
}


int main(int argc, char** argv) {

    sf::RenderWindow window(sf::VideoMode(800, 800), "Pacman");
    window.setFramerateLimit(60);
    AssetManager manager;
 
    
    
    sf::Vector2f startPos = sf::Vector2f(50, 50);
    sf::Sprite rectShape = sf::Sprite(AssetManager::GetTexture("Images/pacman.png"));
    //initShape(rectShape, startPos, sf::Color::Yellow);
    rectShape.setColor(sf::Color::Yellow);
    rectShape.setPosition(startPos);
    rectShape.setScale(0.5, 0.5);
    rectShape.setOrigin(AssetManager::GetTexture("Images/pacman.png").getSize().x*0.5f, AssetManager::GetTexture("Images/pacman.png").getSize().y*0.5f);
    //rectShape.setTexture(&pacmanTexture);
    
    sf::RectangleShape targetRect(sf::Vector2f(50, 50));
    initShape(targetRect, sf::Vector2f(400, 50), sf::Color::Blue);
    
    sf::RectangleShape badRect(sf::Vector2f(50, 100));
    initShape(badRect, sf::Vector2f(250, 50), sf::Color::Red);
    
    bool keys [256] = {false};
    
    while (window.isOpen())
    {
        //Eventos
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type){
                case sf::Event::EventType::Closed:
                    window.close();
                    break;
                    
                case sf::Event::EventType::KeyPressed:
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
        
        //  Arriba: 73   |  W: 22
        //   Abajo: 74   |  S: 18
        //     Izq: 71   |  A: 0
        // Derecha: 72   |  D: 3
        
        if(keys[74] || keys[18]){
            rectShape.move(0, 3);
            rectShape.setRotation(90);
        }
        else if(keys[73] || keys[22]){
            rectShape.move(0, -3);
            rectShape.setRotation(270);
        }
        
        else if(keys[71] || keys[0]){
            rectShape.move(-3, 0);
            rectShape.setRotation(180);
        }     
        else if(keys[72] || keys[3]){
            rectShape.move(3, 0);
            rectShape.setRotation(0);
        }
            
        
        if(rectShape.getGlobalBounds().intersects(targetRect.getGlobalBounds()))
            window.close();
        if(rectShape.getGlobalBounds().intersects(badRect.getGlobalBounds()))
            rectShape.setPosition(startPos);
        
        //Renderizar ciclo
        
        //Renderizar objetos
            
        window.clear();

        window.draw(targetRect);
        window.draw(badRect);
        window.draw(rectShape);

        window.display();
        window.setMouseCursorVisible(false);
    }
    return 0;
}

