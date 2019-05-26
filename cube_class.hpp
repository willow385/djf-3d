#ifndef SDL2_SDL_H
#define SDL2_SDL_H
#include <SDL2/SDL.h>
#endif

#ifndef SPACE_HPP
#define SPACE_HPP
#include "space.hpp"
#endif

#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif

// Yes, this is copied almost verbatim from "cubegame.cpp".
class Cube {
    // One difference being that its state variables are private.
    private:
        Space s;
        CoordTriple vertices[8];
        float edge;
        float x_pos;
        float y_pos;
        float z_pos;

    public:
        // Set the dimensions and location of the cube
        void init(float e, float _x, float _y, float _z) {
            x_pos = _x;
            y_pos = _y;
            z_pos = _z;
            edge = e;
        }

        // get a copy of one of the vertices
        // (or print an error message and exit if the index is out of bounds)
        CoordTriple get_vertex(int index) {
            CoordTriple ret;
            if (index < 8) {
                ret = vertices[index];
            } else {
                std::cout << "Error! Attempted to access illegal array index!\n";
                exit(1);
            }
            return ret;
        }

        // make sure you call init() before you call this
        void set_vertices() {
            vertices[0] = s.point_at(x_pos,        y_pos,        z_pos);
            vertices[1] = s.point_at(x_pos + edge, y_pos,        z_pos);
            vertices[2] = s.point_at(x_pos + edge, y_pos,        z_pos + edge);
            vertices[3] = s.point_at(x_pos,        y_pos,        z_pos + edge);

            vertices[4] = s.point_at(x_pos,        y_pos + edge, z_pos);
            vertices[5] = s.point_at(x_pos + edge, y_pos + edge, z_pos);
            vertices[6] = s.point_at(x_pos + edge, y_pos + edge, z_pos + edge);
            vertices[7] = s.point_at(x_pos,        y_pos + edge, z_pos + edge);
        }

        // this stuff relies on the SDL API to work but could probably be refactored
        // to use a different graphics backend with relatively little pain
        void draw_cube(SDL_Renderer *r) {
            for (int i = 0; i < 3; ++i) {
                SDL_RenderDrawLine(
                    r,
                    s.convert_to_2d(vertices[i]).x,
                    s.convert_to_2d(vertices[i]).y,
                    s.convert_to_2d(vertices[i+1]).x,
                    s.convert_to_2d(vertices[i+1]).y
                );
            }

            SDL_RenderDrawLine(
                r,
                s.convert_to_2d(vertices[0]).x,
                s.convert_to_2d(vertices[0]).y,
                s.convert_to_2d(vertices[3]).x,
                s.convert_to_2d(vertices[3]).y
            );

            for (int i = 4; i < 7; ++i) {
                SDL_RenderDrawLine(
                    r,
                    s.convert_to_2d(vertices[i]).x,
                    s.convert_to_2d(vertices[i]).y,
                    s.convert_to_2d(vertices[i+1]).x,
                    s.convert_to_2d(vertices[i+1]).y
                );
            }

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

        // these next three functions allow us to apply the rotation methods of the Space
        // class on all vertices at once, rather than having to call it for all eight of them
        // individually
        void y_rot_self(float degrees) {
            for (int i = 0; i < 8; ++i) {
                vertices[i] = s.y_rotation(
                    vertices[i],
                    s.point_at(x_pos + (edge / 2), y_pos + (edge/2), z_pos + (edge / 2)),
                    degrees
                );
            }
        }

        void x_rot_self(float degrees) {
            for (int i = 0; i < 8; ++i) {
                vertices[i] = s.x_rotation(
                    vertices[i],
                    s.point_at(x_pos + (edge / 2), y_pos + (edge/2), z_pos + (edge / 2)),
                    degrees
                );
            }
        }

        void z_rot_self(float degrees) {
            for (int i = 0; i < 8; ++i) {
                vertices[i] = s.z_rotation(
                    vertices[i],
                    s.point_at(x_pos + (edge / 2), y_pos + (edge/2), z_pos + (edge / 2)),
                    degrees
                );
            }
        }

        // the next three methods also allow us to rotate the cube, but differently.
        // The previous three methods rotate a cube *about itself* (i.e., about the
        // point at its geometric center). These next three, on the other hand, allow
        // us to rotate the cube *about any other point*. The point about which to rotate
        // the cube is passed as the first argument in each function.
        void y_rot_about(CoordTriple about, float degrees) {
            for (int i = 0; i < 8; ++i) {
                vertices[i] = s.y_rotation(
                    vertices[i],
                    about,
                    degrees
                );
            }
        }

        void x_rot_about(CoordTriple about, float degrees) {
            for (int i = 0; i < 8; ++i) {
                vertices[i] = s.x_rotation(
                    vertices[i],
                    about,
                    degrees
                );
            }
        }

        void z_rot_about(CoordTriple about, float degrees) {
            for (int i = 0; i < 8; ++i) {
                vertices[i] = s.z_rotation(
                    vertices[i],
                    about,
                    degrees
                );
            }
        }
};
