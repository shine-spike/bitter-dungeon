
//
// Disclamer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// In order to load the resources like cute_image.png, you have to set up
// your target scheme:
//
// - Select "Edit Scheme…" in the "Product" menu;
// - Check the box "use custom working directory";
// - Fill the text field with the folder path containing your resources;
//        (e.g. your project folder)
// - Click OK.
//

#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#define max_dimension 100

constexpr int windowWidth = 640, windowHeight = 640;

class Block{
    int type;
    sf::Sprite sprite;
public:
    Block (int a, sf::Sprite b) {type=a; sprite=b;}
    Block () {}
    int getType(){
        return type;
    }
    sf::Sprite getSprite(){
        return sprite;
    }
    void setSprite(sf::Sprite set){
        sprite = set;
    }
    void setDirection(int dir){
        sprite.setRotation(dir * 90);
    }
    bool canAccess(){
        if (type == 10 || type == 20 || type == 40 || type == 50 || type == 70){
            return true;
        }
        else{
            return false;
        }
    }
    
};

class Mob{
    sf::Sprite sprite;
public:
    Mob (sf::Sprite a) {sprite = a;}
    Mob () { }

    sf::Sprite getSprite(){
        return sprite;
    }
    sf::Sprite setSprite(sf::Sprite a){
        sprite = a;
    }
    void move(float x, float y){
        sprite.setPosition(sprite.getPosition().x + x, sprite.getPosition().y + y);
    }
    void setDirection(int dir){
        sprite.setRotation(dir * 90);
    }
    sf::Vector2i getPosition(){
        return sf::Vector2i((sprite.getPosition().x - 16)/32, (sprite.getPosition().y - 16)/32);
    }
};

inline void draw(Block block_grid[][max_dimension], std::string bro, sf::Texture worldtexture, int wwidth, int wheight, int twidth){
    std::ifstream tilefile(bro);
    std::string texturefile;
    
    if (tilefile.is_open()){
        tilefile >> texturefile;
        tilefile >> wwidth;
        tilefile >> wheight;
        tilefile >> twidth;
    }
    
    worldtexture.loadFromFile(texturefile);
    for (int x = 0; x < wheight; x++){
        for (int y = 0; y < wwidth; y++){
            std::string str;
            tilefile >> str;
            sf::Vector2i pos((str[0] - '0') * twidth, (str[1] - '0') * twidth);
            sf::Sprite cursprite;
            cursprite.setTexture(worldtexture);
            cursprite.setOrigin(twidth/2, twidth/2);
            cursprite.setTextureRect(sf::IntRect(pos.x, pos.y, twidth, twidth));
            cursprite.setPosition((y + 0.5) * twidth, (x + 0.5) * twidth);
            block_grid[x][y] = Block((str[0] - '0') * 10 + (str[1] - '0'), cursprite);
        }
    }
}

int main(int argc, char const** argv)
{
    // Create the main window and other important variables
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Dungeon");
    window.setFramerateLimit(60);
    Block blocks[max_dimension][max_dimension];
    int wwidth, wheight, twidth;
    sf::Texture worldtexture;
    std::ifstream tilefile("world1.txt");
    std::string texturefile;
    
    if (tilefile.is_open()){
        tilefile >> texturefile;
        tilefile >> wwidth;
        tilefile >> wheight;
        tilefile >> twidth;
    }
    
    worldtexture.loadFromFile(texturefile);
    for (int x = 0; x < wheight; x++){
        for (int y = 0; y < wwidth; y++){
            std::string str;
            tilefile >> str;
            sf::Vector2i pos((str[0] - '0') * twidth, (str[1] - '0') * twidth);
            sf::Sprite cursprite;
            cursprite.setTexture(worldtexture);
            cursprite.setOrigin(twidth/2, twidth/2);
            cursprite.setTextureRect(sf::IntRect(pos.x, pos.y, twidth, twidth));
            cursprite.setPosition((y + 0.5) * twidth, (x + 0.5) * twidth);
            blocks[x][y] = Block((str[0] - '0') * 10 + (str[1] - '0'), cursprite);
        }
    }


    // Create the Main Character
    sf::Texture mctexture;
    mctexture.loadFromFile("mc.png");
    sf::Sprite mcsprite(mctexture);
    mcsprite.setOrigin(16, 16);
    Mob mc(mcsprite);
    mc.move(336, 336);
    int chose_direction[2]{0,0};
    int dirv = -1;
    int time = 0;
    
    // Main Loop
    sf::Event event;
    while (window.isOpen()){
        sf::Vector2i mcpos = mc.getPosition();
        
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up) {
                chose_direction[0] = 0;
                chose_direction[1] = -1;
                dirv = 2;
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down) {
                chose_direction[0] = 0;
                chose_direction[1] = 1;
                dirv = 0;
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left) {
                chose_direction[0] = -1;
                chose_direction[1] = 0;
                dirv = 1;
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right) {
                chose_direction[0] = 1;
                chose_direction[1] = 0;
                dirv = 3;
            }
            if ((chose_direction[0] != 0 || chose_direction[1] || 0)){
                mc.setDirection(dirv);
                if (blocks[mcpos.y + chose_direction[1]][mcpos.x + chose_direction[0]].canAccess()){
                    mc.move(chose_direction[0] * twidth, chose_direction[1] * twidth);
                }
                dirv = -1;
                chose_direction[0] = 0;
                chose_direction[1] = 0;
            }
        }
        
        for (int x = 0; x < wheight; x++){
            for (int y = 0; y < wwidth; y++){
                window.draw(blocks[x][y].getSprite());
            }
        }
        
        window.draw(mc.getSprite());
        window.display();
        time = (time + 1) % 60;
    }
    return EXIT_SUCCESS;
}