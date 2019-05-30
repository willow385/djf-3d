#ifndef SPACE_HPP
#define SPACE_HPP
#include "space.hpp"
#endif

#ifndef SDL2_SDL_H
#define SDL2_SDL_H
#include <SDL2/SDL.h>
#endif // SDL2_SDL_H

// this is a class instead of a typedef struct because
// having explicitly associated methods for the Triangle
// makes Triangles a lot more useful to me
class Triangle {
    private:
        CoordTriple angle0;
        CoordTriple angle1;
        CoordTriple angle2;
        Space s;
    public:
        // determine exactly what space the triangle is in
        void set_space(Space _s) {
            s = _s;
        }

        Space get_space() {
            Space _s = s;
            return _s;
        }

        CoordTriple get_angle0() {
            CoordTriple ret = angle0;
            return ret;
        }

        CoordTriple get_angle1() {
            CoordTriple ret = angle1;
            return ret;
        }

        CoordTriple get_angle2() {
            CoordTriple ret = angle2;
            return ret;
        }

        void set_angle0(float _x, float _y, float _z) {
            angle0.x = _x;
            angle0.y = _y;
            angle0.z = _z;
        }

        void set_angle1(float _x, float _y, float _z) {
            angle1.x = _x;
            angle1.y = _y;
            angle1.z = _z;
        }

        void set_angle2(float _x, float _y, float _z) {
            angle2.x = _x;
            angle2.y = _y;
            angle2.z = _z;
        }

        /* It can be very useful to know where the exact geometric
        center of the triangle is. Every triangle has such a center.
        Therefore, the Triangle class comes with a method for finding
        where its center is.

        This links to the page where I learned how to do this:
        https://tinyurl.com/trig345
        */
        CoordTriple geo_center() {
            float x_coord = (angle0.x + angle1.x + angle2.x) / 3;
            float y_coord = (angle0.y + angle1.y + angle2.y) / 3;
            float z_coord = (angle0.z + angle1.z + angle2.z) / 3;
            return s.point_at(x_coord, y_coord, z_coord);
        }

        // The next three methods are for rotating the triangle around
        // its own centroid (exact center).
        void x_rot_self(float degrees) {
            CoordTriple center = geo_center();
            angle0 = s.x_rotation(angle0, center, degrees);
            angle1 = s.x_rotation(angle1, center, degrees);
            angle2 = s.x_rotation(angle2, center, degrees);
        }

        void y_rot_self(float degrees) {
            CoordTriple center = geo_center();
            angle0 = s.y_rotation(angle0, center, degrees);
            angle1 = s.y_rotation(angle1, center, degrees);
            angle2 = s.y_rotation(angle2, center, degrees);
        }

        void z_rot_self(float degrees) {
            CoordTriple center = geo_center();
            angle0 = s.z_rotation(angle0, center, degrees);
            angle1 = s.z_rotation(angle1, center, degrees);
            angle2 = s.z_rotation(angle2, center, degrees);
        }

        // The next three methods are for rotating the triangle about any
        // other point.
        void x_rot_about(CoordTriple about, float degrees) {
            angle0 = s.x_rotation(angle0, about, degrees);
            angle1 = s.x_rotation(angle1, about, degrees);
            angle2 = s.x_rotation(angle2, about, degrees);
        }

        void y_rot_about(CoordTriple about, float degrees) {
            angle0 = s.y_rotation(angle0, about, degrees);
            angle1 = s.y_rotation(angle1, about, degrees);
            angle2 = s.y_rotation(angle2, about, degrees);
        }

        void z_rot_about(CoordTriple about, float degrees) {
            angle0 = s.z_rotation(angle0, about, degrees);
            angle1 = s.z_rotation(angle1, about, degrees);
            angle2 = s.z_rotation(angle2, about, degrees);
        }

        // finally, a method for drawing the triangle. These are dependent
        // on the SDL2 API but this could easily be tweaked to work with any
        // other graphics API.
        int draw_self(SDL_Renderer *renderer, float bound) {
            int ret = 0; // error value
            ret += SDL_RenderDrawLine(
                renderer,
                s.convert_to_2d(angle0).x,
                s.convert_to_2d(angle0).y,
                s.convert_to_2d(angle1).x,
                s.convert_to_2d(angle1).y
            );
            ret += SDL_RenderDrawLine(
                renderer,
                s.convert_to_2d(angle1).x,
                s.convert_to_2d(angle1).y,
                s.convert_to_2d(angle2).x,
                s.convert_to_2d(angle2).y
            );
            ret += SDL_RenderDrawLine(
                renderer,
                s.convert_to_2d(angle2).x,
                s.convert_to_2d(angle2).y,
                s.convert_to_2d(angle0).x,
                s.convert_to_2d(angle0).y
            );
            return ret;
        }

        // Methods for transforming the triangle in space.
        void x_trans(float distance) {
            angle0.x = angle0.x + distance;
            angle1.x = angle1.x + distance;
            angle2.x = angle2.x + distance;
        }

        void y_trans(float distance) {
            angle0.y = angle0.y + distance;
            angle1.y = angle1.y + distance;
            angle2.y = angle2.y + distance;
        }

        void z_trans(float distance) {
            angle0.z = angle0.z + distance;
            angle1.z = angle1.z + distance;
            angle2.z = angle2.z + distance;
        }
};
