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
    const float PI = 3.14159265;
    sf::Sprite car;
    sf::Vector2u size;
    
    float SPEED;
    float AC;
    float MAXSPEED;
    
    float* deltaTime;
    
    sf::Vector2f* vertex;
    
    int position;
    int* p_pos;
    int vueltas;
    
    bool checkPoints [12];
    bool visited [12];
    
public:
    Car(std::string const& sprite_name, sf::Vector2f startPosition, float MAX_S, float acceleration, float rotation, float* dt);
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
    
    int getVueltas();
};

#endif /* CAR_H */

