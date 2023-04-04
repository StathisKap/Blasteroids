# Blasteroids
#### Video Demo:[Here](https://youtu.be/Cg35O7ELH5Q)
#### Description:
## Asteroids clone

## Description
A book called "Head First C" has this as it's last exercise.

This project was started in Ubuntu Linux, but then transfered to MacOS with an M1 chip.
So some things have changed.

It's written in C with the help of allegro5.

Allegro is a cross-platform library mainly aimed at video game and multimedia programming. It handles common, low-level tasks such as creating windows, accepting user input, loading data, drawing images, playing sounds, etc. and generally abstracting away the underlying platform. However, Allegro is not a game engine: you are free to design and structure your program as you like.

Asteroids is a space-themed multidirectional shooter arcade game designed by Lyle Rains and Ed Logg released in November 1979 by Atari, Inc. The player controls a single spaceship in an asteroid field which is periodically traversed by flying saucers.

In this version of the games, there are no saucers and there wasn't really a plan of adding any. Certainly a possibility though, so if you wanna add it in the game and make a PR, it'd be welcomed :).

Some things that did stay are the drifting after the spaceship goes forward, the flame behind the spaceship, the asteroid and spaceship shapes (but not colours), and the way the ship and asteroids teleport when crossing the window edges.

There are no sounds as of now, and just like the saucers, there isn't really any plan to add any, but it's a possibility.

A lot of variables are part of a global struct so that we don't need to pass things around all the time.
There are a few things being printed so as to indicate what happens. Examples of that would be "Starting program, Freed memory, etc".
The structure of the project is lots of small functions that do one thing. The files are then separated in a source directory, an include directory
and when we run make, there is an objects directory and then a bin directory.

All the libararies that need to be included, are included in 1 header file, which is then included in the rest of the projects.
There are a few helper functions as well, such as error that prints nice error messages when the program fails.

All the entities on the screen get updated every frame using a respective update function. Not all objects use the same timer. As of now there are 4 timers. 1 for the whole game (frames per second), one for the fire rate, one for the asteroid rotation speed, and one for the respawn timer.


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

Then you need libraries 
    flac, dumb, and opusfile
Use the package manager of your choosing

Finally run
    
    make

Binary will be `bin/ship`


## TODO
- Create a Menu with a scoreboard, options, play and exit options
- Package it and give it an installer so people who can't program or mess around with git, can still play it
