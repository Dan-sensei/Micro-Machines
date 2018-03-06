/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Game.cpp
 * Author: dan
 * 
 * Created on 13 de febrero de 2018, 15:36
 */

#include <SFML/Window/Event.hpp>
#include <iostream>

#include "Game.h"

#define TICK 1000/30

Game::Game(int N, int IA):
window(sf::VideoMode(1200, 900), "MicroMachines - Neon Edition")
{
    //Sat = new SAT();
    N_PLAYERS = N;
    N_IA = IA;
    window.setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width/2 -600, 50));
    
    UI = sf::View(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
    
    view = sf::View(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y/2));
    view.setViewport(sf::FloatRect(0, 0, 1, 0.5f));
    
    view2 = sf::View(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y/2));
    view2.setViewport(sf::FloatRect(0, 0.5f , 1, 0.5f));
    
    window.setFramerateLimit(60);
    window.setMouseCursorVisible(false);
    
    sf::Vector2f startPos = sf::Vector2f(400, 1800);
    Cool_Map = sf::Sprite (AssetManager::GetTexture("Images/New.jpg")); 

    UI.setCenter(startPos);
    view.setCenter(startPos);
    view.zoom(1.3);
    view2.zoom(1.3);
    view2.setCenter(startPos);
    window.setView(view);  
    
    keys = new bool[256];
    for(int i = 0; i<256; i++)
        keys[i]=false;
    
    dtAsSeconds = new float[1];
    //sprite_name, startPosition, MAX_SPEED, acceleration, Initial_rotation, deltaTime, rotation_speed, keyboard
    
    player = new Player("Images/HERO.jpg", startPos, 1000, 900, 0, dtAsSeconds, 220, keys);
    IAs[0] = new Enemy("Images/Enemy.jpg", sf::Vector2f(80, 1600), 1000, 1000, 0, dtAsSeconds); //1000
    IAs[1] = new Enemy("Images/Enemy.jpg", sf::Vector2f(150, 1700), 950, 900, 0, dtAsSeconds);  //900
    IAs[2] = new Enemy("Images/Enemy.jpg", sf::Vector2f(180, 1650), 1000, 1000, 0, dtAsSeconds);    //1000
    IAs[3] = new Enemy("Images/Enemy.jpg", sf::Vector2f(200, 1420), 980, 950, 0, dtAsSeconds);  //950
    
    Light = sf::Color(247, 233, 212);
    Dark = sf::Color(41, 39, 34);

    //HITBOX DEL MAPA
                         //    TAMAÑO                    POSICION       ROTACION X  Y  FACE
    hit[0] = createHitbox(sf::Vector2f(1000, 3000), sf::Vector2f(-1000, 800), 0, 1, 1, false, 0);
    hit[1] = createHitbox(sf::Vector2f(1000, 2000), sf::Vector2f(474, -820), 45, 1, 1, false, 0);
    hit[2] = createHitbox(sf::Vector2f(5000, 1000), sf::Vector2f(800, -1000), 0, 1, 1, false, 0);
    hit[3] = createHitbox(sf::Vector2f(1000, 2000), sf::Vector2f(7366, 250), 135, -1, 1, false, 0);
    hit[4] = createHitbox(sf::Vector2f(1000, 3200), sf::Vector2f(6403, 550), 0, -1, 1, false, 0);
    hit[5] = createHitbox(sf::Vector2f(1000, 2000), sf::Vector2f(6800, 3128), 45, -1, -1, false, 0);
    hit[6] = createHitbox(sf::Vector2f(3800, 1000), sf::Vector2f(2000, 4352), 0, 1, -1, false, 0);
    hit[7] = createHitbox(sf::Vector2f(2200, 1200), sf::Vector2f(-78, 3286), 0, 1, -1, false, 0);
    hit[8] = createHitbox(sf::Vector2f(4752, 1394), sf::Vector2f(583, 1308), 0, -1, 1, false, 0);
    hit[9] = createHitbox(sf::Vector2f(1025.304833, 800), sf::Vector2f(583, 1308), -45, -1, -1, false, 0);
    hit[10] = createHitbox(sf::Vector2f(4152, 1000), sf::Vector2f(1308, 583), 0, 1, -1, false, 0); 
    hit[11] = createHitbox(sf::Vector2f(509.1168825, 800), sf::Vector2f(5460, 583), 45, 1, -1, false, 0);
    hit[12] = createHitbox(sf::Vector2f(485, 2341), sf::Vector2f(5335, 943), 0, 1, 1, false, 0); 
    hit[13] = createHitbox(sf::Vector2f(685.89357785, 500), sf::Vector2f(5820, 3284), 135, 1, 1, false, 0);   
    hit[14] = createHitbox(sf::Vector2f(2630, 1067), sf::Vector2f(2705, 2702), 0, -1, 1, false, 0);
    
    //PUNTOS DE CONTROL
    control = new item [12];
    control[0] = createHitbox(sf::Vector2f(583, 5), sf::Vector2f(291.5, 1308), 0, 1, 1, true, 45);
    control[1] = createHitbox(sf::Vector2f(5, 583), sf::Vector2f(1308, 291.5), 0, 1, 1, true, 45);
    control[2] = createHitbox(sf::Vector2f(5, 583), sf::Vector2f(5460, 291.5), 0, 1, 1, true, 45);
    control[3] = createHitbox(sf::Vector2f(583, 5), sf::Vector2f(6111.5, 943), 0, 1, 1, true, 45);
    control[4] = createHitbox(sf::Vector2f(583, 5), sf::Vector2f(6111.5, 3284), 0, 1, 1, true, 45);
    control[5] = createHitbox(sf::Vector2f(5, 583), sf::Vector2f(5335, 4060.5), 0, 1, 1, true, 45);
    control[6] = createHitbox(sf::Vector2f(5, 583), sf::Vector2f(2705, 4060.5), 0, 1, 1, true, 45);
    control[7] = createHitbox(sf::Vector2f(583, 5), sf::Vector2f(2413.5, 3769), 0, 1, 1, true, 45);
    control[8] = createHitbox(sf::Vector2f(583, 5), sf::Vector2f(2413.5, 3286), 0, 1, 1, true, -45);
    control[9] = createHitbox(sf::Vector2f(5, 583), sf::Vector2f(2121, 2994.5), 0, 1, 1, true, -45);
    control[10] = createHitbox(sf::Vector2f(5, 583), sf::Vector2f(583, 2994.5), 0, 1, 1, true, 45);
    control[11] = createHitbox(sf::Vector2f(583, 5), sf::Vector2f(291.5, 2702), 0, 1, 1, true, 45);
  
    
    std::string text;
    for(int i = 0; i < N_IA; i++){
        text = "IA #"+std::to_string(i+1);
        leaderboard[i].nombre = text;
        leaderboard[i].posicion = IAs[i]->getP_pos();
        leaderboard[i].target = IAs[i];
        leaderboard[i].id = sf::Text(text, AssetManager::GetFont("Fonts/LemonMilk.otf"));
        
        actual[i].position = previous[i].position = IAs[i]->getCar().getPosition();
        actual[i].rotation = previous[i].rotation = 0;
    }
    
    actual[4].position = previous[4].position = player->getCar().getPosition();
    actual[4].rotation = previous[4].rotation = 0;
        
    leaderboard[4].nombre = "Player";
    leaderboard[4].posicion = player->getP_pos();
    leaderboard[4].target = player;
    leaderboard[4].id = sf::Text("Player", AssetManager::GetFont("Fonts/LemonMilk.otf"));  
    
}

