
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


constexpr int windowWidth = 800, windowHeight = 600;

int main(int argc, char const** argv)
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
    // Set the Icon
    
    sf::Image icon;
    if (!icon.loadFromFile("icon.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    
//    // Load a sprite to display
//    sf::Texture texture;
//    if (!texture.loadFromFile("cute_image.jpg")) {
//        return EXIT_FAILURE;
//    }
//    sf::Sprite sprite(texture);
//    
//    // Create a graphical text to display
//    sf::Font font;
//    if (!font.loadFromFile("sansation.ttf")) {
//        return EXIT_FAILURE;
//    }
//    sf::Text text("Hello SFML", font, 50);
//    text.setColor(sf::Color::Black);
//    
//    // Load a music to play
//    sf::Music music;
//    if (!music.openFromFile("nice_music.ogg")) {
//        return EXIT_FAILURE;
//    }
//    
//    // Play the music
//    music.play();
//    
    // Start the game loop
    
    int tproportions[2] {20, 15};
    
    std::ifstream openfile("world1.txt");
    
    sf::Texture tileTexture;
    sf::Sprite tiles;
    
    sf::Vector2i map[100][100];
    sf::Vector2i loadCounter = sf::Vector2i(0,0);
    
    
    if (openfile.is_open())
    {
        std::string tileLocation;
        openfile >> tileLocation;
        tileTexture.loadFromFile(tileLocation);
        tiles.setTexture(tileTexture);
        while (!openfile.eof())
        {
            std::string str;
            openfile >> str;
            char x = str[0];
            char y = str[2];
            if (!isdigit(x) || !isdigit(y))
            {
                map[loadCounter.x][loadCounter.y] = sf::Vector2i(-1, -1 );
            }
            else
            {
                map[loadCounter.x][loadCounter.y] = sf::Vector2i(x - '0', y - '0');
            }
            if (openfile.peek() == '\n')
            {
                loadCounter.x = 0;
                loadCounter.y++;
            }
            else
                loadCounter.x++;
        }
        loadCounter.y++;
    }
    
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            
            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }
        
        // Clear screen
        window.clear(sf::Color::White);

        
        for (int i = 0; i < tproportions[0]; i++)
        {
            for (int j = 0; j < tproportions[1]; j++)
            {
                if (map[i][j].x != -1 && map[i][j].y != -1)
                {
//                    std::cout << i << " " << j << "\n";
                    tiles.setPosition(i * 40, j * 40);
                    tiles.setTextureRect(sf::IntRect(map[i][j].x * 40, map[i][j].y * 40, 40, 40));
                    window.draw(tiles);
                }
            }
        }
        
//        // Draw the sprite
//        window.draw(sprite);
//        
//        // Draw the string
//        window.draw(text);
        
        // Update the window
        window.display();
        std::cout << "\n\n\n";
    }
    
}
