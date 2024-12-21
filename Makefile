
TARGET = test

# Encuentra automáticamente los archivos .cpp y .c en src/
SOURCES = $(wildcard src/*.cpp) $(wildcard src/*.c)
OBJS = $(patsubst %.cpp,%.o,$(patsubst %.c,%.o,$(SOURCES)))

LIBS = -lSDL_image -lSDL -lpng -ljpeg  -lz -lpspaudio -lpspgu -lpspirkeyb -lpsppower -lpsphprm -lm -lstdc++
CFLAGS = -O3 -G0 -Wall -DPSP
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)
INCDIR += ./include
 
EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = game v1
PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak
