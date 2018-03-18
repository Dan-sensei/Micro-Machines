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

#define TICK 1000/35

Game::Game(int N, int nVueltas):
window(sf::VideoMode(1200, 900), "MicroMachines - Neon Edition"),
animator(sprite)
{
    window.setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width/2 -600, 50));

    N_PLAYERS = N;
    N_IA = 4;
    VUELTAS = nVueltas;
    
    sf::Vector2f startPos = sf::Vector2f(200, 1850);
    
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
        view2.setSize(sf::Vector2f(view.getSize().x * 1.3, view.getSize().y * 1.3));
    }
    view.setCenter(startPos);
    view.setSize(sf::Vector2f(view.getSize().x * 1.3, view.getSize().y * 1.3));
    window.setFramerateLimit(60);
    window.setMouseCursorVisible(false);
    
    Cool_Map = sf::Sprite (AssetManager::GetTexture("Images/ULTIMATE_MAP.png"));
    BACKGROUND = sf::Sprite (AssetManager::GetTexture("Images/BACKGROUND.jpg"));
    BACKGROUND.setOrigin(4471, 3284.5);
    BACKGROUND.setPosition(3800, 1835);
    window.setView(view);  
    
    keys = new bool[256];
    for(int i = 0; i<256; i++)
        keys[i]=false;
    
    dtAsSeconds = new float[1];
    //sprite_name, startPosition, MAX_SPEED, acceleration, Initial_rotation, deltaTime, rotation_speed, keyboard
    
    player[0] = new Player(1, "Images/HERO.jpg", startPos, 1000, 900, 0, dtAsSeconds, 200, keys);
    player[1] = new Player(2, "Images/HERO_2.jpg", sf::Vector2f(400, 1950), 1000, 900, 0, dtAsSeconds, 220, keys);
    IAs[0] = new Enemy("Images/BOSS.jpg", sf::Vector2f(400, 1550), 950, 1050, 0, dtAsSeconds); //1000
    IAs[1] = new Enemy("Images/IA1.jpg", sf::Vector2f(400, 1750), 920, 900, 0, dtAsSeconds);  //900
    IAs[2] = new Enemy("Images/IA2.jpg", sf::Vector2f(200, 1650), 900, 1000, 0, dtAsSeconds);    //1000
    IAs[3] = new Enemy("Images/IA3.jpg", sf::Vector2f(200, 1450), 980, 950, 0, dtAsSeconds);  //950
    
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
    control[0] = createHitbox(sf::Vector2f(583, 15), sf::Vector2f(291.5, 1335), 0, 1, 1, true, 45);
    control[1] = createHitbox(sf::Vector2f(15, 583), sf::Vector2f(1308, 291.5), 0, 1, 1, true, 90);
    control[2] = createHitbox(sf::Vector2f(15, 583), sf::Vector2f(5460, 291.5), 0, 1, 1, true, 135);
    control[3] = createHitbox(sf::Vector2f(583, 15), sf::Vector2f(6111.5, 943), 0, 1, 1, true, 180);
    control[4] = createHitbox(sf::Vector2f(583, 15), sf::Vector2f(6111.5, 3354), 0, 1, 1, true, 235);
    control[5] = createHitbox(sf::Vector2f(15, 583), sf::Vector2f(5305, 4060.5), 0, 1, 1, true, 270);
    control[6] = createHitbox(sf::Vector2f(15, 583), sf::Vector2f(2705, 4060.5), 0, 1, 1, true, 315);
    control[7] = createHitbox(sf::Vector2f(583, 15), sf::Vector2f(2413.5, 3669), 0, 1, 1, true, 0);
    control[8] = createHitbox(sf::Vector2f(583, 15), sf::Vector2f(2413.5, 3286), 0, 1, 1, true, 315);
    control[9] = createHitbox(sf::Vector2f(15, 583), sf::Vector2f(2021, 2994.5), 0, 1, 1, true, 270);
    control[10] = createHitbox(sf::Vector2f(15, 583), sf::Vector2f(583, 2994.5), 0, 1, 1, true, 315);
    control[11] = createHitbox(sf::Vector2f(583, 15), sf::Vector2f(291.5, 2602), 0, 1, 1, true, 0);
    
    JUMP = sf::RectangleShape(sf::Vector2f(350, 584));
    JUMP.setOrigin(350/2, 584/2);
    JUMP.setFillColor(sf::Color::Blue);
    JUMP.setPosition(3300, 291.5);
    
    //TURBOS
    turboPos[0] = createTurbo(sf::Vector2f(50, 583), sf::Vector2f(1700, 291.5), 0);
    turboPos[1] = createTurbo(sf::Vector2f(50, 583), sf::Vector2f(6111.5, 1443), 90);
    turboPos[2] = createTurbo(sf::Vector2f(50, 583), sf::Vector2f(6111.5, 1893), 90);
    turboPos[3] = createTurbo(sf::Vector2f(50, 583), sf::Vector2f(6111.5, 2343), 90);
    turboPos[4] = createTurbo(sf::Vector2f(50, 583), sf::Vector2f(4235, 4060.5), 180);
    turboPos[5] = createTurbo(sf::Vector2f(50, 583), sf::Vector2f(291.5, 2402), 270);
    
    for(int i = 0; i < N_IA; i++){
        leaderboard[i].picture = IAs[i]->getCar();
        leaderboard[i].picture.scale(0.6, 0.6);
        leaderboard[i].picture.setOrigin(30, 30);
        leaderboard[i].posicion = IAs[i]->getP_pos();
        leaderboard[i].target = IAs[i];
        
        actual[i].position = previous[i].position = IAs[i]->getCar().getPosition();
        actual[i].rotation = previous[i].rotation = 0;
        actual[i].scale = previous[i].scale = 1;
    }
    
    for(int i = 0; i < N_PLAYERS; i++){
        leaderboard[i+4].picture = player[i]->getCar();
        leaderboard[i+4].picture.scale(0.6, 0.6);
        leaderboard[i+4].picture.setOrigin(30, 30);
        leaderboard[i+4].posicion = player[i]->getP_pos();
        leaderboard[i+4].target = player[i];

        actual[i+4].position = previous[i+4].position = player[i]->getCar().getPosition();
        actual[i+4].rotation = previous[i+4].rotation = 0;
        actual[i+4].scale = previous[i+4].scale = 1;
    }
    

    
    sf::Vector2i size(244, 489);
    turbo = &animator.createAnimation("Turbo", "Images/TURBO.png", sf::seconds(2), true);
    turbo->AddFrames(sf::Vector2i(0, 0), size, 48);
    sprite.setOrigin(size.x*0.5, size.y*0.5);
    sprite.scale(0.5, 1.19);
    sprite.setPosition(1600, 291.5);
    
    TURBO_SOUND.setBuffer(AssetManager::GetSoundBuffer("Sounds/TURBO.ogg"));
    finisher = false;
}

