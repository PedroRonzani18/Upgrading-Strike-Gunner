CC = g++
FLAGS= -g -lglut -lGL -lGLU -lSOIL -lSDL2_mixer -Wall -std=c++20 -O2
OUTPUT= ./ctc
all:
	@ echo "Building target using GCC compile:"
	@$(CC) -g *.cpp */*/*.cpp $(FLAGS) -o $(OUTPUT)

run: all
	@ echo "Running $(OUTPUT):"
	@./$(OUTPUT)

exec:
	@ echo "Running $(OUTPUT):"
	@./$(OUTPUT)

clean:
	rm -f $(OUTPUT)