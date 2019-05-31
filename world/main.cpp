// Compile with the following:
// g++ main.cpp `pkg-config --cflags --libs sdl2`

#include <iostream>
#include <string>
#include <sstream>
#include "triangle.hpp"
#include "djf-SDL-text.h"

#define GREEN 0, 255, 70
#define BLACK 0, 0, 0

// this handy function was copied almost verbatim from StackOverflow
// https://stackoverflow.com/a/5794022/10942736
std::string convert_to_str(float number){
    std::ostringstream buff;
    buff << number;
    return buff.str();
}

int main() {
    /* One criticism I have of SDL is that it requires a fair amount
    of boilerplate code. I understand why this code is necessary and
    appreciate the control it gives me, but the only thing I really want
    to do diffferent from one SDL program to the next is the window
    title and maybe the window size. */
    SDL_Renderer *renderer;
    SDL_Window *main_window;
    SDL_Init(SDL_INIT_VIDEO);
    main_window = SDL_CreateWindow(
        "Dante's 3d world",
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

    // We must have an instance of the Space class in which
    // our pretty shapes reside.
    Space space;
    space.set_depth_to(300);
    space.set_screen_center(300, 300);

    // I'm making a grid of 1024 triangles which will be the ground.
    Triangle ground[0x20][0x20];
    for (int y = 0; y < 0x20; ++y) {
        for (int x = 0; x < 0x20; ++x) {
            // Each of the triangles will be in the same space.
            ground[y][x].set_space(space);

            // The triangles will be offset so that they form an isometric
            // grid.
            if (y % 2 == 0) {
                ground[y][x].set_angle0(
                    x * 15,
                    500,
                    (y * 7.5) + 0
                );
                ground[y][x].set_angle1(
                    (x * 15) - 7.5,
                    500,
                    (y * 7.5) + 7.5
                );
                ground[y][x].set_angle2(
                    (x * 15) + 7.5,
                    500,
                    (y * 7.5) + 7.5
                );
            } else {
                ground[y][x].set_angle0(
                    (x * 15) + 7.5,
                    500,
                    (y * 7.5) + 0
                );
                ground[y][x].set_angle1(
                    x * 15,
                    500,
                    (y * 7.5) + 7.5
                );
                ground[y][x].set_angle2(
                    (x * 15) + 15,
                    500,
                    (y * 7.5) + 7.5
                );
            }
        }
    }

    CoordTriple observer; // the point from which we see
    observer.x = 300;
    observer.y = 200;
    observer.z = -(0x20 * 7.5);

    // The next four values are displayed on the screen.
    float xpos = observer.x;
    float ypos = observer.y;
    float zpos = observer.z;
    float angle = 0;

    while (window_open) {
        if (angle >= 360) {
            angle = 0;
        }
        if (angle < 0) {
            angle = 359;
        }

        SDL_SetRenderDrawColor(renderer, BLACK, 0);
        SDL_RenderClear(renderer);
        render_string(
            renderer, /* rendering context */
            1, /* top-left corner of the string */
            11,
            /* as of 29 May 2019 we do not yet support all ascii chars */
            "*** CONTROLS ***",
            16, /* length of the string */
            GREEN,
            255
        );
        render_string(
            renderer,
            1,
            21,
            "W/S - MOVE FORWARDS/BACK",
            24,
            GREEN,
            255
        );
        render_string(
            renderer,
            1,
            31,
            "A/D - MOVE LEFT/RIGHT",
            21,
            GREEN,
            255
        );
        render_string(
            renderer,
            1,
            41,
            "Q/E - TURN LEFT/RIGHT",
            21,
            GREEN,
            255
        );
        render_string(
            renderer,
            1,
            51,
            "UP/DOWN ARROW KEYS - MOVE UP/DOWN",
            33,
            GREEN,
            255
        );

        render_string(
            renderer,
            1,
            66,
            "*** OBSERVER POSITION RELATIVE TO WORLD ***",
            43,
            GREEN,
            255
        );
        render_string(
            renderer,
            1,
            76,
            "X-POS ",
            6,
            GREEN,
            255
        );
        std::string xbuf = convert_to_str(xpos);
        render_string(
            renderer,
            37,
            76,
            xbuf.c_str(),
            strlen(xbuf.c_str()),
            GREEN,
            255
        );
        render_string(
            renderer,
            1,
            86,
            "Y-POS ",
            6,
            GREEN,
            255
        );
        std::string ybuf = convert_to_str(ypos);
        render_string(
            renderer,
            37,
            86,
            ybuf.c_str(),
            strlen(ybuf.c_str()),
            GREEN,
            255
        );
        render_string(
            renderer,
            1,
            96,
            "Z-POS ",
            6,
            GREEN,
            255
        );
        std::string zbuf = convert_to_str(zpos);
        render_string(
            renderer,
            37,
            96,
            zbuf.c_str(),
            strlen(zbuf.c_str()),
            GREEN,
            255
        );
        render_string(
            renderer,
            1,
            106,
            "THETA ",
            6,
            GREEN,
            255
        );
        std::string angbuf = convert_to_str(angle) + " DEGREES";
        render_string(
            renderer,
            37,
            106,
            angbuf.c_str(),
            strlen(angbuf.c_str()),
            GREEN,
            255
        );

        SDL_SetRenderDrawColor(renderer, GREEN, 255);

        for (int y = 0; y < 0x20; ++y) {
            for (int x = 0; x < 0x20; ++x) {
                ground[y][x].draw_self(renderer, 600);
            }
        }

        SDL_RenderPresent(renderer);

        SDL_PollEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                window_open = false;
                break;
            case SDL_KEYUP:
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_a:
                        xpos--;
                        for (int y = 0; y < 0x20; ++y) {
                            for (int x = 0; x < 0x20; ++x) {
                                ground[y][x].x_trans(1);
                            }
                        }
                        break;
                    case SDLK_d:
                        xpos++;
                        for (int y = 0; y < 0x20; ++y) {
                            for (int x = 0; x < 0x20; ++x) {
                                ground[y][x].x_trans(-1);
                            }
                        }
                        break;
                    case SDLK_w:
                        zpos++;
                        for (int y = 0; y < 0x20; ++y) {
                            for (int x = 0; x < 0x20; ++x) {
                                ground[y][x].z_trans(-1);
                            }
                        }
                        break;
                    case SDLK_s:
                        zpos--;
                        for (int y = 0; y < 0x20; ++y) {
                            for (int x = 0; x < 0x20; ++x) {
                                ground[y][x].z_trans(1);
                            }
                        }
                        break;
                    case SDLK_UP:
                        ypos--;
                        for (int y = 0; y < 0x20; ++y) {
                            for (int x = 0; x < 0x20; ++x) {
                                ground[y][x].y_trans(-1);
                            }
                        }
                        break;
                    case SDLK_DOWN:
                        ypos++;
                        for (int y = 0; y < 0x20; ++y) {
                            for (int x = 0; x < 0x20; ++x) {
                                ground[y][x].y_trans(1);
                            }
                        }
                        break;
                    case SDLK_q:
                        angle--;
                        for (int y = 0; y < 0x20; ++y) {
                            for (int x = 0; x < 0x20; ++x) {
                                ground[y][x].y_rot_about(observer, -1);
                            }
                        }
                        break;
                    case SDLK_e:
                        angle++;
                        for (int y = 0; y < 0x20; ++y) {
                            for (int x = 0; x < 0x20; ++x) {
                                ground[y][x].y_rot_about(observer, 1);
                            }
                        }
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
