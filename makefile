CC = gcc
SRC_DIR = ./src/
OBJ_DIR = ./objects/
BIN_PATH = ./bin/game
SRC_FILES = $(wildcard $(SRC_DIR)*.c)
OBJ = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC_FILES))

# SQLite amalgamation
SQLITE_DIR = deps/sqlite
SQLITE_OBJ = $(OBJ_DIR)sqlite3.o

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
    SQLITE_EXTRA_LIBS =
endif
ifeq ($(UNAME_S),Linux)
    JOBS = $(shell nproc)
    ALLEGRO_LIBS = -lallegro -lallegro_font -lallegro_primitives \
                   -lallegro_image -lallegro_ttf -lallegro_audio -lallegro_acodec
    ALLEGRO_SENTINEL = $(ALLEGRO_DIR)/lib/liballegro.so
    SQLITE_EXTRA_LIBS = -ldl
endif

RPATH  = -Wl,-rpath,$(abspath $(ALLEGRO_DIR)/lib)
CFLAGS = -I$(ALLEGRO_DIR)/include -I$(SQLITE_DIR) -Wno-unused-command-line-argument -g
LDFLAGS = $(ALLEGRO_LIBS) -L$(ALLEGRO_DIR)/lib -lm $(SQLITE_EXTRA_LIBS) $(RPATH)

.PHONY: all deps clean clean-deps run compile_commands

all: deps $(BIN_PATH)

$(BIN_PATH): $(OBJ) $(SQLITE_OBJ)
	@mkdir -p $(@D)
	$(CC) $(OBJ) $(SQLITE_OBJ) $(LDFLAGS) -o $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(ALLEGRO_SENTINEL)
	@mkdir -p $(@D)
	$(CC) $< $(CFLAGS) -c -o $@

$(SQLITE_OBJ): $(SQLITE_DIR)/sqlite3.c
	@mkdir -p $(@D)
	$(CC) $< -c -O2 -o $@

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

compile_commands:
	@echo '[' > compile_commands.json
	@first=1; for f in $(SRC_FILES); do \
		[ $$first -eq 0 ] && echo ',' >> compile_commands.json; \
		first=0; \
		printf '  {\n    "directory": "%s",\n    "file": "%s/%s",\n    "command": "$(CC) %s $(CFLAGS) -c -o /dev/null"\n  }' \
			"$(CURDIR)" "$(CURDIR)" "$$f" "$(CURDIR)/$$f" >> compile_commands.json; \
	done
	@echo '' >> compile_commands.json
	@echo ']' >> compile_commands.json
	@echo "==> compile_commands.json generated."

clean:
	rm -rf ./objects
	rm -f $(BIN_PATH)

# Remove the downloaded and built allegro (forces a full rebuild on next `make`)
clean-deps:
	rm -rf $(DEPS_DIR)

run: all
	$(BIN_PATH)
