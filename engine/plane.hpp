#ifndef SDL2_SDL_H
#define SDL2_SDL_H
#include <SDL2/SDL.h>
#endif

#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP
#include "triangle.hpp"
#endif // TRIANGLE_HPP

#include <stdexcept> // to ensure I don't go out of bounds, because C++ doesn't check array bounds

class Plane {
private:
    Space s;
    Triangle ground[0x20][0x20]; // using hexadecimal numbers, just to be extra pretentious
    float height; // height of each triangle
    float y_val; // y-coordinate of the plane

public:
    Space get_space() {
        Space ret = s;
        return ret;
    }

    // A Plane has to exist in a Space. Otherwise where does it exist?
    void set_space(Space _s) {
        s = _s;
    }

    Triangle get_triangle_index(int index_a, int index_b) {
        if (index_a > 0x20 || index_b > 0x20) {
            throw std::invalid_argument("Error - attempted to access illegal array index");
        }

        Triangle ret = ground[index_a][index_b];
        return ret;
    }

    /* Method for initializing the values of all the Triangles in the Plane.
    The methods set_space(), set_height(), and set_y_val() should be called
    before this method is called. */
    void init_triangles() {
        for (int y = 0; y < 0x20; ++y) {
            for (int x = 0; x < 0x20; ++x) {
                // Each of the triangles will be in the same space.
                ground[y][x].set_space(s);

                // The triangles will be offset so that they form an isometric
                // grid.
                if (y % 2 == 0) {
                    ground[y][x].set_angle0(
                        x * height,
                        y_val,
                        (y * (height / 2)) + 0
                    );
                    ground[y][x].set_angle1(
                        (x * height) - (height / 2),
                        y_val,
                        (y * (height / 2)) + (height / 2)
                    );
                    ground[y][x].set_angle2(
                        (x * height) + (height / 2),
                        y_val,
                        (y * (height / 2)) + (height / 2)
                    );
                } else {
                    ground[y][x].set_angle0(
                        (x * height) + (height / 2),
                        y_val,
                        (y * (height / 2)) + 0
                    );
                    ground[y][x].set_angle1(
                        x * height,
                        y_val,
                        (y * (height / 2)) + (height / 2)
                    );
                    ground[y][x].set_angle2(
                        (x * height) + height,
                        y_val,
                        (y * (height / 2)) + (height / 2)
                    );
                } // end of if/else clause to determine offset amount
            } // end of for-loop for columns
        } // end of for-loop for rows
    } // end of function body
    /* tfw your brackets are so deeply nested that you need comments just
    to remember what scope they terminate lol */

    void set_y_val(float val) {
        y_val = val;
    }

    float get_y_val() {
        float ret = y_val;
        return ret;
    }

    void set_height(float val) {
        height = val;
    }

    float get_height() {
        float ret = height;
        return ret;
    }

    // method to draw the plane using an SDL_Renderer
    int draw_plane(SDL_Renderer *r, float bound) {
        int ret = 0;
        for (int y = 0; y < 0x20; ++y) {
            for (int x = 0; x < 0x20; ++x) {
                ret += ground[y][x].draw_self(r, 600);
            }
        }
        return ret;
    }

    // next three methods are for moving the plane around in space
    void x_trans_plane(float amount) {
        for (int y = 0; y < 0x20; ++y) {
            for (int x = 0; x < 0x20; ++x) {
                ground[y][x].x_trans(amount);
            }
        }
    }

    void y_trans_plane(float amount) {
        for (int y = 0; y < 0x20; ++y) {
            for (int x = 0; x < 0x20; ++x) {
                ground[y][x].y_trans(amount);
            }
        }
    }

    void z_trans_plane(float amount) {
        for (int y = 0; y < 0x20; ++y) {
            for (int x = 0; x < 0x20; ++x) {
                ground[y][x].z_trans(amount);
            }
        }
    }

    // and this method rotates the plane about the y-axis
    void rotate_plane(float degrees) {
        for (int y = 0; y < 0x20; ++y) {
            for (int x = 0; x < 0x20; ++x) {
                ground[y][x].y_rot_about(
                    // this call determines where in the Space the observer must be
                    s.point_at(
                        s.get_screen_center().x,
                        (s.get_screen_center().y * 2) - y_val,
                        -(0x20 * (height / 2))
                    ),
                    degrees
                );
            } // end of for-loop for columns
        } // end of for-loop for rows
    } // end of function body
}; // end of  Plane class definition

/* Moving the code for planes into a class wound up having more total lines of code, but fewer
lines of code in main.cpp, which I count as a win since fewer lines tends to mean better readability.
One thing's for sure: I find main.cpp to be a lot more readable this way. */
