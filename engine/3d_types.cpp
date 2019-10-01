/* I'm going to define a couple of data types which will prove very
useful to have for 3d rendering. */

typedef struct {
    float x;
    float y;
} CoordPair;

typedef struct {
    float x;
    float y;
    float z;
} CoordTriple;

typedef struct {
    CoordTriple endpoint_0;
    CoordTriple endpoint_1;
} Line3d; // subject to the laws of perspective

typedef struct {
    CoordPair endpoint_0;
    CoordPair endpoint_1;
} Line2d; // not subject to the laws of perspective
