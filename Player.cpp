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

Player::Player(sf::Vector2f startPos) {
    Car::car = sf::Sprite( AssetManager::GetTexture("Images/275104-arrows.png") );
    car.setScale(0.5, 0.5);
    car.setOrigin(AssetManager::GetTexture("Images/275104-arrows.png").getSize().x*0.5f, AssetManager::GetTexture("Images/275104-arrows.png").getSize().y*0.9);
    car.setPosition(startPos);
}

void Player::movement() {
    
    //       Q: 16
    //  Arriba: 73   |  W: 22
    //   Abajo: 74   |  S: 18
    //     Izq: 71   |  A: 0
    // Derecha: 72   |  D: 3   
    
    //std::cout << "SPEED " << SPEED << std::endl;
    if(SPEED > -MAXSPEED && (keys[74] || keys[18])){           //ABAJO
        SPEED -= AC;
    }
    else if(SPEED < MAXSPEED && (keys[73] || keys[22])){      //ARRIBA
        SPEED += AC;
    }


    if(keys[71] || keys[0]){       //IZQUIERDA
        car.rotate(-ROTATION*dtAsSeconds[0]*SPEED*(1/MAXSPEED));
    }     
    else if(keys[72] || keys[3]){       //DERECHA
        car.rotate(ROTATION*dtAsSeconds[0]*SPEED*(1/MAXSPEED));
    }        
    
    dir = sf::Vector2f(sin(car.getRotation()*PI/180), -cos(car.getRotation()*PI/180));
    dir *= SPEED*dtAsSeconds[0];

    car.move(dir);
}

void Player::setKeys(bool* k){
    keys=k;
}