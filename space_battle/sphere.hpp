#ifndef ENGINE
#define ENGINE
#include "../engine/djf-3d.hpp"
#endif

#ifndef SDL2_SDL_H
#define SDL2_SDL_H
#include <SDL2/SDL.h>
#endif

#ifndef MATH_H
#define MATH_H
#include <math.h>
#endif

#ifndef RANDOM
#define RANDOM
#include <random>
#endif

#define POINT_CT 1024 // number of points in the sphere

class Sphere {
private:
    float radius;
    Space space;
    CoordTriple centerpoint;
    CoordTriple points[POINT_CT];

    /* The following private method returns a number
    that is greater than or equal to zero and less
    than 360. */
    float random_angle() {
        std::random_device rd;
        std::uniform_int_distribution<int> dist(0, 360);
        return dist(rd);
    }

public:
    /* methods for getting and setting */
    float get_radius() {
        return radius;
    }

    CoordTriple get_centerpoint() {
        return centerpoint;
    }

    int set_radius(float value) {
        radius = value;
        return (radius == value ? 0 : 1);
    }

    int set_centerpoint(CoordTriple point) {
        centerpoint.x = point.x;
        centerpoint.y = point.y;
        centerpoint.z = point.z;

        if (centerpoint.x == point.x
        &&  centerpoint.y == point.y
        &&  centerpoint.z == point.z) {
            return 0;
        } else {
            return 1;
        }
    }

    int set_space(Space s) {
        space = s;
        return 0; // TODO: error handling
    }

    Space get_space() {
        return space;
    }

    /* method for creating the points */
    int set_points() {
        for (int i = 0; i < POINT_CT; ++i) {
            float theta = random_angle();

            // Firstly: put the points at [radius] away
            // from the centerpoint.
            points[i] = space.point_at(
                centerpoint.x,
                centerpoint.y - radius,
                centerpoint.z
            );

            // Then: perform rotations.
            points[i] = space.z_rotation(
                points[i],
                centerpoint,
                random_angle()
            );
            points[i] = space.y_rotation(
                points[i],
                centerpoint,
                random_angle()
            );
        }
        return 0;
    }

    /* method for drawing the damn thing already */
    int draw_self(SDL_Renderer *renderer) {
        int error_val;
        for (int i = 0; i < POINT_CT; ++i) {
            error_val += SDL_RenderDrawPoint(
                renderer,
                space.convert_to_2d(points[i]).x,
                space.convert_to_2d(points[i]).y
            );
        }
        return error_val;
    }

    /* method for transforming the sphere along the x-axis */
    int x_trans(float distance) {
        for (int i = 0; i < POINT_CT; ++i) {
            points[i].x += distance;
        }
        centerpoint.x += distance;
        return 0;
    }

    /* method for transforming the sphere along the y-axis */
    int y_trans(float distance) {
        for (int i = 0; i < POINT_CT; ++i) {
            points[i].y += distance;
        }
        centerpoint.y += distance;
        return 0;
    }

    /* method for transforming the sphere along the z-axis */
    int z_trans(float distance) {
        for (int i = 0; i < POINT_CT; ++i) {
            points[i].z += distance;
        }
        centerpoint.z += distance;
        return 0;
    }


    /* methods for rotating the sphere about itself */
    int x_rot_self(float degrees) {
        for (int i = 0; i < POINT_CT; ++i) {
            points[i] = space.x_rotation(
                points[i],
                centerpoint,
                degrees
            );
        }
        return 0;
    }
    int y_rot_self(float degrees) {
        for (int i = 0; i < POINT_CT; ++i) {
            points[i] = space.y_rotation(
                points[i],
                centerpoint,
                degrees
            );
        }
        return 0;
    }
    int z_rot_self(float degrees) {
        for (int i = 0; i < POINT_CT; ++i) {
            points[i] = space.z_rotation(
                points[i],
                centerpoint,
                degrees
            );
        }
        return 0;
    }
};