Game::~Game() {
}

void Game::go(){
    //masterClock.restart();
    while(window.isOpen()){
        handleEvents();
        //std::cout << "TIME: " << masterClock.getElapsedTime().asMilliseconds() << std::endl;
        if(masterClock.getElapsedTime().asMilliseconds() > TICK){
            update();
        }
        
        float tick = fmin(1.0f, ((float)(masterClock.getElapsedTime().asMilliseconds())/(float)(TICK)));

        render(tick);
    }
}

void Game::handleEvents(){
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type){

            case sf::Event::EventType::Closed:
                window.close();
                break;

            case sf::Event::EventType::KeyPressed:
                std::cout<< "Tecla " << event.key.code << std::endl;
                keys[event.key.code]= true;
                if(keys[16]) window.close();        //Cerrar
                break;

            case sf::Event::KeyReleased:
                keys[event.key.code]= false;
                break;

            default:
                break;
        }
    }
}

void Game::update(){                                                // <--------------------------------------------------------- UPDATE
    std::cout << "UPDATE -- " << std::endl;
    /* REINICIO EL RELOJ */
    deltaTime = masterClock.restart();
    elapsedTime += deltaTime;
    dtAsSeconds[0] = deltaTime.asSeconds();
            
    /* SOBRESCRIBO LOS DATOS ANTERIORES */
    for(int i = 0; i < (N_PLAYERS + N_IA); i++) {
        previous[i] = actual[i];
    }
    
    /* MOVIMIENTO Y LÓGICA */
    player->movement(); 
    for(int i= 0; i<4; i++)
        IAs[i]->logic();
   
    /* COLISIONES */
    checkPoints();
    checkCollisionsBetweeenHitbox();
    checkCollisionsBetweeenPlayers();
    burbuja();
    
    /* ACTUALIZO LA POSICIÓN SIGUIENTE */
    actual[4].position = player->getCar().getPosition();
    actual[4].rotation = player->getCar().getRotation();

    for(int i = 0; i < N_IA; i++){
        actual[i].position = IAs[i]->getCar().getPosition();
        actual[i].rotation = IAs[i]->getCar().getRotation();
    }
    
    if(player->getVueltas() == 2){
        window.close();
    }
    
}

