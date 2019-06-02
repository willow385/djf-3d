#ifndef MATH_H
#define MATH_H
#include <math.h>
#endif

#ifndef _3D_TYPES_HPP
#define _3D_TYPES_HPP
#include "3d_types.hpp"
#endif

/* Definition of axes:

Z-axis: lower values mean closer to the viewer;
        higher values mean further away.
        (close/far)

X-axis: lower values mean further to the left;
        higher values mean further to the right.
        (left/right)

Y-axis: lower values mean higher on the screen;
        higher values mean closer to the bottom.
        (high/low)
*/


class Space {
    private:
        float depth; // "fudge factor" for effect of Z-vals
        float screen_x, screen_y; // center of the screen

    public:
        CoordPair get_screen_center() {
            CoordPair ret;
            ret.x = screen_x;
            ret.y = screen_y;
            return ret;
        }

        int set_depth_to(float value) {
            depth = value; // roughly 200 recommended here
            return (value == depth ? 0 : 1);
        }

        float get_depth_val() {
            return depth;
        }

        int set_screen_center(float x, float y) {
            screen_x = x;
            screen_y = y;
            return ((screen_x == x) && (screen_y == y) ? 0 : 1);
        }

        CoordTriple point_at(float _x, float _y, float _z) {
            CoordTriple point;
            point.x = _x;
            point.y = _y;
            point.z = _z;
            return point;
        }

        // This function is very important. It takes a 3d coordinate and projects
        // it into a 2d coordinate according to the laws of perspective.
        CoordPair convert_to_2d(CoordTriple q) {
            CoordPair ret;
            if (q.z > (-1 * depth)) {
                ret.x = (q.x + (screen_x * (q.z / depth))) / ((q.z / depth) + 1);
                ret.y = (q.y + (screen_y * (q.z / depth))) / ((q.z / depth) + 1);
            }
            return ret;
        }

        // This method rotates a 3d point about the z-axis (parallel to screen).
        // For all rotation methods, the "about" argument is the point about which
        // a point is to be rotated.
        CoordTriple z_rotation(CoordTriple point, CoordTriple about, float degrees) {
            CoordTriple ret;

            float theta = degrees * 0.0174533; // since sin() and cos() take radians
            float s = sin(theta);
            float c = cos(theta);

            // translate point back to origin:
            float tx = point.x - about.x;
            float ty = point.y - about.y;

            // rotate point
            float x_new = tx * c - ty * s;
            float y_new = tx * s + ty * c;

            // translate point back:
            ret.x = x_new + about.x;
            ret.y = y_new + about.y;
            ret.z = point.z;

            // and finally we have our new point
            return ret;
        }

        // This method rotates a point about the x-axis (up or down; perpendicular to screen).
        CoordTriple x_rotation(CoordTriple point, CoordTriple about, float degrees) {
            CoordTriple ret;
            float theta = degrees * 0.0174533;
            float s = sin(theta);
            float c = cos(theta);

            // translate point back to origin:
            float ty = point.y - about.y;
            float tz = point.z - about.z;

            // rotate point
            float y_new = ty * c - tz * s;
            float z_new = ty * s + tz * c;

            // translate point back:
            ret.y = y_new + about.y;
            ret.z = z_new + about.z;
            ret.x = point.x;

            // and finally we have our new point
            return ret;
        }

        // This method rotates a point about the y-axis (left or right; perpendicular to screen).
        CoordTriple y_rotation(CoordTriple point, CoordTriple about, float degrees) {
            CoordTriple ret;
            float theta = degrees * 0.0174533;

            float s = sin(theta);
            float c = cos(theta);

            // translate point back to origin:
            float tx = point.x - about.x;
            float tz = point.z - about.z;

            // rotate point
            float x_new = tx * c - tz * s;
            float z_new = tx * s + tz * c;

            // translate point back:
            ret.x = x_new + about.x;
            ret.z = z_new + about.z;
            ret.y = point.y;

            // and finally we have our new point
            return ret;
        }

        // Function to create a new 3d line between two 3d points
        Line3d line_between(CoordTriple a, CoordTriple b) {
            Line3d ret;
            ret.endpoint_0 = a;
            ret.endpoint_1 = b;
            return ret;
        }
};
