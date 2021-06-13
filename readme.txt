This project is linked against:
SDL2
SDL2_image
SDL2_mixer.h

SETUP: 
sudo apt-cache search libsdl2
sudo apt-get install libsdl2-dev
sudo apt-cache search libsdl2-image
sudo apt-get install libsdl2-image-dev
sudo apt-get install libsdl2-mixer-dev

RUN: 
g++ 01_hello_cpp.cpp -w -lSDL2 -lSDL2_image -lSDL2_mixer -o a.out && ./a.out