Game::~Game() {
}

void Game::go(){
    masterClock.restart();
    
    sf::Sound COUNTDOWN(AssetManager::GetSoundBuffer("Sounds/COUNTDOWN.ogg"));
    float flag = 0.0;
    /* COUNTDOWN! */
    while(elapsedTime.asSeconds() < 3 && window.isOpen()){
        render_init();
        if(flag < elapsedTime.asSeconds()){
            COUNTDOWN.play();
            flag += 1;
        }
        elapsedTime += masterClock.restart();
        handleEvents();
    }
    
    if(!NIGHT_OF_FIRE.openFromFile("Sounds/NIGHT_OF_FIRE.ogg")){
        std::cout << "Error al cargar la música." << std::endl;
    }
    NIGHT_OF_FIRE.play();
    while(window.isOpen()){
    //std::cout << "MASTER " << masterClock.getElapsedTime().asSeconds() << std::endl;
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
                if(keys[16]) window.close();        // Q: Cerrar
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
        actual[i].scale = IAs[i]->getCar().getScale().x;

        if(IAs[i]->getVueltas() == VUELTAS && !finisher){
            finisher = true;
            winner = leaderboard[0].picture;
            NIGHT_OF_FIRE.stop();
            MRKRAB_VIOLIN.openFromFile("Sounds/MRKRAB_VIOLIN.ogg");
            MRKRAB_VIOLIN.play();
        }
    }
    
    for(int i=0; i< N_PLAYERS; i++){
        actual[i+4].position = player[i]->getCar().getPosition();
        actual[i+4].rotation = player[i]->getCar().getRotation();
        actual[i+4].scale = player[i]->getCar().getScale().x;

        if(player[i]->getVueltas() == VUELTAS && !finisher){
            finisher = true;
            winner = leaderboard[0].picture;
            NIGHT_OF_FIRE.stop();
            AHH_BITCONNEEEEEECT.openFromFile("Sounds/AHH_BITCONNEEEEEECT.ogg");
            AHH_BITCONNEEEEEECT.play();
        }
    }
}