void Game::render(float tick){                                       // <--------------------------------------------------------- RENDER
    std::cout << "RENDER -- " << std::endl;
    window.clear(Dark);
    

    
    window.setView(view);
    window.draw(Cool_Map);
    
    window.draw(leaderboard[0].id);
    window.draw(leaderboard[1].id);
    window.draw(leaderboard[2].id);
    window.draw(leaderboard[3].id);
    window.draw(leaderboard[4].id);
    
    rendercontrol();
    renderPlayers(tick);
   
    window.setView(view2);
    window.draw(Cool_Map);
    renderPlayers2(tick);
    
    window.draw(player->getCar());
    player->interpola(actual[4].position.x, actual[4].position.y, actual[4].rotation);
    
    window.setView(UI);
    /* POSICIONES EN LA CARRERA */
    leaderboard[0].id.setPosition(sf::Vector2f(20, 450));
    leaderboard[1].id.setPosition(sf::Vector2f(20, 400));
    leaderboard[2].id.setPosition(sf::Vector2f(20, 350));
    leaderboard[3].id.setPosition(sf::Vector2f(20, 300));
    leaderboard[4].id.setPosition(sf::Vector2f(20, 250));

   
    window.display();
}

void Game::rendercontrol(){
    for(int i=0; i< 12; i++){
        
        window.draw(control[i].figure);
    }
}

