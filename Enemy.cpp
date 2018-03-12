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
: Car(sprite_name, startPosition, MAX_S, acceleration, rotation, 270, dt){
    incrementalRotation = 0;
    desiredRotation = 0;
}

void Enemy::logic(){

    if(SPEED < MAXSPEED)        
        SPEED += AC*deltaTime[0];

    //std::cout << "desiredRotation " << desiredRotation<<std::endl;
    //std::cout << "car " << car.getRotation()<<std::endl;
    
 
    float a = desiredRotation - car.getRotation() ;
    while (a < -180) a += 360;
    while (a > 180) a -= 360;

    
    if(a > 0)
        car.rotate(ROTATION*deltaTime[0]);
    
    else if(a<0)
        car.rotate(-ROTATION*deltaTime[0]);
        
    
    if(abs(desiredRotation - car.getRotation()) < 15)
        car.setRotation(desiredRotation);

    sf::Vector2f dir = sf::Vector2f(sin(car.getRotation()*PI/180) * SPEED, -cos(car.getRotation()*PI/180) * SPEED);
    car.move(dir*deltaTime[0]);
    
    if(SPEED > MAXSPEED)
        SPEED -= 900*deltaTime[0];
    else if(SPEED < -MAXSPEED)
        SPEED += 900*deltaTime[0];
    
    
    if(onAir && !weReGoingDown && car.getScale().x < maxSize){
        car.setScale(car.getScale().x+deltaTime[0], car.getScale().y+deltaTime[0]);
        if(car.getScale().x > maxSize)
            weReGoingDown = true;
    }
    if (weReGoingDown && car.getScale().x > 1){
        car.setScale(car.getScale().x-deltaTime[0], car.getScale().y-deltaTime[0]);
    }
    
    if(car.getScale().x < 1){
        onAir = false;
        weReGoingDown = false;
        car.setScale(1, 1);
    }
    
    vertex[0] = sf::Vector2f(car.getPosition().x - cos(car.getRotation()*PI/180) * (size.x*0.5), car.getPosition().y - sin(car.getRotation()*PI/180) * (size.x*0.5));
    vertex[1] = sf::Vector2f(car.getPosition().x + sin(car.getRotation()*PI/180) * size.y - cos(car.getRotation()*PI/180) * size.x*0.5, car.getPosition().y - sin(car.getRotation()*PI/180) * (size.x*0.5)-cos(car.getRotation()*PI/180) * size.y);
    vertex[2] = sf::Vector2f(car.getPosition().x + sin(car.getRotation()*PI/180) * size.y + cos(car.getRotation()*PI/180) * size.x*0.5, car.getPosition().y + sin(car.getRotation()*PI/180) * (size.x*0.5)-cos(car.getRotation()*PI/180) * size.y);
    vertex[3] = sf::Vector2f(car.getPosition().x + cos(car.getRotation()*PI/180) * (size.x*0.5), car.getPosition().y + sin(car.getRotation()*PI/180) * (size.x*0.5));

    
}

void Enemy::setDesiredRotation(float rot){
    desiredRotation = rot;

}


