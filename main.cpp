/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: dan
 *
 * Created on 19 de marzo de 2018, 0:01
 */

#include <cstdlib>
#include "Game.h"

int main(int argc, char** argv) {
    
    //JUGADORES HUMANOS [1, 2] , VUELTAS
        Game game       (1     ,    2);
        game.go();

}

