# DOSSIERS
BIN_DIR	= bin
INC_DIR = -I include
SRC_DIR	= src
OBJ_DIR	= obj
# FICHIERS
SRC_FILES 	= $(shell find $(SRC_DIR)/ -type f -name '*.cpp')
OBJ_FILES 	= $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o, $(SRC_FILES))
EXEC_BIN	= projet.out
# FLAG
CFLAGS = -Wall -O3
# INCLUDES
LDFLAGS = -lglut -lGLEW -lGLU -lGL -lm 
# Compilateur
CC = g++

all : $(OBJ_FILES)

projet : $(OBJ_FILES)
	@mkdir -p $(BIN_DIR)/
	$(CC) -o $(BIN_DIR)/$(EXEC_BIN) $(OBJ_FILES) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p "$(@D)"
	$(CC) -c $< -o $@ $(CFLAGS) $(INC_DIR)

clean:
	rm -rf *~
	rm -rf $(SRC_DIR)/*/*~
	rm -rf $(OBJ_DIR)/
	rm -rf $(BIN_DIR)/*
