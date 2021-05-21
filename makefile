./bin/ship: ./objects/spaceship.o ./objects/blasteroids.o ./include/blasteroids_header.h
	gcc ./objects/spaceship.o ./objects/blasteroids.o ./include/blasteroids_header.h -o ./bin/ship `pkg-config --libs allegro-5 allegro_font-5 allegro_primitives-5`

./objects/spaceship.o: ./src/spaceship.c
	gcc ./src/spaceship.c -c -o ./objects/spaceship.o `pkg-config --libs allegro-5 allegro_font-5 allegro_primitives-5`

./objects/blasteroids.o: ./src/blasteroids.c
	gcc ./src/blasteroids.c -c -o ./objects/blasteroids.o `pkg-config --libs allegro-5 allegro_font-5 allegro_primitives-5`