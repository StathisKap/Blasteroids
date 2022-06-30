void draw_bullet();
void fire_bullet();
void update_bullet();

typedef struct
{
	float sx; //Where it is on the screen
	float sy;
	float heading;
	bool live; //is it dead?
	ALLEGRO_COLOR color;
	ALLEGRO_BITMAP *image;
	mask_t * mask;
	float size;
} Bullet;
