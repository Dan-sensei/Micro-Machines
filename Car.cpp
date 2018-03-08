/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Car.cpp
 * Author: dan
 * 
 * Created on 9 de febrero de 2018, 12:00
 */

#include "Car.h"

Car::Car(std::string const& sprite_name, sf::Vector2f startPosition, float MAX_S, float acceleration, float rotation, float RootS, float* dt) {
    
    Car::car = sf::Sprite( AssetManager::GetTexture(sprite_name) );
    size = AssetManager::GetTexture(sprite_name).getSize();
    
    car.setOrigin(size.x*0.5f, size.y);
    car.setPosition(startPosition);
    car.setRotation(rotation);
    
    ROTATION = RootS;
    SPEED = 0;
    MAXSPEED = MAX_S;
    AC = acceleration; 
    onAir = false;
    
    vertex = new sf::Vector2f[4];
    vertex[0] = sf::Vector2f(car.getPosition().x - cos(car.getRotation()*PI/180) * (size.x*0.5), car.getPosition().y - sin(car.getRotation()*PI/180) * (size.x*0.5));
    vertex[1] = sf::Vector2f(car.getPosition().x + sin(car.getRotation()*PI/180) * size.y - cos(car.getRotation()*PI/180) * size.x*0.5, car.getPosition().y - sin(car.getRotation()*PI/180) * (size.x*0.5)-cos(car.getRotation()*PI/180) * size.y);
    vertex[2] = sf::Vector2f(car.getPosition().x + sin(car.getRotation()*PI/180) * size.y + cos(car.getRotation()*PI/180) * size.x*0.5, car.getPosition().y + sin(car.getRotation()*PI/180) * (size.x*0.5)-cos(car.getRotation()*PI/180) * size.y);
    vertex[3] = sf::Vector2f(car.getPosition().x + cos(car.getRotation()*PI/180) * (size.x*0.5), car.getPosition().y + sin(car.getRotation()*PI/180) * (size.x*0.5));
    
    position = 0;
    p_pos = &position;
    vueltas = 0;
    
    for (int i = 0; i< 12; i++){
        visited[i]=false;
        checkPoints[i] = false;
    }
    
    deltaTime = dt;
}

Car::Car(const Car& orig) {
}

Car::~Car() {
    delete vertex;
    delete p_pos;
    
    vertex = NULL;
    p_pos = NULL;
}

sf::Sprite Car::getCar(){
    return car;
}

sf::Vector2f* Car::getVertex(){
    return vertex;
}

void Car::incrementPosition(int pos){
    position += pos;
}

int Car::getPosition(){
    return position;
}

void Car::setCheckPoint(int i, bool flag){
    checkPoints[i] = flag;
}

bool Car::getFlag(int i){
    return checkPoints[i];
}

void Car::setVisited(int i){
    visited[i] = true;
}

bool Car::handleIncremenet(int i){
        
    if(position != 0 && position % 12 == 0){
        std::cout  << "VUELTA!" << std::endl;
        vueltas++;
        for (int i = 0; i< 12; i++)
            visited[i]=false;
    }
    
    return (i== 0 && !visited[0]) ? true : (!visited[i] && visited[i-1]) ? true: false;
}

int* Car::getP_pos(){
    return p_pos;
}

void Car::handleHitboxCollision(sf::Vector2f pos, sf::Vector2f axis){
    
    //Origin 66
    
    //float x =  car.getPosition().x -pos.x;
   //float y =  car.getPosition().y -pos.y ;
    
    car.move(pos.x, pos.y);
    
    //std::cout << "Initial: " << car.getRotation() << std::endl;

        
    float x = cos((car.getRotation()-90)*PI/180);
    float y = -sin((car.getRotation()-90)*PI/180);
    //float dot = 2 * (x*axis.x + y*axis.y);

    //sf::Vector2f reflection = sf::Vector2f(x - dot * axis.x , y - dot * axis.y);
    //float angle = atan2(reflection.x, reflection.y)*180/PI;

    float dot = x * axis.x + y*axis.y;
    
    //if(abs(dot) < 0.72)
      //  car.setRotation(angle);

    SPEED -= SPEED*abs(dot)*0.3;
}

void Car::handlePlayersCollision(sf::Vector2f pos, sf::Vector2f axis){
    car.move(pos.x, pos.y);

    SPEED -= SPEED*0.1;
}

int Car::getVueltas(){
    return vueltas;
}

void Car::interpola(float x, float y, float r){
    car.setPosition(x, y);
    car.setRotation(r);
}

bool Car::isOnAir(){
    return onAir;
}

void Car::setAir(bool set){
    onAir = set;
}

void Car::setSpeed(float s){
    SPEED = s;
}