void Game::render_init(){
    sf::Time auxDT = normalClock.restart();
    animator.update(auxDT);
    window.clear(Dark);
    window.setView(view);
    window.draw(BACKGROUND);
    window.draw(Cool_Map);
    window.draw(control[0].figure);
    for(int i = 0; i< 6; i++){
        sprite.setRotation(turboPos[i].getRotation());
        sprite.setPosition(turboPos[i].getPosition());
        window.draw(sprite, sf::BlendAdd);
    }
    renderPlayers(1, 0);
    renderEnemies(1);
    
    if(N_PLAYERS > 1){
        window.setView(view2);
        window.draw(BACKGROUND);
        window.draw(Cool_Map);
        window.draw(control[0].figure);
        for(int i = 0; i< 6; i++){
            sprite.setRotation(turboPos[i].getRotation());
            sprite.setPosition(turboPos[i].getPosition());
            window.draw(sprite, sf::BlendAdd);
        }
        renderPlayers(1, 1);
        renderEnemies(1);
    }
    
    window.setView(UI);
    sf::Text countdown = sf::Text(std::to_string(3-(int)elapsedTime.asSeconds()), AssetManager::GetFont("Fonts/LemonMilk.otf"));  
    
    countdown.setCharacterSize(150);
    countdown.setPosition(view.getCenter().x, view.getCenter().y-150);
    countdown.setFillColor(Light);
    window.draw(countdown);
    window.display();
}

