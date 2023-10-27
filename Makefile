TARGET = ./bin/snake

CC = g++

CFLAG = -g -Wall
LIBS = -lSDL2 -lSDL2_image -lSDL2_ttf

PREF_SRC = ./src/
PREF_OBJ = ./obj/

SRC = $(wildcard $(PREF_SRC)*.cpp) 
OBJ = $(patsubst $(PREF_SRC)%.cpp, $(PREF_OBJ)%.o, $(SRC))

$(TARGET) : $(OBJ)
	$(CC) $(CVER) $(OBJ) -o $(TARGET) $(CFLAG) $(LIBS)

	@echo "Done!"

$(PREF_OBJ)%.o : $(PREF_SRC)%.cpp
	$(CC) $(CVER) -c $< -o $@

clean :
	rm $(TARGET) $(PREF_OBJ)*.o
	
	@echo "Done!"