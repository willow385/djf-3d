*** Compiling instructions ***

0. Make sure that the following are all in the same
directory as `main.cpp':
    3d_types.hpp
    djf-SDL-text.h (from 29 May 2019 or later)
    space.hpp  
    triangle.hpp

1. Run the following command:
    g++ main.cpp -o world `pkg-config --cflags --libs sdl2`

2. You can now run the executable with the command:
    ./world
