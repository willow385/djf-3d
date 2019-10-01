// Compile with the following:
// g++ main.cpp `pkg-config --cflags --libs sdl2`

#include <iostream>
#include <string>
#include <sstream>
#include "../engine/djf-3d.hpp"

#define GREEN 0, 255, 70
#define BLACK 0, 0, 0

// this handy function was copied almost verbatim from StackOverflow
// https://stackoverflow.com/a/5794022/10942736
std::string convert_to_str(float number) {
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

    // I will now create some instances of the Plane class from "plane.hpp".
    Plane plane0;
    plane0.set_space(space);
    plane0.set_height(15);
    plane0.set_y_val(500);
    plane0.init_triangles();

    Plane plane1;
    plane1.set_space(space);
    plane1.set_height(15);
    plane1.set_y_val(500);
    plane1.init_triangles();

    Plane plane2;
    plane2.set_space(space);
    plane2.set_height(15);
    plane2.set_y_val(500);
    plane2.init_triangles();

    Plane plane3;
    plane3.set_space(space);
    plane3.set_height(15);
    plane3.set_y_val(500);
    plane3.init_triangles();

    plane1.x_trans_plane(15.0 * 0x20);
    plane2.z_trans_plane( 7.5 * 0x20);
    plane3.x_trans_plane(15.0 * 0x20);
    plane3.z_trans_plane( 7.5 * 0x20);

    // The next four values are displayed on the screen.
    float xpos = 300;
    float ypos = 200;
    float zpos = 0;
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
            "*** CONTROLS ***",
            16, /* length of the string */
            GREEN,
            255
        );
        render_string(
            renderer,
            1,
            21,
            "W/S - move forwards/back",
            24,
            GREEN,
            255
        );
        render_string(
            renderer,
            1,
            31,
            "A/D - move left/right",
            21,
            GREEN,
            255
        );
        render_string(
            renderer,
            1,
            41,
            "Q/E - turn left/right",
            21,
            GREEN,
            255
        );
        render_string(
            renderer,
            1,
            51,
            "up/down arrow keys - move up/down",
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
        std::string xbuf = "x-pos = " + convert_to_str(xpos);
        render_string(
            renderer,
            1,
            76,
            xbuf.c_str(),
            strlen(xbuf.c_str()),
            GREEN,
            255
        );
        std::string ybuf = "y-pos = " + convert_to_str(ypos);
        render_string(
            renderer,
            1,
            86,
            ybuf.c_str(),
            strlen(ybuf.c_str()),
            GREEN,
            255
        );
        std::string zbuf = "z-pos = " + convert_to_str(zpos);
        render_string(
            renderer,
            1,
            96,
            zbuf.c_str(),
            strlen(zbuf.c_str()),
            GREEN,
            255
        );
        std::string angbuf = "theta = " + convert_to_str(angle) + " DEGREES";
        render_string(
            renderer,
            1,
            106,
            angbuf.c_str(),
            strlen(angbuf.c_str()),
            GREEN,
            255
        );

        SDL_SetRenderDrawColor(renderer, GREEN, 255);

        plane0.draw_plane(renderer, 600);
        plane1.draw_plane(renderer, 600);
        plane2.draw_plane(renderer, 600);
        plane3.draw_plane(renderer, 600);

        SDL_RenderPresent(renderer);

        while (SDL_PollEvent(&event)) { // by putting this in a while loop, we eliminate lag
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
                            plane0.x_trans_plane(1);
                            plane1.x_trans_plane(1);
                            plane2.x_trans_plane(1);
                            plane3.x_trans_plane(1);
                            break;
                        case SDLK_d:
                            xpos++;
                            plane0.x_trans_plane(-1);
                            plane1.x_trans_plane(-1);
                            plane2.x_trans_plane(-1);
                            plane3.x_trans_plane(-1);
                            break;
                        case SDLK_w:
                            zpos++;
                            plane0.z_trans_plane(-1);
                            plane1.z_trans_plane(-1);
                            plane2.z_trans_plane(-1);
                            plane3.z_trans_plane(-1);
                            break;
                        case SDLK_s:
                            zpos--;
                            plane0.z_trans_plane(1);
                            plane1.z_trans_plane(1);
                            plane2.z_trans_plane(1);
                            plane3.z_trans_plane(1);
                            break;
                        case SDLK_DOWN:
                            ypos--;
                            plane0.y_trans_plane(-1);
                            plane1.y_trans_plane(-1);
                            plane2.y_trans_plane(-1);
                            plane3.y_trans_plane(-1);
                            break;
                        case SDLK_UP:
                            ypos++;
                            plane0.y_trans_plane(1);
                            plane1.y_trans_plane(1);
                            plane2.y_trans_plane(1);
                            plane3.y_trans_plane(1);
                            break;
                        case SDLK_q:
                            angle--;
                            plane0.rotate_plane(-1);
                            plane1.rotate_plane(-1);
                            plane2.rotate_plane(-1);
                            plane3.rotate_plane(-1);
                            break;
                        case SDLK_e:
                            angle++;
                            plane0.rotate_plane(1);
                            plane1.rotate_plane(1);
                            plane2.rotate_plane(1);
                            plane3.rotate_plane(1);
                            break;
                    }
                    break; // end of keypress case

                default:
                    break;
            }
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(main_window);
    SDL_Quit();
    return 0;
}
