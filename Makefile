all:
	g++ -g -std=c++17 ./src/Dot.cpp ./src/DynamicText.cpp ./src/LTexture.cpp ./src/Music.cpp ./src/client.cpp ./src/main.cpp ./src/server.cpp -I./include -o ./bin/prog -w -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -ldl

run:
	./bin/prog

clean:
	rm *.out
