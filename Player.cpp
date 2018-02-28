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
    size = AssetManager::GetTexture("Images/HERO.jpg").getSize();
    Car::car = sf::Sprite( AssetManager::GetTexture("Images/HERO.jpg") );
    
    MAXSPEED = 800;
    
    car.setOrigin(size.x*0.5f, size.y);
    car.setPosition(startPos);
    car.setRotation(0);
    
    vertex = new sf::Vector2f[4];
    vertex[0] = sf::Vector2f(car.getPosition().x - cos(car.getRotation()*PI/180) * (size.x*0.5), car.getPosition().y - sin(car.getRotation()*PI/180) * (size.x*0.5));
    vertex[1] = sf::Vector2f(car.getPosition().x + sin(car.getRotation()*PI/180) * size.y - cos(car.getRotation()*PI/180) * size.x*0.5, car.getPosition().y - sin(car.getRotation()*PI/180) * (size.x*0.5)-cos(car.getRotation()*PI/180) * size.y);
    vertex[2] = sf::Vector2f(car.getPosition().x + sin(car.getRotation()*PI/180) * size.y + cos(car.getRotation()*PI/180) * size.x*0.5, car.getPosition().y + sin(car.getRotation()*PI/180) * (size.x*0.5)-cos(car.getRotation()*PI/180) * size.y);
    vertex[3] = sf::Vector2f(car.getPosition().x + cos(car.getRotation()*PI/180) * (size.x*0.5), car.getPosition().y + sin(car.getRotation()*PI/180) * (size.x*0.5));
    
    std::cout << "Vertex 1: (" << vertex[0].x << ", " << vertex[0].y << ")" << std::endl;
    std::cout << "Vertex 2: (" << vertex[1].x << ", " << vertex[1].y << ")" << std::endl;
    std::cout << "Vertex 3: (" << vertex[2].x << ", " << vertex[2].y << ")" << std::endl;
    std::cout << "Vertex 4: (" << vertex[3].x << ", " << vertex[3].y << ")" << std::endl;
    
    position = 0;
    p_pos = &position;
    
    for (int i = 0; i< 12; i++){
        visited[i]=false;
        checkPoints[i] = false;
    }

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
    
    vertex[0] = sf::Vector2f(car.getPosition().x - cos(car.getRotation()*PI/180) * (size.x*0.5), car.getPosition().y - sin(car.getRotation()*PI/180) * (size.x*0.5));
    vertex[1] = sf::Vector2f(car.getPosition().x + sin(car.getRotation()*PI/180) * size.y - cos(car.getRotation()*PI/180) * size.x*0.5, car.getPosition().y - sin(car.getRotation()*PI/180) * (size.x*0.5)-cos(car.getRotation()*PI/180) * size.y);
    vertex[2] = sf::Vector2f(car.getPosition().x + sin(car.getRotation()*PI/180) * size.y + cos(car.getRotation()*PI/180) * size.x*0.5, car.getPosition().y + sin(car.getRotation()*PI/180) * (size.x*0.5)-cos(car.getRotation()*PI/180) * size.y);
    vertex[3] = sf::Vector2f(car.getPosition().x + cos(car.getRotation()*PI/180) * (size.x*0.5), car.getPosition().y + sin(car.getRotation()*PI/180) * (size.x*0.5));
    
    if(keys[4])
        SPEED = 0;
}

void Player::setKeys(bool* k){
    keys=k;
}

