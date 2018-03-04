/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Enemy.cpp
 * Author: dan
 * 
 * Created on 6 de febrero de 2018, 22:17
 */

#include <SFML/Graphics/Transformable.hpp>

#include "Enemy.h"

Enemy::Enemy(std::string const& sprite_name, sf::Vector2f startPosition, float MAX_S, float acceleration, float rotation, float* dt) 
: Car(sprite_name, startPosition, MAX_S, acceleration, rotation, dt){
    incrementalRotation = 0;
    desiredRotation = 0;
}

void Enemy::logic(){
    
    if(SPEED < MAXSPEED)        
        SPEED += AC*deltaTime[0];

   
    if(desiredRotation>0 && incrementalRotation < desiredRotation){
        incrementalRotation += 5;
        car.rotate(5);
    }
    
    else if(desiredRotation < 0 && incrementalRotation > desiredRotation){
        incrementalRotation -= 5;
        car.rotate(-5);
    }
    
    if(incrementalRotation == desiredRotation){
        desiredRotation = 0;
        incrementalRotation = 0;
    }
    
    
    sf::Vector2f dir = sf::Vector2f(sin(car.getRotation()*PI/180) * SPEED, -cos(car.getRotation()*PI/180) * SPEED);

    car.move(dir*deltaTime[0]);
    
    vertex[0] = sf::Vector2f(car.getPosition().x - cos(car.getRotation()*PI/180) * (size.x*0.5), car.getPosition().y - sin(car.getRotation()*PI/180) * (size.x*0.5));
    vertex[1] = sf::Vector2f(car.getPosition().x + sin(car.getRotation()*PI/180) * size.y - cos(car.getRotation()*PI/180) * size.x*0.5, car.getPosition().y - sin(car.getRotation()*PI/180) * (size.x*0.5)-cos(car.getRotation()*PI/180) * size.y);
    vertex[2] = sf::Vector2f(car.getPosition().x + sin(car.getRotation()*PI/180) * size.y + cos(car.getRotation()*PI/180) * size.x*0.5, car.getPosition().y + sin(car.getRotation()*PI/180) * (size.x*0.5)-cos(car.getRotation()*PI/180) * size.y);
    vertex[3] = sf::Vector2f(car.getPosition().x + cos(car.getRotation()*PI/180) * (size.x*0.5), car.getPosition().y + sin(car.getRotation()*PI/180) * (size.x*0.5));

    
}

void Enemy::setDesiredRotation(float rot){
    desiredRotation += rot;

}


