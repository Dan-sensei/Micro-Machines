/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


//Esta clase forma parte del libro "SFML Essentials" para optimizar la carga de texturas

#include "AssetManager.h"
#include <assert.h>


AssetManager* AssetManager::sInstance = nullptr;

AssetManager::AssetManager(){
    assert(sInstance == nullptr);
    sInstance = this;
}

sf::Texture& AssetManager::GetTexture(const std::string& filename){
    
    auto& texMap = sInstance->m_Textures;
    auto pairFound = texMap.find(filename);
    
    if(pairFound != texMap.end()){
        return pairFound->second;
    }
    else{
        auto& texture = texMap[filename];
        texture.loadFromFile(filename);
        return texture;
    }
}

/*
 /usr/include/c++/7.3.0
 ../build/include
 */
sf::Font& AssetManager::GetFont(const std::string& filename){
    
    auto& fontMap = sInstance->m_Fonts;
    auto pairFound = fontMap.find(filename);
    
    if(pairFound != fontMap.end()){
        return pairFound->second;
    }
    else{
        auto& font = fontMap[filename];
        font.loadFromFile(filename);
        return font;
    }
}