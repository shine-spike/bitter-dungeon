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
    sf::Sprite tiles[max_x][max_y];
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
            loadfile >> dimensions[0];
            loadfile >> dimensions[1];
        }
    }
};