CC = gcc
DEPS = ./include/blasteroids.h
OBJ =  ./objects/spaceship.o ./objects/blasteroids.o ./objects/blast.o ./objects/asteroid.o  ./objects/collisions.o
CFLAGS = `pkg-config --libs allegro-5 allegro_font-5 allegro_primitives-5 allegro_image-5 allegro_ttf-5` -lm -lpthread -lallegro_main -Wno-unused-command-line-argument


./bin/ship: $(OBJ)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(OBJ) -o $@
./objects/spaceship.o: ./src/spaceship.c ./include/blasteroids.h ./objects/asteroid.o
	@mkdir -p $(@D)
	$(CC)  $< $(CFLAGS) -c -o $@

./objects/%.o: ./src/%.c $(DEPS)
	@mkdir -p $(@D)
	$(CC) $< $(CFLAGS) -c -o $@
