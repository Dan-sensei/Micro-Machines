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

