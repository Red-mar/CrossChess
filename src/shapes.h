#ifndef SHAPES_H
#define SHAPES_H

#include <vector>
#include "math.h"
#include <algorithm>
#define M_PI 3.14159265358979323846

class Point
{
  public:
	float x;
	float y;

	Point();
	Point(float x, float y);
};

struct Rectangle
{
	float x;
	float y;
	int w;
	int h;

	float top;
	float bottom;
	float leftmost;
	float rightmost;

	Point center;
	Point leftCenter;
	Point rightCenter;
	Point topLeft;
	Point topRight;
	Point topCenter;
	Point bottomLeft;
	Point bottomRight;
	Point bottomCenter;

	Rectangle(float x, float y, int w, int h);

	Rectangle(Point topLeft, Point bottomRight);

	Rectangle(Rectangle *other);

	Rectangle();

	void copy(Rectangle *other);

	void addX(float xAdd);
	void addY(float yAdd);
	void setX(float xSet);
	void setY(float ySet);
	void stretch(float scale);
	void stretch(float scaleX, float scaleY);
	void update();
	bool overlaps(Rectangle other);
	bool overlaps(Rectangle *other);
	void placeOnTop(Rectangle *other);
};

struct Circle
{
	float x;
	float y;
	int r; /// Radius

	float centerX;
	float centerY;

	/// Creates a nice circle with `x` and `y` coordinates and `r`
	/// radius.
	Circle(float x, float y, int r);

	/// Adds to the current x.
	///
	/// @note Although this seems useless, you must call this
	///       instead of directly modifying x because it
	///       refreshes internal points.
	///
	void addX(float xAdd);

	/// Adds to the current y.
	///
	/// @note Although this seems useless, you must call this
	///       instead of directly modifying y because it
	///       refreshes internal points.
	///
	void addY(float yAdd);
};

struct RotatedRectangle
{
	Point A, B, C, D;

	RotatedRectangle(Point A, Point B, Point C, Point D);

	RotatedRectangle(Rectangle rectangle);

	float isLeft(Point p0, Point p1, Point p2);

	bool PointInRectangle(Point P);
};

//https://www.redblobgames.com/grids/hexagons/

struct Hexagon
{
	Point points[6];
	Point center;
	int size;

	Hexagon(Point center, int size);
	Hexagon(Point A, Point B, Point C, Point D, Point E, Point F);
};

struct Orientation
{
	const double f0, f1, f2, f3;
	const double b0, b1, b2, b3;
	const double start_angle; // in multiples of 60°
	Orientation(double f0_, double f1_, double f2_, double f3_,
				double b0_, double b1_, double b2_, double b3_,
				double start_angle_)
		: f0(f0_), f1(f1_), f2(f2_), f3(f3_),
		  b0(b0_), b1(b1_), b2(b2_), b3(b3_),
		  start_angle(start_angle_) {}
};

const Orientation layout_pointy = Orientation(sqrt(3.0), sqrt(3.0) / 2.0, 0.0, 3.0 / 2.0,
											  sqrt(3.0) / 3.0, -1.0 / 3.0, 0.0, 2.0 / 3.0,
											  0.5);
const Orientation layout_flat = Orientation(3.0 / 2.0, 0.0, sqrt(3.0) / 2.0, sqrt(3.0),
											2.0 / 3.0, 0.0, -1.0 / 3.0, sqrt(3.0) / 3.0,
											0.0);

struct Layout
{
	const Orientation orientation;
	const Point size;
	const Point origin;
	Layout(Orientation orientation_, Point size_, Point origin_)
		: orientation(orientation_), size(size_), origin(origin_) {}
};

struct Hex
{ // Cube storage, cube constructor
	const int q, r, s;
	Hex(int q_, int r_, int s_) : q(q_), r(r_), s(s_)
	{
		//assert (q + r + s == 0);
	}
};

static bool operator==(Hex a, Hex b)
{
	return a.q == b.q && a.r == b.r && a.s == b.s;
}



static bool operator!=(Hex a, Hex b)
{
	return !(a == b);
}

static Hex hex_add(Hex a, Hex b)
{
	return Hex(a.q + b.q, a.r + b.r, a.s + b.s);
}

