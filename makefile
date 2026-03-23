CC = gcc
SRC_DIR = ./src/
OBJ_DIR = ./objects/
BIN_PATH = ./bin/game
SRC_FILES = $(wildcard $(SRC_DIR)*.c)
OBJ = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC_FILES))

# Detect OS
UNAME_S := $(shell uname -s)
$(info Detected OS: $(UNAME_S))

# Allegro source version
ALLEGRO_VERSION = 5.2.10
ALLEGRO_REPO    = https://github.com/liballeg/allegro5.git
DEPS_DIR        = deps
ALLEGRO_SRC     = $(DEPS_DIR)/allegro5
ALLEGRO_BUILD   = $(DEPS_DIR)/allegro5_build
ALLEGRO_DIR     = $(DEPS_DIR)/allegro5_install

# Number of parallel jobs (macOS uses sysctl, Linux uses nproc)
ifeq ($(UNAME_S),Darwin)
    JOBS = $(shell sysctl -n hw.ncpu)
    ALLEGRO_LIBS = -lallegro_main -lallegro -lallegro_font -lallegro_primitives \
                   -lallegro_image -lallegro_ttf -lallegro_audio -lallegro_acodec
    ALLEGRO_SENTINEL = $(ALLEGRO_DIR)/lib/liballegro.dylib
endif
ifeq ($(UNAME_S),Linux)
    JOBS = $(shell nproc)
    ALLEGRO_LIBS = -lallegro -lallegro_font -lallegro_primitives \
                   -lallegro_image -lallegro_ttf -lallegro_audio -lallegro_acodec
    ALLEGRO_SENTINEL = $(ALLEGRO_DIR)/lib/liballegro.so
endif

RPATH  = -Wl,-rpath,$(abspath $(ALLEGRO_DIR)/lib)
CFLAGS = -I$(ALLEGRO_DIR)/include -Wno-unused-command-line-argument -g
LDFLAGS = $(ALLEGRO_LIBS) -L$(ALLEGRO_DIR)/lib -lm $(RPATH)

.PHONY: all deps clean clean-deps run

all: deps $(BIN_PATH)

$(BIN_PATH): $(OBJ)
	@mkdir -p $(@D)
	$(CC) $(OBJ) $(LDFLAGS) -o $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(ALLEGRO_SENTINEL)
	@mkdir -p $(@D)
	$(CC) $< $(CFLAGS) -c -o $@

# Build Allegro from source if not already installed
deps: $(ALLEGRO_SENTINEL)

$(ALLEGRO_SENTINEL):
	@echo "==> Fetching Allegro $(ALLEGRO_VERSION)..."
	@if [ ! -d "$(ALLEGRO_SRC)/.git" ]; then \
		git clone --depth 1 --branch $(ALLEGRO_VERSION) $(ALLEGRO_REPO) $(ALLEGRO_SRC); \
	fi
	@echo "==> Configuring Allegro..."
	@mkdir -p $(ALLEGRO_BUILD)
	cd $(ALLEGRO_BUILD) && cmake $(CURDIR)/$(ALLEGRO_SRC) \
		-DCMAKE_BUILD_TYPE=Release \
		-DCMAKE_INSTALL_PREFIX=$(CURDIR)/$(ALLEGRO_DIR) \
		-DCMAKE_POLICY_VERSION_MINIMUM=3.5 \
		-DWANT_DEMO=OFF \
		-DWANT_EXAMPLES=OFF \
		-DWANT_TESTS=OFF \
		-DWANT_DOCS=OFF \
		-DWANT_MONOLITH=OFF
	@echo "==> Building Allegro (using $(JOBS) jobs)..."
	$(MAKE) -C $(ALLEGRO_BUILD) -j$(JOBS)
	@echo "==> Installing Allegro..."
	$(MAKE) -C $(ALLEGRO_BUILD) install
	@echo "==> Allegro $(ALLEGRO_VERSION) ready."

clean:
	rm -rf ./objects
	rm -f $(BIN_PATH)

# Remove the downloaded and built allegro (forces a full rebuild on next `make`)
clean-deps:
	rm -rf $(DEPS_DIR)

run: all
	$(BIN_PATH)
