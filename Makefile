#makefile for c4droid 

# Variables principales
TARGET = build/bin
CC     = gcc
CXX    = g++
CFLAGS = -Wall -I./include
CXXFLAGS = -Wall -I./include
LDFLAGS =  -lSDL

# Carpetas
SRC_DIR  = src
OBJ_DIR  = obj
BUILD_DIR = build


# Archivos fuente y objetos
C_SOURCES = $(wildcard $(SRC_DIR)/*.c)
CPP_SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(C_SOURCES)) \
          $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(CPP_SOURCES))

# Regla principal
all: $(BUILD_DIR) $(TARGET) $(LD_FLAGS)

# Crear la carpeta build/bin si no existe
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Crear la carpeta obj si no existe
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Enlazar el ejecutable
$(TARGET): $(OBJ_DIR) $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

# Compilar archivos .c a .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Compilar archivos .cpp a .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpiar archivos generados
clean:
	rm -rf $(OBJ_DIR) $(BUILD_DIR)

.PHONY: all clean



