./bin/ship: ./objects/spaceship.o ./objects/blasteroids.o ./include/blasteroids.h ./objects/blast.o ./objects/asteroid.o  ./objects/collisions.o
	@mkdir -p $(@D)
	gcc ./objects/spaceship.o ./objects/blasteroids.o ./include/blasteroids.h ./objects/blast.o ./objects/asteroid.o  ./objects/collisions.o -o ./bin/ship `pkg-config --libs allegro-5 allegro_font-5 allegro_primitives-5 allegro_image-5 allegro_ttf-5` -lm -lpthread 

./objects/spaceship.o: ./src/spaceship.c ./include/blasteroids.h ./objects/asteroid.o
	@mkdir -p $(@D)
	gcc ./src/spaceship.c -c -o ./objects/spaceship.o `pkg-config --libs allegro-5 allegro_font-5 allegro_primitives-5 allegro_image-5 allegro_ttf-5` -lm -lpthread

./objects/blasteroids.o: ./src/blasteroids.c ./include/blasteroids.h
	@mkdir -p $(@D)
	gcc ./src/blasteroids.c -c -o ./objects/blasteroids.o `pkg-config --libs allegro-5 allegro_font-5 allegro_primitives-5 allegro_image-5 allegro_ttf-5` -lm -lpthread

./objects/blast.o: ./src/blast.c ./include/blasteroids.h
	@mkdir -p $(@D)
	gcc ./src/blast.c -c -o ./objects/blast.o `pkg-config --libs allegro-5 allegro_font-5 allegro_primitives-5 allegro_image-5 allegro_ttf-5` -lm -lpthread

./objects/asteroid.o: ./src/asteroid.c ./include/blasteroids.h
	@mkdir -p $(@D)
	gcc ./src/asteroid.c -c -o ./objects/asteroid.o `pkg-config --libs allegro-5 allegro_font-5 allegro_primitives-5 allegro_image-5 allegro_ttf-5` -lm -lpthread

./objects/collisions.o: ./src/collisions.c ./include/blasteroids.h
	@mkdir -p $(@D)
	gcc ./src/collisions.c -c -o ./objects/collisions.o `pkg-config --libs allegro-5 allegro_font-5 allegro_primitives-5 allegro_image-5 allegro_ttf-5` -lm -lpthread
