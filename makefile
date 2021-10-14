CC = gcc
DEPS = ./include/blasteroids.h
OBJ =  ./objects/spaceship.o ./objects/blasteroids.o ./include/blasteroids.h ./objects/blast.o ./objects/asteroid.o  ./objects/collisions.o
CFLAGS = `pkg-config --libs allegro-5 allegro_font-5 allegro_primitives-5 allegro_image-5 allegro_ttf-5` -lm -lpthread


./bin/ship: $(OBJ)
	@mkdir -p $(@D)
	$(CC) $(OBJ) -o $@ $(CFLAGS)

./objects/spaceship.o: ./src/spaceship.c ./include/blasteroids.h ./objects/asteroid.o
	@mkdir -p $(@D)
	$(CC) -c -o $@ $< $(CFLAGS)

./objects/%.o: ./src/%.c $(DEPS)
	@mkdir -p $(@D)
	$(CC) -c -o $@ $< $(CFLAGS)
