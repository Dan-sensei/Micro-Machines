/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SAT.cpp
 * Author: dan
 * 
 * Created on 2 de marzo de 2018, 20:33
 */

#include <vector>
#include "SAT.h"

SAT::SAT() {
}

SAT::SAT(const SAT& orig) {
}

SAT::~SAT() {
}

//Separation Axis Theorem - Guía seguida: http://www.dyn4j.org/2010/01/sat/
SAT::MTV SAT::collides(sf::Vector2f* target, sf::Vector2f* vertex){
    MTV mtv;
    mtv.collides = false;

    double THE_OVERLAP = 100000000;
    sf::Vector2f MINIMUM;
    double tmp;
    std::vector<sf::Vector2f> finalEdges;
    getNormals(finalEdges, target);
    getNormals(finalEdges, vertex);
    sf::Vector2<double> pPlayer;
    sf::Vector2<double> pHitbox;
    
    for(std::vector<sf::Vector2f>::iterator edge = finalEdges.begin(); edge != finalEdges.end(); ++edge){
        pPlayer = projection(*edge, target);
        pHitbox = projection(*edge, vertex);
        
        if(!ItOverlaps(pPlayer, pHitbox)){
            return mtv;
        }
        else{
            tmp = overlapDistance(pPlayer, pHitbox);
            if(tmp < THE_OVERLAP){
                THE_OVERLAP = tmp;
                MINIMUM = *edge;
            }
        }
    }
    
    mtv.collides = true;
    mtv.axis = sf::Vector2f(abs(MINIMUM.x), abs(MINIMUM.y));
    mtv.amount = THE_OVERLAP;
    return mtv;
}

void SAT::getNormals(std::vector<sf::Vector2f>& finalEdges, sf::Vector2f* vertex){
    
    sf::Vector2f normal;
    sf::Vector2f first;
    sf::Vector2f next;
    sf::Vector2f edge;
    
    for (int i = 0; i < 2; i++){
        first = vertex[i];
        next = vertex[i+1==4 ? 0 : i+1];
        edge = sf::Vector2f(next.x - first.x, next.y - first.y);
        normal = sf::Vector2f(-edge.y, edge.x);
        finalEdges.push_back(normalize(normal));
    }
}

sf::Vector2<double> SAT::projection(sf::Vector2f edge, sf::Vector2f* vertex){
    sf::Vector2<double> p;
    
    double min;
    double max;
    double tmp;
    min = edge.x * vertex[0].x + edge.y * vertex[0].y;
    max= min;
    //std::cout << "NV: " << nv << std::endl;
    for(int i=1; i< 4; i++){   
        tmp = edge.x * vertex[i].x + edge.y * vertex[i].y;
        if(tmp>=max)
            max = tmp;
        else if(tmp < min)
            min = tmp;
    }
    p= sf::Vector2<double>(min, max);

    return p;
}

bool SAT::ItOverlaps(sf::Vector2<double> p1, sf::Vector2<double> p2){
    if(p1.x > p2.y || p2.x > p1.y)
        return false;
    return true;
}

float SAT::overlapDistance(sf::Vector2<double> p1, sf::Vector2<double> p2){
    float x;  
    x = (p1.y < p2.y) ? p1.y -p2.x : p2.y - p1.x;
    return x;
}

sf::Vector2f SAT::normalize(sf::Vector2f vector){
    sf::Vector2f normalized;
    double unit;
    unit = sqrt(vector.x * vector.x + vector.y * vector.y);
    normalized = sf::Vector2f(vector.x/unit, vector.y/unit);
    return normalized;
}