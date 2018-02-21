/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Car.h
 * Author: dan
 *
 * Created on 9 de febrero de 2018, 12:00
 */

#ifndef CAR_H
#define CAR_H

#include <SFML/System/Vector2.hpp>
#include "AssetManager.h"
#include <math.h> 
#include <iostream>

class Car {
    
protected:
    float MAXSPEED = 800;
    sf::Sprite car;
    float AC = 10;
    float SPEED = 0;
    float ROTATION = 300;
    const float PI = 3.14159265;
    float* dtAsSeconds = new float[1];
    sf::Vector2u* vertex;
    sf::Vector2u size;
    
public:
    Car();
    Car(const Car& orig);
    virtual ~Car();
    void setTime(float* s);
    sf::Sprite getCar();
    sf::Vector2u* getVertex();
};

#endif /* CAR_H */

