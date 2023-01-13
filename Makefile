CC = g++
FLAGS= -g -lglut -lGL -lGLU -lSOIL -lSDL2_mixer -Wall -std=c++14 -O2
OUTPUT= main
all:
	@$(CC) -g *.cpp */*/*.cpp $(FLAGS) -o $(OUTPUT)

run: all
	./$(OUTPUT)

clean:
		rm *.o -f