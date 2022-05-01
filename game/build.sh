COMPILE="g++ -g -std=c++17 ./src/*.cpp -I./include -o ./bin/prog -w -lSDL2 -lSDL2_image -ldl"
echo ${COMPILE}
eval $COMPILE
