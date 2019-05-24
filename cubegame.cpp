// Compile with the following:
// g++ cubegame.cpp `pkg-config --cflags --libs sdl2`

#include <SDL2/SDL.h>
#include <iostream>
#include "space.hpp"

#define CYAN 0, 150, 255
#define MAGENTA 255, 0, 5
#define BLACK 0, 0, 0

// Though I'll probably get around to making a header file for all Platonic shapes later,
// I'm just defining a quick Cube class here for this standalone program.
class Cube {
    public:
        Space s;
        CoordTriple vertices[8];
        float edge;
        float x_pos;
        float y_pos;
        float z_pos;

        void init(float e, float _x, float _y, float _z) {
            x_pos = _x;
            y_pos = _y;
            z_pos = _z;
            edge = e;
        }

        // I chose this way to write the parameters for my own benefit; it's a bit ugly but more
        // readable for me.
        void set_vertices() {
            vertices[0] = s.point_at(x_pos,        y_pos,        z_pos       );
            vertices[1] = s.point_at(x_pos + edge, y_pos,        z_pos       );
            vertices[2] = s.point_at(x_pos + edge, y_pos,        z_pos + edge);
            vertices[3] = s.point_at(x_pos,        y_pos,        z_pos + edge);

            vertices[4] = s.point_at(x_pos,        y_pos + edge, z_pos       );
            vertices[5] = s.point_at(x_pos + edge, y_pos + edge, z_pos       );
            vertices[6] = s.point_at(x_pos + edge, y_pos + edge, z_pos + edge);
            vertices[7] = s.point_at(x_pos,        y_pos + edge, z_pos + edge);
        }

        // big wall of code to draw the kyoob
        void draw_cube(SDL_Renderer *r) {
            // draw the top face
            for (int i = 0; i < 3; ++i) {
                SDL_RenderDrawLine(
                    r,
                    s.convert_to_2d(vertices[i]).x,
                    s.convert_to_2d(vertices[i]).y,
                    s.convert_to_2d(vertices[i+1]).x,
                    s.convert_to_2d(vertices[i+1]).y
                );
            }

            // draw the bottom face
            for (int i = 4; i < 7; ++i) {
                SDL_RenderDrawLine(
                    r,
                    s.convert_to_2d(vertices[i]).x,
                    s.convert_to_2d(vertices[i]).y,
                    s.convert_to_2d(vertices[i+1]).x,
                    s.convert_to_2d(vertices[i+1]).y
                );
            }

            // draw the lines connecting the two faces
            SDL_RenderDrawLine(
                r,
                s.convert_to_2d(vertices[0]).x,
                s.convert_to_2d(vertices[0]).y,
                s.convert_to_2d(vertices[3]).x,
                s.convert_to_2d(vertices[3]).y
            );

            SDL_RenderDrawLine(
                r,
                s.convert_to_2d(vertices[4]).x,
                s.convert_to_2d(vertices[4]).y,
                s.convert_to_2d(vertices[7]).x,
                s.convert_to_2d(vertices[7]).y
            );

            for (int i = 0; i < 4; ++i) {
                SDL_RenderDrawLine(
                    r,
                    s.convert_to_2d(vertices[i]).x,
                    s.convert_to_2d(vertices[i]).y,
                    s.convert_to_2d(vertices[i+4]).x,
                    s.convert_to_2d(vertices[i+4]).y
                );
            }
        }

        void y_rot(float degrees) {
            for (int i = 0; i < 8; ++i) {
                vertices[i] = s.y_rotation(
                    vertices[i],
                    s.point_at(x_pos + (edge / 2), y_pos + (edge/2), z_pos + (edge / 2)),
                    degrees
                );
            }
        }

        void x_rot(float degrees) {
            for (int i = 0; i < 8; ++i) {
                vertices[i] = s.x_rotation(
                    vertices[i],
                    s.point_at(x_pos + (edge / 2), y_pos + (edge/2), z_pos + (edge / 2)),
                    degrees
                );
            }
        }

        void z_rot(float degrees) {
            for (int i = 0; i < 8; ++i) {
                vertices[i] = s.z_rotation(
                    vertices[i],
                    s.point_at(x_pos + (edge / 2), y_pos + (edge/2), z_pos + (edge / 2)),
                    degrees
                );
            }
        }
};

int main() {
    SDL_Renderer *renderer;
    SDL_Window *main_window;
    SDL_Init(SDL_INIT_VIDEO);
    main_window = SDL_CreateWindow(
        "Use the keys Q, W, E, A, S, D to rotate cube",
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
    space.set_depth_to(170);
    space.set_screen_center(300, 300);

    // two cubes fro anaglyphic effect
    Cube cyan;
    Cube magenta;
    cyan.s = space;
    magenta.s = space;

    magenta.init(
        200, // length of edges
        196, // x-position
        200, // y-position
        30   // z-position
    );
    cyan.init(
        200,
        204,
        200,
        30
    );
    cyan.set_vertices();
    magenta.set_vertices();

    while (window_open) {
        SDL_SetRenderDrawColor(renderer, BLACK, 0);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, CYAN, 255);
        cyan.draw_cube(renderer);
        SDL_SetRenderDrawColor(renderer, MAGENTA, 255);
        magenta.draw_cube(renderer);
        SDL_RenderPresent(renderer);

        SDL_PollEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                window_open = false;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_q:
                        cyan.z_rot(-0.8);
                        magenta.z_rot(-0.8);
                        break;
                    case SDLK_e:
                        cyan.z_rot(0.8);
                        magenta.z_rot(0.8);
                        break;
                    case SDLK_w:
                        cyan.x_rot(-0.8);
                        magenta.x_rot(-0.8);
                        break;
                    case SDLK_s:
                        cyan.x_rot(0.8);
                        magenta.x_rot(0.8);
                        break;
                    case SDLK_a:
                        cyan.y_rot(-0.8);
                        magenta.y_rot(-0.8);
                        break;
                    case SDLK_d:
                        cyan.y_rot(0.8);
                        magenta.y_rot(0.8);
                        break;
                }
                break;
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(main_window);
    SDL_Quit();
    return 0;
}
