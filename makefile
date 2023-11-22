CC = gcc
SRC_DIR = ./src/
OBJ_DIR = ./objects/
BIN_PATH = ./bin/game
SRC_FILES = $(wildcard $(SRC_DIR)*.c)
OBJ = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC_FILES))

# Detect OS
UNAME_S := $(shell uname -s)

# Echo the OS
$(info Detected OS: $(UNAME_S))

# Set Allegro library paths based on OS
ifeq ($(UNAME_S),Linux)
    ALLEGRO_DIR = ./lib/allegro_linux
    ALLEGRO_LIBS = -lallegro -lallegro_font -lallegro_primitives -lallegro_image -lallegro_ttf -lallegro_audio -lallegro_acodec
    RPATH = -Wl,-rpath,$(ALLEGRO_DIR)/lib/
endif
ifeq ($(UNAME_S),Darwin)
    ALLEGRO_DIR = ./lib/allegro_osx
    ALLEGRO_LIBS = -lallegro_main -lallegro -lallegro_font -lallegro_primitives -lallegro_image -lallegro_ttf -lallegro_audio -lallegro_acodec
    RPATH = -Wl,-rpath,@executable_path/../lib/allegro/lib/
endif

CFLAGS = -I$(ALLEGRO_DIR)/include -Wno-unused-command-line-argument -g
LDFLAGS = $(ALLEGRO_LIBS) -L$(ALLEGRO_DIR)/lib -lm $(RPATH)


$(BIN_PATH): $(OBJ)
	@mkdir -p $(@D)
	$(CC) $(OBJ) $(LDFLAGS) -o $@ -v

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(@D)
	$(CC) $< $(CFLAGS) -c -o $@

clean:
	rm -rf ./objects
	rm $(BIN_PATH)

run:
	$(BIN_PATH)