void Game::renderPlayers(float tick){
    
    float x;
    float y;
    float c;
    float s;

    for(int i = 0; i < N_PLAYERS; i++){
        x = previous[4].position.x *(1-tick) + actual[4].position.x*tick;
        y = previous[4].position.y *(1-tick) + actual[4].position.y*tick;
        c = cos(previous[4].rotation *PI/180) * (1-tick) + cos(actual[4].rotation*PI/180)*tick;
        s = sin(previous[4].rotation *PI/180) * (1-tick) + sin(actual[4].rotation*PI/180)*tick;

        //std::cout << "Tick " << tick << std::endl; 
        //std::cout << "Previous: " << previous[4].position.x << ", " << previous[4].position.y << " | Actual: " << actual[4].position.x << ", " << actual[4].position.y << std::endl;
        //std::cout << "Interpolated -----: " << x << ", " << y << std::endl;
        player->interpola(x, y, atan2(s,c)*180/PI);  
        view.setCenter(player->getCar().getPosition());
        window.setView(view);
        window.draw(player->getCar());
        //std::cout << "CAR ----- " << player->getCar().getPosition().x << ", " << player->getCar().getPosition().y << std::endl << std::endl;
    }

    for(int i=0; i< N_IA; i++){
        x = previous[i].position.x *(1-tick) + actual[i].position.x*tick;
        y = previous[i].position.y *(1-tick) + actual[i].position.y*tick;
        c = cos(previous[i].rotation *PI/180) * (1-tick) + cos(actual[i].rotation*PI/180)*tick;
        s = sin(previous[i].rotation *PI/180) * (1-tick) + sin(actual[i].rotation*PI/180)*tick;
        
        IAs[i]->interpola(x, y, atan2(s,c)*180/PI);
        window.draw(IAs[i]->getCar());
        IAs[i]->interpola(actual[i].position.x, actual[i].position.y, actual[i].rotation);
    }
        
}

void Game::renderPlayers2(float tick){
    
    float x;
    float y;
    float c;
    float s;

    for(int i=0; i< N_IA; i++){
        x = previous[i].position.x *(1-tick) + actual[i].position.x*tick;
        y = previous[i].position.y *(1-tick) + actual[i].position.y*tick;
        c = cos(previous[i].rotation *PI/180) * (1-tick) + cos(actual[i].rotation*PI/180)*tick;
        s = sin(previous[i].rotation *PI/180) * (1-tick) + sin(actual[i].rotation*PI/180)*tick;
        
        IAs[i]->interpola(x, y, atan2(s,c)*180/PI);
        if(i==0){
            view2.setCenter(IAs[0]->getCar().getPosition());
            window.setView(view2);
        }
        window.draw(IAs[i]->getCar());
        IAs[i]->interpola(actual[i].position.x, actual[i].position.y, actual[i].rotation);
    }
    
    for(int i = 0; i < N_PLAYERS; i++){
        x = previous[4].position.x *(1-tick) + actual[4].position.x*tick;
        y = previous[4].position.y *(1-tick) + actual[4].position.y*tick;
        c = cos(previous[4].rotation *PI/180) * (1-tick) + cos(actual[4].rotation*PI/180)*tick;
        s = sin(previous[4].rotation *PI/180) * (1-tick) + sin(actual[4].rotation*PI/180)*tick;
        
        player->interpola(x, y, atan2(s,c)*180/PI);  
    }

        
}

void Game::checkPoints(){
   
    int j;
    for(int i=0; i<4; i++){

        j = IAs[i]->getPosition() % 12;
        if(IAs[i]->getCar().getGlobalBounds().intersects(control[j].figure.getGlobalBounds()) && !IAs[i]->getFlag(j) && IAs[i]->handleIncremenet(j)){
            
            IAs[i]->setDesiredRotation(control[j].newRotation);
            IAs[i]->setCheckPoint(j, true);
            IAs[i]->setVisited(j);
            IAs[i]->incrementPosition(1);
        }
        else if(!(IAs[i]->getCar().getGlobalBounds().intersects(control[j].figure.getGlobalBounds()))){
            IAs[i]->setCheckPoint(j, false);
        }
    }
    
    j = player->getPosition() % 12;
    if(player->getCar().getGlobalBounds().intersects(control[j].figure.getGlobalBounds()) && !player->getFlag(j) && player->handleIncremenet(j)){
         player->setCheckPoint(j, true);
         player->setVisited(j);
         player->incrementPosition(1);

     }
     else if(!(player->getCar().getGlobalBounds().intersects(control[j].figure.getGlobalBounds())))
         player->setCheckPoint(j, false);    
}

