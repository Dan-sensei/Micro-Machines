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

struct name{
        int pos;
        std::string nombre;
    };

void burbuja(name array[4]){
    name tmp;
    for (int i=1; i<5; i++)
        for (int j=0 ; j<5 - 1; j++){
            
            if (array[j].pos < array[j+1].pos){
                std::cout << " In "<<std::endl; 
                tmp = array[j];
                array[j] = array[j+1];
                array[j+1] = tmp;
            }

        }
}

int main(int argc, char** argv) {
    
    
    
    name test [4];
    test[0].nombre = "cero";
    test[0].pos = 0;
    
    test[1].nombre = "uno";
    test[1].pos = 0;
    
    test[2].nombre = "dos";
    test[2].pos = 0;
    
    test[3].nombre = "tres";
    test[3].pos = 0;
    
    for(int i = 0; i< 4; i++)
        std::cout << test[i].nombre << " " << test[i].pos << std::endl;
    
    std::cout << std::endl;
    
    burbuja(test);
    
    for(int i = 0; i< 4; i++)
        std::cout << test[i].nombre << " " << test[i].pos << std::endl;
    

    Game game;
    game.go();
}

