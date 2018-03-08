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

#define TICK 1000/25

Game::Game(int N, int IA):
window(sf::VideoMode(1200, 900), "MicroMachines - Neon Edition")
{
    window.setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width/2 -600, 50));

    N_PLAYERS = N;
    N_IA = IA;
    
    sf::Vector2f startPos = sf::Vector2f(400, 1800);
    
    UI = sf::View(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
    UI.setCenter(startPos);
    
    if(N_PLAYERS == 1){
         view = sf::View(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
    }
    else{
        view = sf::View(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y/2));
        view.setViewport(sf::FloatRect(0, 0, 1, 0.5f));

        view2 = sf::View(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y/2));
        view2.setViewport(sf::FloatRect(0, 0.5f , 1, 0.5f));
        view2.setCenter(startPos);
        view2.zoom(1.3);
    }
    view.setCenter(startPos);
    view.zoom(1.3);
    
    window.setFramerateLimit(60);
    window.setMouseCursorVisible(false);
    
    Cool_Map = sf::Sprite (AssetManager::GetTexture("Images/New.jpg")); 

    window.setView(view);  
    
    keys = new bool[256];
    for(int i = 0; i<256; i++)
        keys[i]=false;
    
    dtAsSeconds = new float[1];
    //sprite_name, startPosition, MAX_SPEED, acceleration, Initial_rotation, deltaTime, rotation_speed, keyboard
    
    player[0] = new Player(1, "Images/HERO.jpg", startPos, 1000, 900, 0, dtAsSeconds, 220, keys);
    player[1] = new Player(2, "Images/HERO.jpg", sf::Vector2f(300, 1800), 1000, 900, 0, dtAsSeconds, 220, keys);
    IAs[0] = new Enemy("Images/Enemy.jpg", sf::Vector2f(80, 1700), 1000, 1000, 0, dtAsSeconds); //1000
    IAs[1] = new Enemy("Images/Enemy.jpg", sf::Vector2f(150, 1750), 950, 900, 0, dtAsSeconds);  //900
    IAs[2] = new Enemy("Images/Enemy.jpg", sf::Vector2f(180, 1650), 1000, 1000, 0, dtAsSeconds);    //1000
    IAs[3] = new Enemy("Images/Enemy.jpg", sf::Vector2f(200, 1620), 980, 950, 0, dtAsSeconds);  //950
    
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
    control[1] = createHitbox(sf::Vector2f(5, 583), sf::Vector2f(1308, 291.5), 0, 1, 1, true, 90);
    control[2] = createHitbox(sf::Vector2f(5, 583), sf::Vector2f(5460, 291.5), 0, 1, 1, true, 135);
    control[3] = createHitbox(sf::Vector2f(583, 5), sf::Vector2f(6111.5, 943), 0, 1, 1, true, 180);
    control[4] = createHitbox(sf::Vector2f(583, 5), sf::Vector2f(6111.5, 3284), 0, 1, 1, true, 235);
    control[5] = createHitbox(sf::Vector2f(5, 583), sf::Vector2f(5335, 4060.5), 0, 1, 1, true, 270);
    control[6] = createHitbox(sf::Vector2f(5, 583), sf::Vector2f(2705, 4060.5), 0, 1, 1, true, 315);
    control[7] = createHitbox(sf::Vector2f(583, 5), sf::Vector2f(2413.5, 3769), 0, 1, 1, true, 0);
    control[8] = createHitbox(sf::Vector2f(583, 5), sf::Vector2f(2413.5, 3286), 0, 1, 1, true, 315);
    control[9] = createHitbox(sf::Vector2f(5, 583), sf::Vector2f(2121, 2994.5), 0, 1, 1, true, 270);
    control[10] = createHitbox(sf::Vector2f(5, 583), sf::Vector2f(583, 2994.5), 0, 1, 1, true, 315);
    control[11] = createHitbox(sf::Vector2f(583, 5), sf::Vector2f(291.5, 2702), 0, 1, 1, true, 0);
    
    JUMP = sf::RectangleShape(sf::Vector2f(350, 584));
    JUMP.setOrigin(350/2, 584/2);
    JUMP.setFillColor(sf::Color::Blue);
    JUMP.setPosition(2800, 291.5);
    
    for(int i = 0; i < N_IA; i++){
        leaderboard[i].nombre = "IA #"+std::to_string(i+1);
        leaderboard[i].posicion = IAs[i]->getP_pos();
        leaderboard[i].target = IAs[i];
        leaderboard[i].id = sf::Text("IA #"+std::to_string(i+1), AssetManager::GetFont("Fonts/LemonMilk.otf"));
        
        actual[i].position = previous[i].position = IAs[i]->getCar().getPosition();
        actual[i].rotation = previous[i].rotation = 0;
    }
    
    for(int i = 0; i < N_PLAYERS; i++){
        leaderboard[i+4].nombre = "Player " + std::to_string(i);
        leaderboard[i+4].posicion = player[i]->getP_pos();
        leaderboard[i+4].target = player[i];
        leaderboard[i+4].id = sf::Text("Player " + std::to_string(i), AssetManager::GetFont("Fonts/LemonMilk.otf"));  

        actual[i+4].position = previous[i+4].position = player[i]->getCar().getPosition();
        actual[i+4].rotation = previous[i+4].rotation = 0;
    
    }
    

    
}

