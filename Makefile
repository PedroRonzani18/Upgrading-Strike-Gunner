CC = g++
FLAGS= -g -lglut -lGL -lGLU -lSOIL -lSDL2_mixer -Wall -std=c++14 -O2
OUTPUT= ./Bin/ctc
all:
	@ echo "Building target using GCC compile:"
	@$(CC) -g *.cpp */*/*.cpp $(FLAGS) -o $(OUTPUT)

run: all
	@ echo "Running $(OUTPUT):"
	@./$(OUTPUT)

clean:
	rm -f $(OUTPUT)