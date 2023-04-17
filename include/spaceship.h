#ifndef INCLUDE_SPACESHIP_H_
	#define INCLUDE_SPACESHIP_H_
#endif // INCLUDE_SPACESHIP_H_

typedef struct {
	float sx; //Where it is on the screen
	float sy;//*
	float heading; //The direction it's pointing
	float speed;
	float drift;
	float scale;
	bool live; //is it dead?
	ALLEGRO_COLOR color;
	ALLEGRO_BITMAP *image;
	ALLEGRO_TRANSFORM transform;
} Spaceship;

void draw_ship(); //Draws the ship
void draw_flame(); //Draws the flame when it goes forward
void KeysForSpaceship(); // Reads the keystate of the keys and does stuff
void Respawn();
void draw_lives();
void LifeUp(int points);
