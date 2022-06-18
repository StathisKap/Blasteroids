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
	mask_t * mask;
	ALLEGRO_TRANSFORM transform;
} Spaceship;

void draw_ship(); //Draws the ship
void draw_flame(); //Draws the flame when it goes forward
void KeysForSpaceship(); 
void Create_Ship_Mask();
void Ship_Init();