void Game::checkCollisionsBetweeenHitbox(){
    /* PARA CADA COLLIDER */
    for(int i = 0; i < 15; i++){
        
        /* PARA CADA JUGADOR */
        for(int j = 0; j<N_PLAYERS ; j++){
            if((Sat_result = Sat.collides(player->getVertex(), hit[i].vertex)).collides){
                Sat_result.axis.x = hit[i].sx * abs(Sat_result.axis.x);
                Sat_result.axis.y = hit[i].sy * abs(Sat_result.axis.y);
                //std::cout << "MTV - Axis: " << Sat_result.axis.x << ", " << Sat_result.axis.y << std::endl;
                player->handleHitboxCollision(sf::Vector2f(Sat_result.axis.x*Sat_result.amount,  Sat_result.axis.y*Sat_result.amount), Sat_result.axis);
            }
        }
        
        /* PARA CADA IA */
        for(int j=0; j< N_IA; j++){
            if((Sat_result = Sat.collides(IAs[j]->getVertex(), hit[i].vertex)).collides){
                Sat_result.axis.x = hit[i].sx * abs(Sat_result.axis.x);
                Sat_result.axis.y = hit[i].sy * abs(Sat_result.axis.y);
                IAs[j]->handleHitboxCollision(sf::Vector2f(Sat_result.axis.x*Sat_result.amount,  Sat_result.axis.y*Sat_result.amount), Sat_result.axis);
            }    
        }
    }
}

void Game::checkCollisionsBetweeenPlayers(){
    float x;
    float y;
    for(int i=0; i< N_IA; i++){
        for(int j = 0; j<N_IA && i!=j; j++){
            if((Sat_result = Sat.collides(IAs[i]->getVertex(), IAs[j]->getVertex())).collides){
                x = (IAs[i]->getCar().getPosition().x > IAs[j]->getCar().getPosition().x) ? 1 : -1;
                y = (IAs[i]->getCar().getPosition().y > IAs[j]->getCar().getPosition().y) ? 1 : -1;

                IAs[i]->handlePlayersCollision(sf::Vector2f(Sat_result.axis.x*x,  Sat_result.axis.y*y), Sat_result.axis);
            }
           
            if((Sat_result = Sat.collides(IAs[i]->getVertex(), player->getVertex())).collides){
                x = (IAs[i]->getCar().getPosition().x > player->getCar().getPosition().x) ? 1 : -1;
                y = (IAs[i]->getCar().getPosition().y > player->getCar().getPosition().y) ? 1 : -1;

                IAs[i]->handlePlayersCollision(sf::Vector2f(Sat_result.axis.x*Sat_result.amount*x,  Sat_result.axis.y*Sat_result.amount*y), Sat_result.axis);
            }
            
        }
    }
    
    for(int i=0; i< N_IA; i++){
        if((Sat_result = Sat.collides(player->getVertex(), IAs[i]->getVertex())).collides){
            x = (player->getCar().getPosition().x > IAs[i]->getCar().getPosition().x) ? 1 : -1;
            y = (player->getCar().getPosition().y > IAs[i]->getCar().getPosition().y) ? 1 : -1;
            
            player->handlePlayersCollision(sf::Vector2f(Sat_result.axis.x*Sat_result.amount*x,  Sat_result.axis.y*Sat_result.amount*y), Sat_result.axis);
        }
    }
    
}


