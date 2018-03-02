/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SAT.h
 * Author: dan
 *
 * Created on 2 de marzo de 2018, 20:33
 */

#ifndef SAT_H
#define SAT_H

#include <SFML/System/Vector2.hpp>
#include <math.h>

class SAT {
public:
    SAT();
    SAT(const SAT& orig);
    virtual ~SAT();

    struct MTV{
        bool collides;
        sf::Vector2f mtv;
    };

public:
    MTV collides(sf::Vector2f* target, sf::Vector2f* vertex);
    sf::Vector2f normalize(sf::Vector2f vector);
private:
    void getNormals(std::vector<sf::Vector2f>& finalEdges, sf::Vector2f* vertex);
    sf::Vector2<double> projection(sf::Vector2f edge, sf::Vector2f* vertex);
    bool ItOverlaps(sf::Vector2<double> p1, sf::Vector2<double> p2);
    float overlapDistance(sf::Vector2<double> p1, sf::Vector2<double> p2);
        
};

#endif /* SAT_H */

