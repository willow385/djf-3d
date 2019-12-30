/* NOTICE posted 30 December 2019

I am archiving much of my old code from when I was first learning to program. The code in this repository is embarassingly bad, and it's not how I would write code to do something similar today. Please don't take this repository as an example of my programming habits and knowledge; look at my more recent repositories instead. */


# djf-3d
A basic 3d graphics engine in C++

This engine relies on the SDL2 API; however, some of the components are designed to work with multiple possible graphics
backends for portability's sake. (use `sudo apt-get install libsdl2-dev` to install SDL on Ubuntu or other Debian)

3d rendering is where I find object-oriented programming to be most useful. I have therefore written much of the engine
in an object-oriented style. This is why I used C++ instead of pure C to write the engine.

Each subdirectory (other than `engine`) contains a `main.cpp` file and a `README.txt` file which gives instructions for how
to compile and run it.