void Game::burbuja(){
    namepos tmp;
    int pro1;
    int pro2;
    sf::Vector2f axis;
    for (int i=1; i<5; i++)
        for (int j=0 ; j<5 - 1; j++){
            /* COMPRUEBA SI LA POSICION (SUMA DE LOS PUNTOS DE CONTROL POR LOS QUE HA PASADO)*/
            if (*leaderboard[j].posicion < *leaderboard[j+1].posicion){  
                
                tmp = leaderboard[j];
                leaderboard[j] = leaderboard[j+1];
                leaderboard[j+1] = tmp;
            }
            
            /* SI ES IGUAL */
            else if(*leaderboard[j].posicion == *leaderboard[j+1].posicion){
                /* CALCULO EL VECTOR QUE UNE LOS CENTROS DE LOS PUNTOS DE CONTROL*/
                int prev = *leaderboard[j].posicion % 12 -1;
                if(*leaderboard[j].posicion % 12 ==0){
                    prev = 11;
                }
                
                axis = control[(*leaderboard[j].posicion) % 12].figure.getPosition() - control[prev].figure.getPosition();
                axis = Sat.normalize(axis);
                
                /* Y PROYECTO LA POSICIÓN DEL JUGADOR EN ÉL*/
                //std::cout << "EJE: " << axis.x << ", " << axis.y << std:: endl;
                if(axis.x == 0){
                    pro1 = leaderboard[j].target->getCar().getPosition().y * axis.y;
                    pro2 = leaderboard[j+1].target->getCar().getPosition().y * axis.y;
                }
                else if(axis.y == 0){      
                    pro1 = leaderboard[j].target->getCar().getPosition().x * axis.x;
                    pro2 = leaderboard[j+1].target->getCar().getPosition().x * axis.x;
                }
                else{
                    pro1 = axis.x * (leaderboard[j].target->getCar().getPosition().x) + axis.y * (leaderboard[j].target->getCar().getPosition().y);
                    pro2 = axis.x * (leaderboard[j+1].target->getCar().getPosition().x) + axis.y * (leaderboard[j+1].target->getCar().getPosition().y);
                }
               
                /* PARA SABER QUIÉN ESTÁ DELANTE */
                if(pro1 < pro2){
                    tmp = leaderboard[j];
                    leaderboard[j] = leaderboard[j+1];
                    leaderboard[j+1] = tmp;
                }
            }
        }
}



Game::item Game::createHitbox(sf::Vector2f wallSize, sf::Vector2f pos, float rotation, int sx, int sy, bool center, float rot){
    Game::item h;
    h.figure.setSize(wallSize);
    h.figure.setRotation(rotation);
    h.figure.setPosition(pos);
    
    if(center)   
        h.figure.setOrigin(wallSize.x/2, wallSize.y/2);
    
    h.vertex = new sf::Vector2f [4];
    h.vertex[0]=pos;
    if(rotation == 0){   
        h.vertex[1]=sf::Vector2f(h.vertex[0].x + wallSize.x, h.vertex[0].y);
        h.vertex[2]=sf::Vector2f(h.vertex[0].x + wallSize.x, h.vertex[0].y + wallSize.y);
        h.vertex[3]=sf::Vector2f(h.vertex[0].x, h.vertex[0].y + wallSize.y);
    }
    else{
        h.vertex[1] = sf::Vector2f(h.vertex[0].x+cos(rotation*PI/180)*wallSize.x, h.vertex[0].y + sin(rotation*PI/180)*wallSize.x);
        h.vertex[2] = sf::Vector2f(h.vertex[0].x+cos(rotation*PI/180)*wallSize.x - sin(rotation*PI/180)*wallSize.y , h.vertex[0].y +cos(rotation*PI/180)*wallSize.y + sin(rotation*PI/180)*wallSize.x);
        h.vertex[3] = sf::Vector2f(h.vertex[0].x-sin(rotation*PI/180)*wallSize.y, h.vertex[0].y + cos(rotation*PI/180)*wallSize.y);
    }
    
    h.sx = sx;
    h.sy = sy;
    h.newRotation = rot;
    return h;
}