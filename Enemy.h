/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Enemy.h
 * Author: dan
 *
 * Created on 6 de febrero de 2018, 22:17
 */

#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/System/Vector2.hpp>
#include "AssetManager.h"
#include "Car.h"

class Enemy : public Car{
    private:
        float desiredRotation;
        float incrementalRotation;
        
    public:
        Enemy(std::string const& sprite_name, sf::Vector2f startPosition, float MAX_S, float acceleration, float rotation, float* dt);
        void setDesiredRotation(float rot);
        void logic();

};

#endif /* ENEMY_H */

