
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
    void setType(int ntype){
        type = ntype;
    }
};

int main(int argc, char const** argv)
{
    // Create the main window and other important variables
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Dungeon");
    window.setFramerateLimit(30);
    window.setVerticalSyncEnabled(true);
    Block blocks[max_dimension][max_dimension];
    std::ifstream tilefile("world1.txt");
    std::string texturefile;
    int wwidth, wheight, twidth;
    
    if (tilefile.is_open()){
        tilefile >> texturefile;
        tilefile >> wwidth;
        tilefile >> wheight;
        tilefile >> twidth;
    }
    
    sf::Texture worldtexture;
    worldtexture.loadFromFile(texturefile);
    
    for (int x = 0; x < wheight; x++){
        for (int y = 0; y < wwidth; y++){
            std::string str;
            tilefile >> str;
            sf::Vector2i pos((str[0] - '0') * twidth, (str[2] - '0') * twidth);
            sf::Sprite cursprite;
            cursprite.setTexture(worldtexture);
            cursprite.setTextureRect(sf::IntRect(pos.x, pos.y, twidth, twidth));
            cursprite.setPosition(x * twidth, y * twidth);
            blocks[x][y] = Block((str[0] - '0') * 10 + (str[2] - '0'), cursprite);
        }
    }
    
    // Main Loop
    sf::Event event;
    while (window.isOpen()){
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }
        
        //Render Tilemap
        
        for (int x = 0; x < wheight; x++){
            for (int y = 0; y < wwidth; y++){
                window.draw(blocks[x][y].getSprite());
            }
        }
        
        window.display();
    }
    return EXIT_SUCCESS;
}
