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
    size = AssetManager::GetTexture("Images/Enemy.jpg").getSize();
    Car::car = sf::Sprite( AssetManager::GetTexture("Images/Enemy.jpg") );
    car.setPosition(startPos);
    MAXSPEED = speed;
    car.setOrigin(size.x*0.5f, size.y);
    incrementalRotation = 0;
    desiredRotation = 0;
    for (int i = 0; i< 12; i++){
        visited[i]=false;
        checkPoints[i] = false;
    }
    position = 0;
    p_pos = &position;
    
    vertex = new sf::Vector2f[4];
    vertex[0] = sf::Vector2f(car.getPosition().x - cos(car.getRotation()*PI/180) * (size.x*0.5), car.getPosition().y - sin(car.getRotation()*PI/180) * (size.x*0.5));
    vertex[1] = sf::Vector2f(car.getPosition().x + sin(car.getRotation()*PI/180) * size.y - cos(car.getRotation()*PI/180) * size.x*0.5, car.getPosition().y - sin(car.getRotation()*PI/180) * (size.x*0.5)-cos(car.getRotation()*PI/180) * size.y);
    vertex[2] = sf::Vector2f(car.getPosition().x + sin(car.getRotation()*PI/180) * size.y + cos(car.getRotation()*PI/180) * size.x*0.5, car.getPosition().y + sin(car.getRotation()*PI/180) * (size.x*0.5)-cos(car.getRotation()*PI/180) * size.y);
    vertex[3] = sf::Vector2f(car.getPosition().x + cos(car.getRotation()*PI/180) * (size.x*0.5), car.getPosition().y + sin(car.getRotation()*PI/180) * (size.x*0.5));

    
}

void Enemy::logic(){
    
    if(SPEED < MAXSPEED)        
        SPEED += AC;

   
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
    
    
    sf::Vector2f dir = sf::Vector2f(sin(car.getRotation()*PI/180), -cos(car.getRotation()*PI/180));
    dir *= SPEED*dtAsSeconds[0];

    car.move(dir);
    
    vertex[0] = sf::Vector2f(car.getPosition().x - cos(car.getRotation()*PI/180) * (size.x*0.5), car.getPosition().y - sin(car.getRotation()*PI/180) * (size.x*0.5));
    vertex[1] = sf::Vector2f(car.getPosition().x + sin(car.getRotation()*PI/180) * size.y - cos(car.getRotation()*PI/180) * size.x*0.5, car.getPosition().y - sin(car.getRotation()*PI/180) * (size.x*0.5)-cos(car.getRotation()*PI/180) * size.y);
    vertex[2] = sf::Vector2f(car.getPosition().x + sin(car.getRotation()*PI/180) * size.y + cos(car.getRotation()*PI/180) * size.x*0.5, car.getPosition().y + sin(car.getRotation()*PI/180) * (size.x*0.5)-cos(car.getRotation()*PI/180) * size.y);
    vertex[3] = sf::Vector2f(car.getPosition().x + cos(car.getRotation()*PI/180) * (size.x*0.5), car.getPosition().y + sin(car.getRotation()*PI/180) * (size.x*0.5));

    
}

void Enemy::setDesiredRotation(float rot){
    desiredRotation = rot;

}


