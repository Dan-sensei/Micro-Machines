/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: dan
 *
 * Created on 2 de febrero de 2018, 11:47
 */

#include <cstdlib>

#include "Game.h"

using namespace std;
/*
 * 
 */

int main(int argc, char** argv) {

    //JUGADORES HUMANOS [1, 2] , VUELTAS
    Game game(2, 2);
    game.go();
    
}

