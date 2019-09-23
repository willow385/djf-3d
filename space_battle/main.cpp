// Compile with the following:
// g++ main.cpp `pkg-config --cflags --libs sdl2`

#include <SDL2/SDL.h>
#include <iostream>

#ifndef ENGINE
#define ENGINE
#include "../engine/djf-3d.cpp"
#endif

#include "sphere.cpp"

#define GREEN 0, 255, 70
#define BLACK 0, 0, 0

int main() {
    SDL_Renderer *renderer;
    SDL_Window *main_window;
    SDL_Init(SDL_INIT_VIDEO);
    main_window = SDL_CreateWindow(
        "Space Battle! (written in C++ by Dante Falzone)",
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

    Space space;
    space.set_depth_to(800);
    space.set_screen_center(300, 300);

    Sphere universe;
    universe.set_radius(150);
    universe.set_space(space);
    universe.set_centerpoint(
        space.point_at(
            300,
            300,
            100
        )
    );
    universe.set_points();

    while (window_open) {
        SDL_SetRenderDrawColor(renderer, BLACK, 0);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, GREEN, 255);
        universe.draw_self(renderer);

        render_string(
            renderer,
            1,
            1,
            "*** Controls ***",
            16,
            GREEN,
            255
        );
        render_string(
            renderer,
            1,
            11,
            "WASD :: move up/down/left/right",
            31,
            GREEN,
            255
        );
        render_string(
            renderer,
            1,
            21,
            "X/E  :: move forwards/backwards",
            31,
            GREEN,
            255
        );
        SDL_RenderPresent(renderer);

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    window_open = false;
                    break;
                case SDL_KEYUP: break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_w:
                            universe.y_trans(5);
                            break;
                        case SDLK_a:
                            universe.x_trans(5);
                            break;
                        case SDLK_s:
                            universe.y_trans(-5);
                            break;
                        case SDLK_d:
                            universe.x_trans(-5);
                            break;
                        case SDLK_x:
                            universe.z_trans(5);
                            break;
                        case SDLK_e:
                            universe.z_trans(-5);
                            break;
                        case SDLK_UP:
                            universe.x_rot_self(1);
                            break;
                    }
                    break;
                default: break;
            }
        }
    }

    /* if any heap memory was allocated, free it here */
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(main_window);
    SDL_Quit();
    return 0;
}
