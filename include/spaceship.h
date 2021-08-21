void draw_ship(); //Draws the ship
void draw_flame(); //Draws the flame when it goes forward

typedef struct {
	float sx; //Where it is on the screen
	float sy;//*
	float heading; //The direction it's pointing
	float speed;
	float drift;
	float scale;
	bool live; //is it dead?
	ALLEGRO_COLOR color;
} Spaceship;