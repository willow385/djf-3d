*** Compiling instructions ***

0. Make sure that the directory structure matches this github repo

1. Run the following command:
    g++ main.cpp -o world `pkg-config --cflags --libs sdl2`

2. You can now run the executable with the command:
    ./world
