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

using namespace std;

const float MAXSPEED = 550;
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
    
    int SPEED = 0; 
    
    sf::Vector2f startPos = sf::Vector2f(50, 50);
    sf::Sprite rectShape = sf::Sprite(AssetManager::GetTexture("Images/275104-arrows.png"));
    //initShape(rectShape, startPos, sf::Color::Yellow);
    rectShape.setPosition(startPos);
    rectShape.setScale(0.5, 0.5);
    rectShape.setOrigin(AssetManager::GetTexture("Images/275104-arrows.png").getSize().x*0.5f, AssetManager::GetTexture("Images/275104-arrows.png").getSize().y*0.9);
    //rectShape.setTexture(&pacmanTexture);

    sf::Sprite PISTA = sf::Sprite(AssetManager::GetTexture("Images/RACE.jpeg"));
    PISTA.setScale(3, 3);
    
    auto wSize = window.getSize();
    sf::View view(sf::FloatRect(0, 0, wSize.x, wSize.y));
    
    sf::Vector2f dir;
    view.setCenter(startPos);
    
    window.setView(view);
    
    bool keys [256] = {false};
    sf::Event event;
    float dtAsSeconds;
    
    while (window.isOpen())
    {
        //Eventos
        deltaTime = clock.restart();
        elapsedTime += deltaTime;
        
        dtAsSeconds = deltaTime.asSeconds();
        
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
            
        //       Q: 16
        //  Arriba: 73   |  W: 22
        //   Abajo: 74   |  S: 18
        //     Izq: 71   |  A: 0
        // Derecha: 72   |  D: 3
        
        
        
        if(SPEED > 0 && (keys[74] || keys[18])){           //ABAJO
            SPEED -= 10;
        }
        else if(SPEED < MAXSPEED && (keys[73] || keys[22])){      //ARRIBA
            SPEED += 10;
        }
       
        
        if(keys[71] || keys[0]){       //IZQUIERDA
            rectShape.rotate(-ROTATION*dtAsSeconds*SPEED*(1/MAXSPEED));
        }     
        else if(keys[72] || keys[3]){       //DERECHA
            rectShape.rotate(ROTATION*dtAsSeconds*SPEED*(1/MAXSPEED));
        }        
        
        std::cout << rectShape.getRotation() << std::endl;
        dir = sf::Vector2f(sin(rectShape.getRotation()*PI/180), -cos(rectShape.getRotation()*PI/180));
        dir *= SPEED*dtAsSeconds;
        
        rectShape.move(dir);
        
        view.setCenter(rectShape.getPosition());
        window.setView(view);
        //Renderizar ciclo
        
        //Renderizar objetos
            
        window.clear();
        window.draw(PISTA);
        window.draw(rectShape);
        
        window.display();
        window.setMouseCursorVisible(false);
    }
    return 0;
}

