// Compile with the following:
// g++ 3d_anim.cpp `pkg-config --cflags --libs sdl2`

#include <SDL2/SDL.h>
#include <iostream>
#include <thread>
#include <chrono>
#include "axes.hpp"

#define CYAN 0, 150, 255
#define MAGENTA 255, 0, 100
#define BLACK 0, 0, 0

int main() {
    SDL_Renderer *renderer;
    SDL_Window *main_window;
    SDL_Init(SDL_INIT_VIDEO);
    main_window = SDL_CreateWindow(
        "Anaglyphic Axis Rotation in C++ by Dante Falzone",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        600,
        600,
        0
    );
    renderer = SDL_CreateRenderer(
        main_window,
        0,
        0
    );
    if (main_window == NULL || renderer == NULL) {
        std::cout << "Error! Something went horribly wrong!\n";
        std::cout << "Error: " << SDL_GetError() << '\n';
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(main_window);
        SDL_Quit();
        return 1;
    }

    bool window_open = true;
    SDL_Event event;

    // these variables offset the two sets of axes
    int ashift = 306;
    int bshift = 294;

    Space s0; // the Space class does point manipulation and abstracts calculation for us
    Space s1;
    Axes a; // the Axes class defines a set of lines based on the Space class and the Line3d type
    Axes b;
    s0.set_depth_to(130);
    s0.set_screen_center(300, 300);
    s1.set_depth_to(130);
    s1.set_screen_center(300, 300);
    a.space = s0;
    a.init(100, ashift, 300);
    b.space = s1;
    b.init(100, bshift, 300);

    while (window_open) {
        std::this_thread::sleep_for(std::chrono::milliseconds(50)); // delay framerate
        SDL_SetRenderDrawColor(renderer, BLACK, 0);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, CYAN, 255);

        // because the Space and Axes classes are graphics-API-agnostic, we have
        // to do the grunt work of translating their calculations into SDL function
        // calls ourselves
        SDL_RenderDrawLine(
            renderer,
            a.space.convert_to_2d(a.x_axis.endpoint_0).x,
            a.space.convert_to_2d(a.x_axis.endpoint_0).y,
            a.space.convert_to_2d(a.x_axis.endpoint_1).x,
            a.space.convert_to_2d(a.x_axis.endpoint_1).y
        );
        SDL_RenderDrawLine(
            renderer,
            a.space.convert_to_2d(a.y_axis.endpoint_0).x,
            a.space.convert_to_2d(a.y_axis.endpoint_0).y,
            a.space.convert_to_2d(a.y_axis.endpoint_1).x,
            a.space.convert_to_2d(a.y_axis.endpoint_1).y
        );
        SDL_RenderDrawLine(
            renderer,
            a.space.convert_to_2d(a.z_axis.endpoint_0).x,
            a.space.convert_to_2d(a.z_axis.endpoint_0).y,
            a.space.convert_to_2d(a.z_axis.endpoint_1).x,
            a.space.convert_to_2d(a.z_axis.endpoint_1).y
        );

        SDL_SetRenderDrawColor(renderer, MAGENTA, 255);

        SDL_RenderDrawLine(
            renderer,
            b.space.convert_to_2d(b.x_axis.endpoint_0).x,
            b.space.convert_to_2d(b.x_axis.endpoint_0).y,
            b.space.convert_to_2d(b.x_axis.endpoint_1).x,
            b.space.convert_to_2d(b.x_axis.endpoint_1).y
        );
        SDL_RenderDrawLine(
            renderer,
            b.space.convert_to_2d(b.y_axis.endpoint_0).x,
            b.space.convert_to_2d(b.y_axis.endpoint_0).y,
            b.space.convert_to_2d(b.y_axis.endpoint_1).x,
            b.space.convert_to_2d(b.y_axis.endpoint_1).y
        );
        SDL_RenderDrawLine(
            renderer,
            b.space.convert_to_2d(b.z_axis.endpoint_0).x,
            b.space.convert_to_2d(b.z_axis.endpoint_0).y,
            b.space.convert_to_2d(b.z_axis.endpoint_1).x,
            b.space.convert_to_2d(b.z_axis.endpoint_1).y
        );

        SDL_RenderPresent(renderer);

        // this giant code wall performs 1-degree rotations on our points along the x and z axes
        a.x_axis.endpoint_0 = a.space.x_rotation(a.x_axis.endpoint_0, a.space.point_at(ashift, 300, 0), 1);
        a.x_axis.endpoint_1 = a.space.x_rotation(a.x_axis.endpoint_1, a.space.point_at(ashift, 300, 0), 1);
        a.y_axis.endpoint_0 = a.space.x_rotation(a.y_axis.endpoint_0, a.space.point_at(ashift, 300, 0), 1);
        a.y_axis.endpoint_1 = a.space.x_rotation(a.y_axis.endpoint_1, a.space.point_at(ashift, 300, 0), 1);
        a.z_axis.endpoint_0 = a.space.x_rotation(a.z_axis.endpoint_0, a.space.point_at(ashift, 300, 0), 1);
        a.z_axis.endpoint_1 = a.space.x_rotation(a.z_axis.endpoint_1, a.space.point_at(ashift, 300, 0), 1);

        a.x_axis.endpoint_0 = a.space.z_rotation(a.x_axis.endpoint_0, a.space.point_at(ashift, 300, 0), 1);
        a.x_axis.endpoint_1 = a.space.z_rotation(a.x_axis.endpoint_1, a.space.point_at(ashift, 300, 0), 1);
        a.y_axis.endpoint_0 = a.space.z_rotation(a.y_axis.endpoint_0, a.space.point_at(ashift, 300, 0), 1);
        a.y_axis.endpoint_1 = a.space.z_rotation(a.y_axis.endpoint_1, a.space.point_at(ashift, 300, 0), 1);
        a.z_axis.endpoint_0 = a.space.z_rotation(a.z_axis.endpoint_0, a.space.point_at(ashift, 300, 0), 1);
        a.z_axis.endpoint_1 = a.space.z_rotation(a.z_axis.endpoint_1, a.space.point_at(ashift, 300, 0), 1);

        b.x_axis.endpoint_0 = b.space.x_rotation(b.x_axis.endpoint_0, b.space.point_at(bshift, 300, 0), 1);
        b.x_axis.endpoint_1 = b.space.x_rotation(b.x_axis.endpoint_1, b.space.point_at(bshift, 300, 0), 1);
        b.y_axis.endpoint_0 = b.space.x_rotation(b.y_axis.endpoint_0, b.space.point_at(bshift, 300, 0), 1);
        b.y_axis.endpoint_1 = b.space.x_rotation(b.y_axis.endpoint_1, b.space.point_at(bshift, 300, 0), 1);
        b.z_axis.endpoint_0 = b.space.x_rotation(b.z_axis.endpoint_0, b.space.point_at(bshift, 300, 0), 1);
        b.z_axis.endpoint_1 = b.space.x_rotation(b.z_axis.endpoint_1, b.space.point_at(bshift, 300, 0), 1);

        b.x_axis.endpoint_0 = b.space.z_rotation(b.x_axis.endpoint_0, b.space.point_at(bshift, 300, 0), 1);
        b.x_axis.endpoint_1 = b.space.z_rotation(b.x_axis.endpoint_1, b.space.point_at(bshift, 300, 0), 1);
        b.y_axis.endpoint_0 = b.space.z_rotation(b.y_axis.endpoint_0, b.space.point_at(bshift, 300, 0), 1);
        b.y_axis.endpoint_1 = b.space.z_rotation(b.y_axis.endpoint_1, b.space.point_at(bshift, 300, 0), 1);
        b.z_axis.endpoint_0 = b.space.z_rotation(b.z_axis.endpoint_0, b.space.point_at(bshift, 300, 0), 1);
        b.z_axis.endpoint_1 = b.space.z_rotation(b.z_axis.endpoint_1, b.space.point_at(bshift, 300, 0), 1);

        SDL_PollEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                window_open = false;
                break;
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(main_window);
    SDL_Quit();
    return 0;
}
