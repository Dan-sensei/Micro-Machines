/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Player.h
 * Author: dan
 *
 * Created on 9 de febrero de 2018, 12:25
 */

#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/System/Vector2.hpp>
#include "AssetManager.h"
#include "Car.h"

class Player : public Car {
private:
    sf::Vector2f dir;
    float AC = 17;
    float MAXSPEED = 1000;
    bool* keys = new bool [256];
public:
    Player(sf::Vector2f startPos);
    void movement();
    void setKeys(bool* k);
};

#endif /* PLAYER_H */

