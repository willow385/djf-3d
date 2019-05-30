# djf-3d
A basic 3d graphics engine in C++

NOTE: the `.cpp` files aren't components of a greater whole; they are standalone programs written to demonstrate djf-3d.
The engine itself is made out of `.hpp` and `.h` files.

As I continue to develop this, some components may come to rely on the SDL2 API; however, many of the components are
designed to work with multiple possible graphics backends for portability's sake.  (use `sudo apt-get install libsdl2-dev` to
install SDL on Ubuntu or other Debian)

3d rendering is where I find object-oriented programming to be most useful. I have therefore written much of the engine
in an object-oriented style. This is why I used C++ instead of pure C to write the engine.

As of 29 May 2019, the coolest of these is in the subdirectory `world`. Do check it out.