void Game::render(float tick){                                       // <--------------------------------------------------------- RENDER =========================================================
    //std::cout << "RENDER -- " << std::endl;
    sf::Time auxDT = normalClock.restart();
    animator.update(auxDT);
    window.clear(Dark);
    
    window.setView(view);
    window.draw(BACKGROUND);
    window.draw(Cool_Map);
    window.draw(control[0].figure);

    for(int i = 0; i< 6; i++){
        sprite.setRotation(turboPos[i].getRotation());
        sprite.setPosition(turboPos[i].getPosition());
        window.draw(sprite, sf::BlendAdd);
    }
    
    renderPlayers(tick, 0);
    renderEnemies(tick);
    sf::Text vueltas = sf::Text("", AssetManager::GetFont("Fonts/LemonMilk.otf"));
    
    /* POSICIONES EN LA CARRERA */
    int map = 80;
    vueltas.setPosition(window.mapPixelToCoords(sf::Vector2i(10, 20)));
    vueltas.setString( "VUELTA "+std::to_string(player[0]->getVueltas()) + " / " +std::to_string(VUELTAS) );
    window.draw(vueltas);
    sf::Text display;
    for(int i = 0; i < (N_IA+N_PLAYERS); i++){
        display = sf::Text(std::to_string(i+1)+" - ", AssetManager::GetFont("Fonts/LemonMilk.otf"));
        display.setOrigin(display.getLocalBounds().width/2, display.getLocalBounds().height/2);
        display.setPosition(window.mapPixelToCoords(sf::Vector2i(35, map)));
        leaderboard[i].picture.setPosition(window.mapPixelToCoords(sf::Vector2i(70, map)));
        window.draw(leaderboard[i].picture);
        window.draw(display);
        map+=30;
    }
    
    if(N_PLAYERS == 2){
        /* CAMARA 2 */
        window.setView(view2);
        window.draw(BACKGROUND);
        window.draw(Cool_Map);
        window.draw(control[0].figure);
        for(int i = 0; i< 6; i++){
            sprite.setRotation(turboPos[i].getRotation());
            sprite.setPosition(turboPos[i].getPosition());
            window.draw(sprite, sf::BlendAdd);
        }
        renderPlayers(tick, 1);
        renderEnemies(tick);
        map = 540;
        vueltas.setPosition(window.mapPixelToCoords(sf::Vector2i(10, 470)));
        vueltas.setString( "VUELTA "+std::to_string(player[1]->getVueltas()) + " / " +std::to_string(VUELTAS) );
        window.draw(vueltas);
        for(int i = 0; i < (N_IA+N_PLAYERS); i++){
            display = sf::Text(std::to_string(i+1)+" - ", AssetManager::GetFont("Fonts/LemonMilk.otf"));
            display.setOrigin(display.getLocalBounds().width/2, display.getLocalBounds().height/2);
            display.setPosition(window.mapPixelToCoords(sf::Vector2i(35, map)));
            leaderboard[i].picture.setPosition(window.mapPixelToCoords(sf::Vector2i(70, map)));
            window.draw(leaderboard[i].picture);
            window.draw(display);
            map+=30;
        }
    }
    
    window.setView(UI);
    if(finisher){
        sf::Text win = sf::Text("WINNER", AssetManager::GetFont("Fonts/LemonMilk.otf"));  
        win.setCharacterSize(75);
        win.setPosition(window.mapPixelToCoords(sf::Vector2i(window.getSize().x/2-300, window.getSize().y/2-50)));
        win.setFillColor(Light);
        
        
        winner.setScale(2, 2);
        winner.setPosition(window.mapPixelToCoords(sf::Vector2i(window.getSize().x/2+100, window.getSize().y/2-10)));
        window.draw(winner);
        window.draw(win);
       
    }
   
    window.display();
}

void Game::rendercontrol(){
    for(int i=0; i< 12; i++)
        window.draw(control[i].figure);
}

