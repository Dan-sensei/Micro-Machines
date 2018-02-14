/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Enemy.cpp
 * Author: dan
 * 
 * Created on 6 de febrero de 2018, 22:17
 */

#include <SFML/Graphics/Transformable.hpp>

#include "Enemy.h"

Enemy::Enemy(sf::Vector2f startPos) {
    Car::car = sf::Sprite( AssetManager::GetTexture("Images/275104-arrows.png") );
    car.setPosition(startPos);
}

void Enemy::logic(){
    car.move(5, 5);
}
