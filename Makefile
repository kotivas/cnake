TARGET = ./bin/cnake

CC = g++

CFLAG = -g -Wall
LIBS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

PREF_SRC = ./src/
PREF_OBJ = ./obj/
PREF_SRC_UI = ./src/ui/
SRC = $(wildcard $(PREF_SRC)*.cpp $(PREF_SRC_UI)*.cpp) 
OBJ = $(patsubst $(PREF_SRC)%.cpp, $(PREF_OBJ)%.o, $(SRC))

$(TARGET) : $(OBJ)
	$(CC) $(CVER) $(OBJ) -o $(TARGET) $(CFLAG) $(LIBS)

	@echo "Done!"

$(PREF_OBJ)%.o : $(PREF_SRC)%.cpp
	$(CC) $(CVER) -c $< -o $@ $(CFLAG)

clean :
	rm $(TARGET) $(PREF_OBJ)*.o $(PREF_OBJ_UI)*.o
	
	@echo "Done!"
	
