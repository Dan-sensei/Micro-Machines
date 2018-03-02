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

Car::Car() {
}

Car::Car(const Car& orig) {
}

Car::~Car() {

}

sf::Sprite Car::getCar(){
    return car;
}
void Car::setTime(float* s){
    dtAsSeconds = s;
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

void Car::setPos(sf::Vector2f pos, sf::Vector2f axis){
    
    //Origin 66
    
    //float x =  car.getPosition().x -pos.x;
   //float y =  car.getPosition().y -pos.y ;
    
    car.move(pos.x, pos.y);
    
    std::cout << "Initial: " << car.getRotation() << std::endl;

        
    float x = cos((car.getRotation()-90)*PI/180);
    float y = -sin((car.getRotation()-90)*PI/180);
    float dot = 2 * (x*axis.x + y*axis.y);

    sf::Vector2f reflection = sf::Vector2f(x - dot * axis.x , y - dot * axis.y);
    float angle = atan2(reflection.x, reflection.y)*180/PI;

    dot = x * axis.x + y*axis.y;


    //if(abs(dot) < 0.72)
      //  car.setRotation(angle);

    SPEED -= SPEED*abs(dot)*0.08;

   // SPEED*=0.3;
}

int Car::getVueltas(){
    return vueltas;
}