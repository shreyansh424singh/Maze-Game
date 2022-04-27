
filename = game

all:
	g++ $(filename).cpp -w -lSDL2 -lSDL2_image -o $(filename).out

run:	$(filename).out
	./$(filename).out

clean:
	rm *.out
