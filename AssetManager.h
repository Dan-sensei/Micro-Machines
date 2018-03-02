/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AssetManager.h
 * Author: dan
 *
 * Created on 5 de febrero de 2018, 11:40
 */

#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <SFML/Graphics.hpp>
#include <map>

class AssetManager{
    public:
        AssetManager();
        
        static sf::Texture& GetTexture(std::string const& filename);
        static sf::Font& GetFont(std::string const& filename);
        
    private:
        std::map<std::string, sf::Texture> m_Textures;
        std::map<std::string, sf::Font> m_Fonts;
        static AssetManager* sInstance;
};

#endif /* ASSETMANAGER_H */

