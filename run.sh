rm builds/main
g++ src/*.c* -I ./include -I ./resources -L ./lib -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl -o builds/main
./builds/main
