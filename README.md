# Blasteroids
#### Video Demo:[Here](https://youtu.be/Cg35O7ELH5Q)
#### Description:
## Asteroids clone

## Description
A book called "Head First C" has this as it's last exercise.

This project was started in Ubuntu Linux, but then transfered to MacOS with an M1 chip.
So some things have changed.

It's written in C with the help of allegro5.

## File Breakdown
1. blasteroids.c:
    * Main function goes here and it goes through the main loop. 
    * Takes care of a rendering
    * Takes care of initialisation
    * Frees allocated memory
2. asteroid.c:
    * draws the bitmap for the asteroids
    * makes asteroids rotate
    * spawns and draws asteroids
3. collisions.c:
    * uses box collision to affect the player or the asteroids
4. ship.c:
    * This is the player
    * Takes cares of the lives
    * Takes care of the bitmap of the ship, and the lives of the player
    * Takes care of controls
5. blast.c:
    * Spawns circles that act as bullets

## Compilation
For most reliable results, install allegro5 from source code:

    https://github.com/liballeg/allegro5

Alternatively you can use brew:

    brew install allegro5

or apt:

    sudo apt-get install liballegro5-dev

Then run 
    
    make

Binary will be `bin/ship`


## TODO
- Make the Asteroids spawn in waves
- Make the Asteroids split in two every time they are shot
- Add a score
- Create a Menu with a scoreboard, options, play and exit options
- Package it and give it an installer so people who can't program or mess around with git, can still play it
