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
#include "SAT.h"

class Player : public Car {
private:
    sf::Vector2f dir;
    bool* keys;
    float ROTATION;
    
public:
    Player(std::string const& sprite_name, sf::Vector2f startPosition, float MAX_S, float acceleration, float rotation, float* dt, float r_speed, bool* keyboard);
    void movement();
    
};

#endif /* PLAYER_H */

