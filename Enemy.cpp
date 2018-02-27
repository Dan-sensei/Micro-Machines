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

Enemy::Enemy(sf::Vector2f startPos, float speed) {
    size = AssetManager::GetTexture("Images/HERO.jpg").getSize();
    Car::car = sf::Sprite( AssetManager::GetTexture("Images/HERO.jpg") );
    car.setPosition(startPos);
    MAXSPEED = speed;
    car.setOrigin(size.x*0.5f, size.y);
    incrementalRotation = 0;
    desiredRotation = 0;
    for (int i = 0; i< 9; i++)
        checkPoints[i] = false;
}

void Enemy::logic(){
    
    if(SPEED < MAXSPEED)        
        SPEED += AC;
    
    //std::cout << "desiredRotation: " << desiredRotation << std::endl;
    //std::cout << "incrementalRotation: " << incrementalRotation << std::endl;
   
    if(desiredRotation>0 && incrementalRotation < desiredRotation){
        incrementalRotation += 5;
        //std::cout << "Incrementing...: " << incrementalRotation << std::endl;
        car.rotate(5);
    }
    
    else if(desiredRotation < 0 && incrementalRotation > desiredRotation){
        incrementalRotation -= 5;
        car.rotate(-5);
    }
    
    if(incrementalRotation == desiredRotation){
        desiredRotation = 0;
        incrementalRotation = 0;
        collides = false;
    }
    
    
    sf::Vector2f dir = sf::Vector2f(sin(car.getRotation()*PI/180), -cos(car.getRotation()*PI/180));
    dir *= SPEED*dtAsSeconds[0];

    car.move(dir);
    
}

void Enemy::setDesiredRotation(float rot){
    desiredRotation = rot;
    collides = true;
}


void Enemy::setCheckPoint(int i, bool flag){
    checkPoints[i] = flag;
}

bool Enemy::getFlag(int i){
    return checkPoints[i];
}