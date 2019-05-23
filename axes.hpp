#ifndef SPACE_HPP
#define SPACE_HPP
#include "space.hpp"
#endif

class Axes {
    public:
        Line3d x_axis, y_axis, z_axis;
        Space space;

        // default vals for the axes
        void init(float bound, float origin_x, float origin_y) {
            x_axis = space.line_between(space.point_at((-1 * bound) + origin_x, origin_y, 0), space.point_at(bound + origin_x, origin_y, 0));
            y_axis = space.line_between(space.point_at(origin_x, (-1 * bound + origin_y), 0), space.point_at(origin_x, bound + origin_y, 0));
            z_axis = space.line_between(space.point_at(origin_x, origin_y, -1 * bound), space.point_at(origin_x, origin_y, bound));
        }
};