Game::~Game() {
}

void Game::go(){
    //masterClock.restart();
    while(window.isOpen()){
        handleEvents();
        //std::cout << "TIME: " << masterClock.getElapsedTime().asMilliseconds() << std::endl;
        if(masterClock.getElapsedTime().asMilliseconds() > TICK)
            update();
        
        
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
    //std::cout << "UPDATE -- " << std::endl;
    /* REINICIO EL RELOJ */
    deltaTime = masterClock.restart();
    elapsedTime += deltaTime;
    dtAsSeconds[0] = deltaTime.asSeconds();
            
    /* SOBRESCRIBO LOS DATOS ANTERIORES */
    for(int i = 0; i < (N_PLAYERS + N_IA); i++) {
        previous[i] = actual[i];
    }
    
    /* MOVIMIENTO Y LÓGICA */
    for(int i=0; i<N_PLAYERS; i++)
        player[i]->movement(); 
    
    for(int i= 0; i<4; i++)
        IAs[i]->logic();
   
    /* COLISIONES */
    checkPoints();
    checkCollisionsBetweeenHitbox();
    checkCollisionsBetweeenPlayers();
    checkSpecialInteractions();
    burbuja();
    
    /* ACTUALIZO LA POSICIÓN SIGUIENTE */

    for(int i = 0; i < N_IA; i++){
        actual[i].position = IAs[i]->getCar().getPosition();
        actual[i].rotation = IAs[i]->getCar().getRotation();
    }
    
    for(int i=0; i< N_PLAYERS; i++){
        actual[i+4].position = player[i]->getCar().getPosition();
        actual[i+4].rotation = player[i]->getCar().getRotation();
    }
    
    if(player[0]->getVueltas() == 2){
        window.close();
    }
    
}

void Game::render(float tick){                                       // <--------------------------------------------------------- RENDER =========================================================
    //std::cout << "RENDER -- " << std::endl;
    window.clear(Dark);
    

    
    window.setView(view);
    window.draw(Cool_Map);
    window.draw(JUMP);
    renderPlayers(tick, 0);
    renderEnemies(tick, 0);
    

    window.draw(leaderboard[0].id);
    window.draw(leaderboard[1].id);
    window.draw(leaderboard[2].id);
    window.draw(leaderboard[3].id);
    window.draw(leaderboard[4].id);
    
    if(N_PLAYERS == 2){
        
    
    /* CAMARA 2 */
    window.setView(view2);
    window.draw(Cool_Map);
    window.draw(JUMP);
    renderEnemies(tick, 1);
    renderPlayers(tick, 1);
    

    
    UI.setCenter(0, 0);
    window.setView(UI);
    }
    /* POSICIONES EN LA CARRERA */
   

   
    window.display();
}

void Game::rendercontrol(){
    for(int i=0; i< 12; i++){
        
        window.draw(control[i].figure);
    }
}

void Game::renderPlayers(float tick, int camera){
    
    float x;
    float y;
    float c;
    float s;
    
    
    for(int i = 0; i < N_PLAYERS; i++){
        x = previous[(i+camera)%2+N_IA].position.x *(1-tick) + actual[(i+camera)%2+N_IA].position.x*tick;
        y = previous[(i+camera)%2+N_IA].position.y *(1-tick) + actual[(i+camera)%2+N_IA].position.y*tick;
        c = cos(previous[(i+camera)%2+N_IA].rotation *PI/180) * (1-tick) + cos(actual[(i+camera)%2+N_IA].rotation*PI/180)*tick;
        s = sin(previous[(i+camera)%2+N_IA].rotation *PI/180) * (1-tick) + sin(actual[(i+camera)%2+N_IA].rotation*PI/180)*tick;

        //std::cout << "Tick " << tick << std::endl; 
        //std::cout << "Previous: " << previous[4].position.x << ", " << previous[4].position.y << " | Actual: " << actual[4].position.x << ", " << actual[4].position.y << std::endl;
        //std::cout << "Interpolated -----: " << x << ", " << y << std::endl;
        player[(i+camera)%2]->interpola(x, y, atan2(s,c)*180/PI);  
        
        if((i+camera)%2 == 0 && camera == 0){
            view.setCenter(player[(i+camera)%2]->getCar().getPosition());
            window.setView(view);
            leaderboard[0].id.setPosition(player[0]->getCar().getPosition() - sf::Vector2f(650, 250));
            leaderboard[1].id.setPosition(player[0]->getCar().getPosition() - sf::Vector2f(650, 200));
            leaderboard[2].id.setPosition(player[0]->getCar().getPosition() - sf::Vector2f(650, 150));
            leaderboard[3].id.setPosition(player[0]->getCar().getPosition() - sf::Vector2f(650, 100));
            leaderboard[4].id.setPosition(player[0]->getCar().getPosition() - sf::Vector2f(650, 50));
        }
        else if((i+camera)%2 == 1 && camera == 1){
            view2.setCenter(player[(i+camera)%2]->getCar().getPosition());
            window.setView(view2);
        }
        window.draw(player[(i+camera)%2]->getCar());
        player[(i+camera)%2]->interpola(actual[(i+camera)%2+N_IA].position.x, actual[(i+camera)%2+N_IA].position.y, actual[(i+camera)%2+N_IA].rotation);
        //std::cout << "CAR ----- " << player[0]->getCar().getPosition().x << ", " << player[0]->getCar().getPosition().y << std::endl << std::endl;
    }


        
}

void Game::renderEnemies(float tick, int camera){
    
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
       
        window.draw(IAs[i]->getCar());
       IAs[i]->interpola(actual[i].position.x, actual[i].position.y, actual[i].rotation);
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
    
    j = player[0]->getPosition() % 12;
    if(player[0]->getCar().getGlobalBounds().intersects(control[j].figure.getGlobalBounds()) && !player[0]->getFlag(j) && player[0]->handleIncremenet(j)){
         player[0]->setCheckPoint(j, true);
         player[0]->setVisited(j);
         player[0]->incrementPosition(1);

     }
     else if(!(player[0]->getCar().getGlobalBounds().intersects(control[j].figure.getGlobalBounds())))
         player[0]->setCheckPoint(j, false);    
}

void Game::checkCollisionsBetweeenHitbox(){
    SAT::MTV Sat_result;
    /* PARA CADA COLLIDER */
    for(int i = 0; i < 15; i++){
        /* PARA CADA JUGADOR */
        for(int j = 0; j<N_PLAYERS ; j++){
            if((Sat_result = Sat.collides(player[j]->getVertex(), hit[i].vertex)).collides){
                Sat_result.axis.x = hit[i].sx * abs(Sat_result.axis.x);
                Sat_result.axis.y = hit[i].sy * abs(Sat_result.axis.y);
                //std::cout << "MTV - Axis: " << Sat_result.axis.x << ", " << Sat_result.axis.y << std::endl;
                player[j]->handleHitboxCollision(sf::Vector2f(Sat_result.axis.x*Sat_result.amount,  Sat_result.axis.y*Sat_result.amount), Sat_result.axis);
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
    SAT::MTV Sat_result;
    for(int i=0; i< N_IA; i++){
        for(int j = 0; j<N_IA && i!=j; j++){
            if((Sat_result = Sat.collides(IAs[i]->getVertex(), IAs[j]->getVertex())).collides){
                x = (IAs[i]->getCar().getPosition().x > IAs[j]->getCar().getPosition().x) ? 1 : -1;
                y = (IAs[i]->getCar().getPosition().y > IAs[j]->getCar().getPosition().y) ? 1 : -1;

                IAs[i]->handlePlayersCollision(sf::Vector2f(Sat_result.axis.x*x*Sat_result.amount,  Sat_result.axis.y*y*Sat_result.amount), Sat_result.axis);
            }
           
            if((Sat_result = Sat.collides(IAs[i]->getVertex(), player[0]->getVertex())).collides){
                x = (IAs[i]->getCar().getPosition().x > player[0]->getCar().getPosition().x) ? 1 : -1;
                y = (IAs[i]->getCar().getPosition().y > player[0]->getCar().getPosition().y) ? 1 : -1;

                IAs[i]->handlePlayersCollision(sf::Vector2f(Sat_result.axis.x*Sat_result.amount*x,  Sat_result.axis.y*Sat_result.amount*y), Sat_result.axis);
            }
            
        }
    }
    
    for(int i=0; i< N_IA; i++){
        if((Sat_result = Sat.collides(player[0]->getVertex(), IAs[i]->getVertex())).collides){
            x = (player[0]->getCar().getPosition().x > IAs[i]->getCar().getPosition().x) ? 1 : -1;
            y = (player[0]->getCar().getPosition().y > IAs[i]->getCar().getPosition().y) ? 1 : -1;
            
            player[0]->handlePlayersCollision(sf::Vector2f(Sat_result.axis.x*Sat_result.amount*x,  Sat_result.axis.y*Sat_result.amount*y), Sat_result.axis);
        }
    }
    
}

void Game::checkSpecialInteractions(){
    if(player[0]->getCar().getGlobalBounds().intersects(JUMP.getGlobalBounds())){
        std::cout << "Endl" << std::endl;
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