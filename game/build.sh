COMPILE="g++ -g -std=c++17 ./src/*.cpp -I./include -o ./bin/prog -w -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -ldl"
echo ${COMPILE}
eval $COMPILE
