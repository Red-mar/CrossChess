#ifndef SHAPES_H
#define SHAPES_H

#include <vector>
#include <algorithm>
#include <math.h>

class Point
{
  public:
	double x;
	double y;

	Point();
	Point(double x, double y);
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

//TODO clean this up :(

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
	int q, r, s;
	Hex(int q_, int r_, int s_) : q(q_), r(r_), s(s_)
	{
		//assert (q + r + s == 0);
	}
};

bool operator==(Hex a, Hex b);
bool operator!=(Hex a, Hex b);
Hex hex_add(Hex a, Hex b);
Hex hex_subtract(Hex a, Hex b);
Hex hex_multiply(Hex a, int k);
Hex hex_divide(Hex a, int k);
int hex_length(Hex hex);
int hex_distance(Hex a, Hex b);

const std::vector<Hex> hex_directions = std::vector<Hex>({
	Hex(1, 0, -1), Hex(1, -1, 0), Hex(0, -1, 1),
	Hex(-1, 0, 1), Hex(-1, 1, 0), Hex(0, 1, -1)});

Hex hex_direction(int direction /* 0 to 5 */);
Hex hex_neighbor(Hex hex, int direction);
Point hex_to_pixel(Layout layout, Hex h);

struct FractionalHex
{
	const double q, r, s;
	FractionalHex(double q_, double r_, double s_)
		: q(q_), r(r_), s(s_) {}
};

FractionalHex pixel_to_hex(Layout layout, Point p);
Point hex_corner_offset(Layout layout, int corner);
std::vector<Point> polygon_corners(Layout layout, Hex h);
Hex hex_round(FractionalHex h);
float lerp(double a, double b, double t);
FractionalHex hex_lerp(Hex a, Hex b, double t);
std::vector<Hex> hex_linedraw(Hex a, Hex b);
std::vector<Hex> hex_diagonal_linedraw(Hex a, Hex b);

static const std::vector<Hex> hex_diagonals = {
	Hex(2, -1, -1), Hex(1, 1, -2), Hex(-1, 2, -1),
	Hex(-2, 1, 1), Hex(-1, -1, 2), Hex(1, -2, 1)};


Hex hex_diagonal(int direction /* 0 to 5 */);
Hex hex_diagonal_neighbor(Hex hex, int direction);

/*
namespace std
{
template <>
struct hash<Hex>
{
	size_t operator()(const Hex &h) const
	{
		hash<int> int_hash;
		size_t hq = int_hash(h.q);
		size_t hr = int_hash(h.r);
		return hq ^ (hr + 0x9e3779b9 + (hq << 6) + (hq >> 2));
	}
};
}
*/
#endif // !SHAPES_H
