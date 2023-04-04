CC = gcc
SRC_DIR = ./src/
OBJ_DIR = ./objects/
SRC_FILES= $(wildcard $(SRC_DIR)*.c)
OBJ= $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC_FILES))
CFLAGS = `pkg-config --cflags --libs allegro_main-5 allegro_font-5 allegro_primitives-5 allegro_image-5 allegro_ttf-5 allegro_audio-5 allegro_acodec-5`
CFLAGS += -lm -Wno-unused-command-line-argument -g

./bin/ship: $(OBJ)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(OBJ) -o $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(@D)
	$(CC) $< $(CFLAGS) -c -o $@

clean:
	rm -rf ./objects
	rm ./bin/ship