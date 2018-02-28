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
    float MAXSPEED;
    sf::Sprite car;
    float AC = 10;
    float SPEED = 0;
    float ROTATION = 300;
    const float PI = 3.14159265;
    float* dtAsSeconds = new float[1];
    sf::Vector2f* vertex;
    sf::Vector2u size;
    int* p_pos;
    int position;
    bool checkPoints [12];
    bool visited [12];
    
    
public:
    Car();
    Car(const Car& orig);
    virtual ~Car();
    void setTime(float* s);
    sf::Sprite getCar();
    sf::Vector2f* getVertex();
    void incrementPosition(int pos);
    int getPosition();
    int* getP_pos();
    
    void setCheckPoint(int i, bool flag);
    bool getFlag(int i);
    
    void setVisited(int i);
    bool handleIncremenet(int i);
    void setPos(sf::Vector2f pos, sf::Vector2f axis);
};

#endif /* CAR_H */

