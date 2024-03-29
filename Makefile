TARGET = ./bin/cnake

CC = g++

CFLAG = -g -Wall -std=c++17 -O3
LIBS = -lSDL2 -lSDL2main -lSDL2_image -lSDL2_ttf -lSDL2_mixer

ifeq ($(OS),Windows_NT)
	CFLAG += -Isdl2/include -Lsdl2/lib -mwindows -static-libgcc -static-libstdc++ -static
	LIBS += -lmingw32 -lusp10 -lrpcrt4 -lm -ldinput8 -ldxguid -ldxerr8 -luser32 -lgdi32 -lwinmm -limm32 -lole32 -loleaut32 -lshell32 -lsetupapi -lversion -luuid
endif

PREF_SRC = ./src/
PREF_OBJ = ./obj/
SRC = $(wildcard $(PREF_SRC)*.cpp ) 
OBJ = $(patsubst $(PREF_SRC)%.cpp, $(PREF_OBJ)%.o, $(SRC))

$(TARGET) : $(OBJ)
	$(CC) $(CVER) $(OBJ) -o $(TARGET) $(CFLAG) $(LIBS)

$(PREF_OBJ)%.o : $(PREF_SRC)%.cpp
	@echo "- Building $<..."

	@$(CC) $(CVER) -c $< -o $@ $(CFLAG)

clean :
	@rm $(TARGET) $(PREF_OBJ)*.o
	
	@echo "- Done!"
	