void Game::renderPlayers(float tick, int camera){   
    float x;
    float y;
    float c;
    float s;
    float scale;
    float factor;
    for(int i = 0; i < N_PLAYERS; i++){
        x = previous[(i+camera)%2+N_IA].position.x *(1-tick) + actual[(i+camera)%2+N_IA].position.x*tick;
        y = previous[(i+camera)%2+N_IA].position.y *(1-tick) + actual[(i+camera)%2+N_IA].position.y*tick;
        c = cos(previous[(i+camera)%2+N_IA].rotation *PI/180) * (1-tick) + cos(actual[(i+camera)%2+N_IA].rotation*PI/180)*tick;
        s = sin(previous[(i+camera)%2+N_IA].rotation *PI/180) * (1-tick) + sin(actual[(i+camera)%2+N_IA].rotation*PI/180)*tick;
        scale = previous[(i+camera)%2+N_IA].scale *(1-tick) + actual[(i+camera)%2+N_IA].scale*tick;
        //std::cout << "Tick " << tick << std::endl; 
        //std::cout << "Previous: " << previous[4].position.x << ", " << previous[4].position.y << " | Actual: " << actual[4].position.x << ", " << actual[4].position.y << std::endl;
        //std::cout << "Interpolated -----: " << x << ", " << y << std::endl;
        player[(i+camera)%2]->interpola(x, y, atan2(s,c)*180/PI, scale);  
        
        if((i+camera)%2 == 0 && camera == 0){
            //std::cout << "ZOOM " << player[(i+camera)%2]->getCar().getScale().x + 0.3 << std::endl;
            view.setCenter(player[(i+camera)%2]->getCar().getPosition());
            factor = player[(i+camera)%2]->getCar().getScale().x + 0.3;
            if(N_PLAYERS == 1){
                view.setSize(sf::Vector2f(window.getSize().x*factor, window.getSize().y*factor));
            }
            else{
                view.setSize(sf::Vector2f(window.getSize().x*factor, (window.getSize().y/2)*factor));
            }
            window.setView(view);
            
        }
        else if((i+camera)%2 == 1 && camera == 1){
            view2.setCenter(player[(i+camera)%2]->getCar().getPosition());
            factor = player[(i+camera)%2]->getCar().getScale().x + 0.3;
            view2.setSize(sf::Vector2f(window.getSize().x*factor, (window.getSize().y/2)*factor));
            
            window.setView(view2);
        }
        window.draw(player[(i+camera)%2]->getCar());
        player[(i+camera)%2]->interpola(actual[(i+camera)%2+N_IA].position.x, actual[(i+camera)%2+N_IA].position.y, actual[(i+camera)%2+N_IA].rotation, actual[(i+camera)%2+N_IA].scale);
        //std::cout << "CAR ----- " << player[0]->getCar().getPosition().x << ", " << player[0]->getCar().getPosition().y << std::endl << std::endl;
    }     
}

void Game::renderEnemies(float tick){
    
    float x;
    float y;
    float c;
    float s;
    float scale;
    
    for(int i=0; i< N_IA; i++){
        x = previous[i].position.x *(1-tick) + actual[i].position.x*tick;
        y = previous[i].position.y *(1-tick) + actual[i].position.y*tick;
        c = cos(previous[i].rotation *PI/180) * (1-tick) + cos(actual[i].rotation*PI/180)*tick;
        s = sin(previous[i].rotation *PI/180) * (1-tick) + sin(actual[i].rotation*PI/180)*tick;
        scale = previous[i].scale *(1-tick) + actual[i].scale*tick;
        
       IAs[i]->interpola(x, y, atan2(s,c)*180/PI, scale);
       
       window.draw(IAs[i]->getCar());
       IAs[i]->interpola(actual[i].position.x, actual[i].position.y, actual[i].rotation, actual[i].scale);
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
    for(int i = 0; i < N_PLAYERS; i++){
        
        j = player[i]->getPosition() % 12;
        if(player[i]->getCar().getGlobalBounds().intersects(control[j].figure.getGlobalBounds()) && !player[i]->getFlag(j) && player[i]->handleIncremenet(j)){
             player[i]->setCheckPoint(j, true);
             player[i]->setVisited(j);
             player[i]->incrementPosition(1);

         }
         else if(!(player[i]->getCar().getGlobalBounds().intersects(control[j].figure.getGlobalBounds())))
             player[i]->setCheckPoint(j, false);    
    }
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
        if(!IAs[i]->isOnAir()){
            
            for(int j = 0; j<N_IA && i!=j; j++){
                if(!IAs[j]->isOnAir() && (Sat_result = Sat.collides(IAs[i]->getVertex(), IAs[j]->getVertex())).collides){
                    x = (IAs[i]->getCar().getPosition().x > IAs[j]->getCar().getPosition().x) ? 1 : -1;
                    y = (IAs[i]->getCar().getPosition().y > IAs[j]->getCar().getPosition().y) ? 1 : -1;

                    IAs[i]->handlePlayersCollision(sf::Vector2f(Sat_result.axis.x*x*Sat_result.amount,  Sat_result.axis.y*y*Sat_result.amount));
                }
            }
            for(int j = 0; j< N_PLAYERS; j++)
                if(!player[j]->isOnAir() && (Sat_result = Sat.collides(IAs[i]->getVertex(), player[j]->getVertex())).collides){
                    x = (IAs[i]->getCar().getPosition().x > player[j]->getCar().getPosition().x) ? 1 : -1;
                    y = (IAs[i]->getCar().getPosition().y > player[j]->getCar().getPosition().y) ? 1 : -1;

                    IAs[i]->handlePlayersCollision(sf::Vector2f(Sat_result.axis.x*Sat_result.amount*x,  Sat_result.axis.y*Sat_result.amount*y));
                }
        }
            
    }
    
    for(int i = 0; i< N_PLAYERS; i++){
        if(!player[i]->isOnAir()){  
            for(int j=0; j< N_IA; j++){
                if(!IAs[j]->isOnAir() && (Sat_result = Sat.collides(player[i]->getVertex(), IAs[j]->getVertex())).collides){
                    x = (player[i]->getCar().getPosition().x > IAs[j]->getCar().getPosition().x) ? 1 : -1;
                    y = (player[i]->getCar().getPosition().y > IAs[j]->getCar().getPosition().y) ? 1 : -1;

                    player[i]->handlePlayersCollision(sf::Vector2f(Sat_result.axis.x*Sat_result.amount*x,  Sat_result.axis.y*Sat_result.amount*y));
                }
            }
            if(N_PLAYERS > 1)
                if(!player[(i+1)%2]->isOnAir() && (Sat_result = Sat.collides(player[i]->getVertex(), player[(i+1)%2]->getVertex())).collides){
                    x = (player[i]->getCar().getPosition().x > player[(i+1)%2]->getCar().getPosition().x) ? 1 : -1;
                    y = (player[i]->getCar().getPosition().y > player[(i+1)%2]->getCar().getPosition().y) ? 1 : -1;

                    player[i]->handlePlayersCollision(sf::Vector2f(Sat_result.axis.x*Sat_result.amount*x,  Sat_result.axis.y*Sat_result.amount*y));
                }
        }
    }
    
}

void Game::checkSpecialInteractions(){
    
    
    for(int i = 0; i < N_IA; i++){
        if(IAs[i]->getCar().getGlobalBounds().intersects(JUMP.getGlobalBounds())){
            IAs[i]->setSpeed(1800);
            IAs[i]->setAir(true);
        }
        for(int j = 0; j< 6; j++){
            if(IAs[i]->getCar().getGlobalBounds().intersects(turboPos[j].getGlobalBounds()))
                IAs[i]->setSpeed(1800);
        }
    }
    
    for(int i=0; i< N_PLAYERS; i++){
        if(player[i]->getCar().getGlobalBounds().intersects(JUMP.getGlobalBounds())){
            player[i]->setSpeed(1800);
            player[i]->setAir(true);
            TURBO_SOUND.play();
        }
        for(int j = 0; j< 6; j++){
            if(player[i]->getCar().getGlobalBounds().intersects(turboPos[j].getGlobalBounds())){
                player[i]->setSpeed(1800);
                TURBO_SOUND.play();
            }
        }
    }
    //std::cout << "Scale " << player[0]->getCar().getScale().x << std::endl;
}


void Game::burbuja(){
    namepos tmp;
    int pro1;
    int pro2;
    sf::Vector2f axis;
    for (int i=1; i<(N_IA+N_PLAYERS); i++)
        for (int j=0 ; j<(N_IA+N_PLAYERS) - 1; j++){
            /* COMPRUEBA LA POSICION (SUMA DE LOS PUNTOS DE CONTROL POR LOS QUE HA PASADO)*/
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

sf::RectangleShape Game::createTurbo(sf::Vector2f size, sf::Vector2f pos, float rotation){
    sf::RectangleShape turbo;
    
    turbo.setSize(size);
    turbo.setFillColor(sf::Color::Red);
    turbo.setOrigin(size.x*0.5, size.y*0.5);
    turbo.setRotation(rotation);
    turbo.setPosition(pos);
    
    return turbo;
}