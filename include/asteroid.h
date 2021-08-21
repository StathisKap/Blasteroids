void spawn_asteroid();
void draw_asteroid();
void update_asteroid();

typedef struct {
	float sx;
	float sy;
	float heading;
	float twist;
	float speed;
	float rot_velocity;
	float scale;
	int gone;
	ALLEGRO_COLOR color;
} Asteroid;