static Hex hex_subtract(Hex a, Hex b)
{
	return Hex(a.q - b.q, a.r - b.r, a.s - b.s);
}

static Hex hex_multiply(Hex a, int k)
{
	return Hex(a.q * k, a.r * k, a.s * k);
}

static int hex_length(Hex hex)
{
	return int((abs(hex.q) + abs(hex.r) + abs(hex.s)) / 2);
}

static int hex_distance(Hex a, Hex b)
{
	return hex_length(hex_subtract(a, b));
}

static const std::vector<Hex> hex_directions = {
	Hex(1, 0, -1), Hex(1, -1, 0), Hex(0, -1, 1),
	Hex(-1, 0, 1), Hex(-1, 1, 0), Hex(0, 1, -1)};

static Hex hex_direction(int direction /* 0 to 5 */)
{
	//assert (0 <= direction && direction < 6);
	return hex_directions[direction];
}

static Hex hex_neighbor(Hex hex, int direction)
{
	return hex_add(hex, hex_direction(direction));
}

static Point hex_to_pixel(Layout layout, Hex h)
{
	const Orientation &M = layout.orientation;
	double x = (M.f0 * h.q + M.f1 * h.r) * layout.size.x;
	double y = (M.f2 * h.q + M.f3 * h.r) * layout.size.y;
	return Point(x + layout.origin.x, y + layout.origin.y);
}

struct FractionalHex
{
	const double q, r, s;
	FractionalHex(double q_, double r_, double s_)
		: q(q_), r(r_), s(s_) {}
};

static FractionalHex pixel_to_hex(Layout layout, Point p)
{
	{
		const Orientation &M = layout.orientation;
		Point pt = Point((p.x - layout.origin.x) / layout.size.x,
						 (p.y - layout.origin.y) / layout.size.y);
		double q = M.b0 * pt.x + M.b1 * pt.y;
		double r = M.b2 * pt.x + M.b3 * pt.y;
		return FractionalHex(q, r, -q - r);
	}
}

static Point hex_corner_offset(Layout layout, int corner) {
    Point size = layout.size;
    double angle = 2.0 * M_PI *
             (layout.orientation.start_angle + corner) / 6;
    return Point(size.x * cos(angle), size.y * sin(angle));
}

static std::vector<Point> polygon_corners(Layout layout, Hex h) {
    std::vector<Point> corners = {};
    Point center = hex_to_pixel(layout, h);
    for (int i = 0; i < 6; i++) {
        Point offset = hex_corner_offset(layout, i);
        corners.push_back(Point(center.x + offset.x,
                                center.y + offset.y));
    }
    return corners;
}

static Hex hex_round(FractionalHex h) {
    int q = int(round(h.q));
    int r = int(round(h.r));
    int s = int(round(h.s));
    double q_diff = abs(q - h.q);
    double r_diff = abs(r - h.r);
    double s_diff = abs(s - h.s);
    if (q_diff > r_diff && q_diff > s_diff) {
        q = -r - s;
    } else if (r_diff > s_diff) {
        r = -q - s;
    } else {
        s = -q - r;
    }
    return Hex(q, r, s);
}

static float lerp(double a, double b, double t) {
    return a * (1-t) + b * t;
    /* better for floating point precision than
       a + (b - a) * t, which is what I usually write */
}

static FractionalHex hex_lerp(Hex a, Hex b, double t) {
    return FractionalHex(lerp(a.q, b.q, t),
                         lerp(a.r, b.r, t),
                         lerp(a.s, b.s, t));
}

static std::vector<Hex> hex_linedraw(Hex a, Hex b) {
    int N = hex_distance(a, b);
    std::vector<Hex> results = {};
    double step = 1.0 / std::max(N, 1);
    for (int i = 0; i <= N; i++) {
        results.push_back(hex_round(hex_lerp(a, b, step * i)));
    }
    return results;
}

namespace std {
    template <> struct hash<Hex> {
        size_t operator()(const Hex& h) const {
            hash<int> int_hash;
            size_t hq = int_hash(h.q);
            size_t hr = int_hash(h.r);
            return hq ^ (hr + 0x9e3779b9 + (hq << 6) + (hq >> 2));
        }
    };
}


#endif // !SHAPES_H
