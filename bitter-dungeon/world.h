//
//  world.h
//  bitter-dungeon
//
//  Created by Jack McKinney on 6/07/2015.
//  Copyright (c) 2015 Jack McKinney. All rights reserved.
//

#ifndef __bitter_dungeon__world__
#define __bitter_dungeon__world__

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#endif /* defined(__bitter_dungeon__world__) */
#define max_x 100
#define max_y 100

class World {
    std::string filename;
    sf::Texture worldtextures;
    sf::Sprite tiles[max_x][max_y];
    int tilesize;
    int dimensions[2];
    
    // we read this stuff from the file in load()
public:
    void load(std::string fname){
        std::ifstream loadfile(fname);
        filename = fname;
        sf::Texture tileTexture;
        std::string tileLocation;
        if (loadfile.is_open())
        {
            loadfile >> tileLocation;
            loadfile >> tilesize;
            loadfile >> dimensions[0];
            loadfile >> dimensions[1];
        }
        for (int x = 0; x < dimensions[0]; x++)
        {
            for (int y = 0; y < dimensions[1]; y++)
            {
                std::string str;
                loadfile >> str;
                char tx = str[0] - '0';
                char ty = str[2] - '0';
                tiles[x][y].setPosition(x * tilesize, y * tilesize);
                tiles[x][y].setTextureRect(sf::IntRect(tx, ty * tilesize, tilesize, tilesize));
            }
        }
    }
    sf::Sprite getBlock(int x, int y){
        return tiles[x][y];
    }
};

class Block {
    sf::Sprite sprite;
    int type[2];
public:
    Block (sf::Sprite a, int b[2]) : sprite(a), type{b[0], b[1]} {}
    sf::Sprite getSprite(){
        return sprite;
    }
    void setSprite(sf::Sprite newsprite){
        sprite = newsprite;
    }
    int getType();
};

class Bricks: public Block{
public:
    Bricks (sf::Sprite a, int b[2]) : Block(a,b) {}
    int* getType(){
        int type[2] {0, 0};
        return type;
    };
    bool access(){
        return false;
    };
};

class Dirt: public Block{
public:
    Dirt (sf::Sprite a, int b[2]) : Block(a,b) {}
    int* getType(){
        int type[2] {0, 1};
        return type;
    }
    bool access(){
        return true;
    };
};