# Compiladores
CC = gcc
CXX = g++

# Flags para compilación
CFLAGS = -Wall -O2 -Iinclude
CXXFLAGS = -Wall -O2 -Iinclude

# Flags para enlazar con SDL 1.2 estático
LDLIBS = -lSDL_image -lSDL

# Directorios
SRCDIR = src
INCDIR = include
OBJDIR = obj
BINDIR = build
TARGET = $(BINDIR)/game_c4droid

# Archivos fuente y objetos
SRC_C = $(wildcard $(SRCDIR)/*.c)
SRC_CPP = $(wildcard $(SRCDIR)/*.cpp)
OBJ_C = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC_C))
OBJ_CPP = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRC_CPP))
OBJ = $(OBJ_C) $(OBJ_CPP)

# Regla principal
all: $(TARGET)

# Regla para compilar el ejecutable
$(TARGET): $(OBJ)
	@mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDLIBS)

# Regla para compilar archivos C
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)  # Asegura que la carpeta obj esté creada
	$(CC) $(CFLAGS) -c -o $@ $<

# Regla para compilar archivos C++
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)  # Asegura que la carpeta obj esté creada
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Limpieza
clean:
	rm -rf $(BINDIR) $(OBJDIR)  