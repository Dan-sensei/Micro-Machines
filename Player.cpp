/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Player.cpp
 * Author: dan
 * 
 * Created on 9 de febrero de 2018, 12:25
 */

#include "Player.h"

Player::Player(std::string const& sprite_name, sf::Vector2f startPosition, float MAX_S, float acceleration, float rotation, float* dt, float r_speed, bool* keyboard)
:Car(sprite_name, startPosition, MAX_S, acceleration, rotation, dt)
{
    ROTATION = r_speed;
    keys = keyboard;
    std::cout << "Vertex 1: (" << vertex[0].x << ", " << vertex[0].y << ")" << std::endl;
    std::cout << "Vertex 2: (" << vertex[1].x << ", " << vertex[1].y << ")" << std::endl;
    std::cout << "Vertex 3: (" << vertex[2].x << ", " << vertex[2].y << ")" << std::endl;
    std::cout << "Vertex 4: (" << vertex[3].x << ", " << vertex[3].y << ")" << std::endl;
}

void Player::movement(sf::Vector2f& position, float& speed, float& rotation) {
    
    //       Q: 16
    //  Arriba: 73   |  W: 22
    //   Abajo: 74   |  S: 18
    //     Izq: 71   |  A: 0
    // Derecha: 72   |  D: 3   
    
    std::cout << "SPEED " << SPEED << std::endl;
    std::cout << "DT " << deltaTime[0] << std::endl;

    if(SPEED > -MAXSPEED && (keys[74] || keys[18])){           //ABAJO
        SPEED -= AC*deltaTime[0];
    }
    else if(SPEED < MAXSPEED && (keys[73] || keys[22])){      //ARRIBA
        SPEED += AC*deltaTime[0];
    }

    
    if(keys[71] || keys[0]){       //IZQUIERDA
        car.rotate(-ROTATION*deltaTime[0]*SPEED*(1/MAXSPEED));
    }     
    else if(keys[72] || keys[3]){       //DERECHA
        car.rotate(ROTATION*deltaTime[0]*SPEED*(1/MAXSPEED));
    }        
    
    dir = sf::Vector2f(sin(car.getRotation()*PI/180) * SPEED, -cos(car.getRotation()*PI/180) * SPEED);

    //std::cout << "Speed: " << SPEED << " | Dir: " << dir.x << ", " << dir.y << std::endl;
    
    car.move(dir*deltaTime[0]);
    
    //std::cout << "deltaTime: " << deltaTime[0] << std::endl;
    //car.move(dir);
    
    vertex[0] = sf::Vector2f(car.getPosition().x - cos(car.getRotation()*PI/180) * (size.x*0.5), car.getPosition().y - sin(car.getRotation()*PI/180) * (size.x*0.5));
    vertex[1] = sf::Vector2f(car.getPosition().x + sin(car.getRotation()*PI/180) * size.y - cos(car.getRotation()*PI/180) * size.x*0.5, car.getPosition().y - sin(car.getRotation()*PI/180) * (size.x*0.5)-cos(car.getRotation()*PI/180) * size.y);
    vertex[2] = sf::Vector2f(car.getPosition().x + sin(car.getRotation()*PI/180) * size.y + cos(car.getRotation()*PI/180) * size.x*0.5, car.getPosition().y + sin(car.getRotation()*PI/180) * (size.x*0.5)-cos(car.getRotation()*PI/180) * size.y);
    vertex[3] = sf::Vector2f(car.getPosition().x + cos(car.getRotation()*PI/180) * (size.x*0.5), car.getPosition().y + sin(car.getRotation()*PI/180) * (size.x*0.5));
    
    if(keys[4])         //E
        SPEED = 0;
    
    position = car.getPosition();
    speed = SPEED;
    rotation = car.getRotation();
}

