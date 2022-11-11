# pacccsusss
#include<iostream>
#include "SFML/Graphics.hpp"
using namespace std;

enum DIRECTIONS { LEFT, RIGHT, UP, DOWN }; //left is 0, right is 1, up is 2, down is 3
int main() {
    //game set up (you'll need these lines in every game)
    sf::RenderWindow screen(sf::VideoMode(1040, 1020), "amogus but pacman"); //set up screen
    sf::Event event; //set up event queue
    sf::Clock clock; //set up the clock (needed for game timing)
    const float FPS = 60.0f; //FPS
    screen.setFramerateLimit(FPS); //set FPS

    //load in images
    sf::Texture brick;
    brick.loadFromFile("amogus.png");
    sf::Sprite wall;
    wall.setTexture(brick);

    sf::Texture button;
    button.loadFromFile("emergency.png");
    sf::Sprite pellet;
    pellet.setTexture(button);

    int map[14][13] = {
        1,1,1,1,1,1,1,1,1,1,1,1,1,
        1,2,2,2,2,2,2,2,2,2,2,2,1,
        1,1,1,1,2,2,1,1,2,2,1,1,1,
        1,2,1,2,2,2,1,2,2,2,2,2,1,
        1,2,2,2,1,1,2,2,1,1,2,2,1,
        1,1,2,2,2,1,2,2,2,1,2,2,1,
        1,2,2,1,2,2,2,1,2,1,1,2,1,
        1,2,1,1,1,2,1,1,2,1,1,2,1,
        1,2,2,2,2,2,0,2,2,1,2,2,1,
        1,2,2,1,1,1,1,1,2,1,2,2,1,
        1,2,2,2,2,2,2,2,2,2,2,2,1,
        1,1,1,1,1,1,1,1,1,1,1,1,1
    };


   //player/////////////////////////////////////////////////////
    int xpos = 480;
    int ypos = 640;
    int vx = 0;
    int vy = 0;
    //sf::CircleShape circle(35);
    int radius = 35;
    sf::Texture player;
    player.loadFromFile("imposter.png");; //using RGB value for color here (hex also works)
    sf::Sprite sus;
    sus.setTexture(player);
    sus.setPosition(xpos, ypos); //top left "corner" of circle (not center!)
    bool keys[] = { false, false, false, false };

    //################### HOLD ONTO YOUR BUTTS, ITS THE GAME LOOP###############################################################
    while (screen.isOpen()) {//keep window open until user shuts it down

        while (screen.pollEvent(event)) { //look for events-----------------------

            //this checks if the user has clicked the little "x" button in the top right corner
            if (event.type == sf::Event::EventType::Closed)
                screen.close();
            //KEYBOARD INPUT 
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                keys[LEFT] = true;
            }
            else keys[LEFT] = false;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                keys[RIGHT] = true;
            }
            else keys[RIGHT] = false;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                keys[UP] = true;
            }
            else keys[UP] = false;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                keys[DOWN] = true;
            }
            else keys[DOWN] = false;
        }//end event loop---------------------------------------------------------------
        //move Mr. Pac
        if (keys[LEFT] == true) {
            vx = -4;
            keys[RIGHT] = false;
            keys[UP] = false;
            keys[DOWN] = false;
        }
        else if (keys[RIGHT] == true) {
            vx = 4;
            keys[LEFT] = false;
            keys[UP] = false;
            keys[DOWN] = false;
        }
        else if (keys[UP] == true) {
            vy = -4;
            keys[RIGHT] = false;
            keys[LEFT] = false;
            keys[DOWN] = false;
        }
        else if (keys[DOWN] == true) {
            vy = 4;
            keys[RIGHT] = false;
            keys[UP] = false;
            keys[LEFT] = false;
        }
        else {
            if(vx != 0){
                //xpos += vx;
                vy = 0;
            }

            else if (vy != 0) {
               // ypos += vy;
                vx = 0;
            }
            
        }


        //collision//////////

        if (vx > 0 && map[(ypos) / 80][(xpos + radius * 2 + 5) / 80] == 1)
            vx = 0;
        if (vx < 0 && map[(ypos) / 80][(xpos -5) / 80] == 1)
            vx = 0;

        if (vy > 0 && map[(ypos + radius * 2 + 5) / 80][(xpos ) / 80] == 1)
            vy = 0;
        if (vy < 0 && map[(ypos - 5) / 80][(xpos) / 80] == 1)
            vy = 0;

        //nom nom/////////////////////////////

        if (map[(ypos) / 80][(xpos + radius * 2 + 3) / 80] == 2)
            map[ypos/80][xpos/80] = 0;

        //update player
        xpos += vx;
        ypos += vy;
        sus.setPosition(xpos, ypos);


       
        

                //render section-----------------------------------------
        screen.clear(); //wipes screen, without this things smear
        for (int rows = 0; rows < 14; rows++)
            for (int cols = 0; cols < 13; cols++) {
                if (map[rows][cols] == 1) {
                    wall.setPosition(cols * 80, rows * 80);
                    screen.draw(wall);
                }
                if (map[rows][cols] == 2) {
                    pellet.setPosition(cols * 80, rows * 80);
                    screen.draw(pellet);
                }
            }
        screen.draw(sus); //draw player
        screen.display(); //flips memory drawings onto screen

    }//######################## end game loop ###################################################################################

    cout << "goodbye!" << endl;
} //end of main
