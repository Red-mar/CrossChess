#include "shapes.h"
#define M_PI 3.14159265358979323846
#define PI 3.14159265358979323846

Point::Point(double x, double y) : x(x),
								 y(y)
{
}

Point::Point() : x(0),
				 y(0)
{
}

Rectangle::Rectangle(float x, float y, int w, int h) : x(x),
													   y(y),
													   w(w),
													   h(h)
{
	this->update();
}
Rectangle::Rectangle() : x(0),
						 y(0),
						 w(1),
						 h(1)
{
	this->update();
}
Rectangle::Rectangle(Rectangle *other)
{
	this->copy(other);
}
void Rectangle::copy(Rectangle *other)
{
	this->x = other->x;
	this->y = other->y;
	this->w = other->w;
	this->h = other->h;

	this->update();
}
void Rectangle::addX(float xAdd)
{
	this->x += xAdd;

	this->update();
}
void Rectangle::addY(float yAdd)
{
	this->y += yAdd;

	this->update();
}
void Rectangle::setX(float xSet)
{
	this->x = xSet;

	this->update();
}
void Rectangle::setY(float ySet)
{
	this->y = ySet;

	this->update();
}
void Rectangle::stretch(float scale)
{
	this->stretch(scale, scale);
}
void Rectangle::stretch(float scaleX, float scaleY)
{
	if ((scaleX <= 0) || (scaleY <= 0))
		return;

	float oldW = (float)w;
	float oldH = (float)h;

	this->w *= (int)scaleX;
	this->h *= (int)scaleY;

	// Centralizing one rectangle on the other
	this->x += fabs(oldW - this->w) / 2;
	this->y += fabs(oldH - this->h) / 2;

	this->update();
}
void Rectangle::update()
{
	this->top = y;
	this->bottom = y + h;

	this->leftmost = x;
	this->rightmost = x + w;

	this->center = Point(x + (w / 2),
						 y + (h / 2));

	this->topLeft = Point(x, y);
	this->topRight = Point(x + w, y);
	this->bottomLeft = Point(x, y + h);
	this->bottomRight = Point(x + w, y + h);

	this->topCenter = Point(center.x, top);
	this->bottomCenter = Point(center.x, bottom);
	this->leftCenter = Point(leftmost, center.y);
	this->rightCenter = Point(rightmost, center.y);
}
bool Rectangle::overlaps(Rectangle other)
{
	return this->overlaps(&other);
}
bool Rectangle::overlaps(Rectangle *other)
{
	if ((x <= other->rightmost) &&
		(other->x <= rightmost) &&
		(y <= other->bottom) &&
		(other->y <= bottom))
		return true;

	return false;
}
void Rectangle::placeOnTop(Rectangle *other)
{
	this->y = (other->y - this->h);

	this->update();
}

Circle::Circle(float x, float y, int r) : x(x),
										  y(y),
										  r(r)
{
	this->centerX = x + r;
	this->centerY = y + r;
}

void Circle::addX(float xAdd)
{
	this->x += xAdd;
	this->centerX += xAdd;
}

void Circle::addY(float yAdd)
{
	this->y += yAdd;
	this->centerY += yAdd;
}

RotatedRectangle::RotatedRectangle(Point A, Point B, Point C, Point D) : A(A), B(B), C(C), D(D)
{
}

RotatedRectangle::RotatedRectangle(Rectangle rectangle) // 45 degrees?
{
	A = Point(rectangle.x + (rectangle.w / 2),
			  rectangle.y);
	B = Point(rectangle.topRight.x,
			  rectangle.topRight.y + (rectangle.h / 2));
	C = Point(rectangle.bottomLeft.x + (rectangle.w / 2),
			  rectangle.bottomLeft.y);
	D = Point(rectangle.topLeft.x,
			  rectangle.topLeft.y + (rectangle.h / 2));
}

float RotatedRectangle::isLeft(Point p0, Point p1, Point p2)
{
	return (float)((p1.x - p0.x) * (p2.y - p0.y) - (p2.x - p0.x) * (p1.y - p0.y));
}

bool RotatedRectangle::PointInRectangle(Point P)
{
	return (isLeft(A, B, P) > 0 && isLeft(B, C, P) > 0 && isLeft(C, D, P) > 0 && isLeft(D, A, P) > 0);
}

Hexagon::Hexagon(Point center, int size) : center(center), size(size)
{

	for (size_t i = 0; i < sizeof(points) / sizeof(points[0]); i++)
	{
		float angleDeg = 60 * (float)(i+1);
		float angleRad = (float)(PI / 180 * angleDeg);
		points[i] = Point(center.x + size * cos(angleRad),
						  center.y + size * sin(angleRad));
	}
}

Hexagon::Hexagon(Point A, Point B, Point C, Point D, Point E, Point F)
{
	points[0] = A;
	points[1] = B;
	points[2] = C;
	points[3] = D;
	points[4] = E;
	points[5] = F;
}

bool operator==(Hex a, Hex b)
{
	return a.q == b.q && a.r == b.r && a.s == b.s;
}

bool operator!=(Hex a, Hex b)
{
	return !(a == b);
}

Hex hex_add(Hex a, Hex b)
{
	return Hex(a.q + b.q, a.r + b.r, a.s + b.s);
}

Hex hex_subtract(Hex a, Hex b)
{
	return Hex(a.q - b.q, a.r - b.r, a.s - b.s);
}

Hex hex_multiply(Hex a, int k)
{
	return Hex(a.q * k, a.r * k, a.s * k);
}

Hex hex_divide(Hex a, int k)
{
	return Hex(a.q / k, a.r / k, a.s / k);
}

int hex_length(Hex hex)
{
	return int((abs(hex.q) + abs(hex.r) + abs(hex.s)) / 2);
}

int hex_distance(Hex a, Hex b)
{
	return hex_length(hex_subtract(a, b));
}

Hex hex_direction(int direction /* 0 to 5 */)
{
	//assert (0 <= direction && direction < 6);
	return hex_directions[direction];
}

Hex hex_neighbor(Hex hex, int direction)
{
	return hex_add(hex, hex_direction(direction));
}

Point hex_to_pixel(Layout layout, Hex h)
{
	const Orientation &M = layout.orientation;
	double x = (M.f0 * h.q + M.f1 * h.r) * layout.size.x;
	double y = (M.f2 * h.q + M.f3 * h.r) * layout.size.y;
	return Point(x + layout.origin.x, y + layout.origin.y);
}

FractionalHex pixel_to_hex(Layout layout, Point p)
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

Point hex_corner_offset(Layout layout, int corner)
{
	Point size = layout.size;
	double angle = 2.0 * M_PI *
				   (layout.orientation.start_angle + corner) / 6;
	return Point(size.x * cos(angle), size.y * sin(angle));
}

std::vector<Point> polygon_corners(Layout layout, Hex h)
{
	std::vector<Point> corners = {};
	Point center = hex_to_pixel(layout, h);
	for (int i = 0; i < 6; i++)
	{
		Point offset = hex_corner_offset(layout, i);
		corners.push_back(Point(center.x + offset.x,
								center.y + offset.y));
	}
	return corners;
}

Hex hex_round(FractionalHex h)
{
	int q = int(round(h.q));
	int r = int(round(h.r));
	int s = int(round(h.s));
	double q_diff = abs(q - h.q);
	double r_diff = abs(r - h.r);
	double s_diff = abs(s - h.s);
	if (q_diff > r_diff && q_diff > s_diff)
	{
		q = -r - s;
	}
	else if (r_diff > s_diff)
	{
		r = -q - s;
	}
	else
	{
		s = -q - r;
	}
	return Hex(q, r, s);
}

float lerp(double a, double b, double t)
{
	return (float)(a * (1 - t) + b * t);
	/* better for floating point precision than
       a + (b - a) * t, which is what I usually write */
}

FractionalHex hex_lerp(Hex a, Hex b, double t)
{
	return FractionalHex(lerp(a.q, b.q, t),
						 lerp(a.r, b.r, t),
						 lerp(a.s, b.s, t));
}

std::vector<Hex> hex_linedraw(Hex a, Hex b)
{
	int N = hex_distance(a, b);
	std::vector<Hex> results = {};
	double step = 1.0 / std::max(N, 1);
	for (int i = 0; i <= N; i++)
	{
		FractionalHex lerp = hex_lerp(a, b, step * i);
		results.push_back(hex_round(lerp));
	}
	return results;
}

std::vector<Hex> hex_diagonal_linedraw(Hex a, Hex b)
{
	int N = hex_distance(a, b);
	std::vector<Hex> results = {};
	double step = 1.0 / std::max(N, 1);
	for (int i = 0; i <= N; i++)
	{
		FractionalHex lerp = hex_lerp(a, b, step * i);
		if ((floor(lerp.q) == lerp.q && floor(lerp.r) == lerp.r && floor(lerp.s) == lerp.s) || //TODO: fix floating point comparison errors
			lerp.q == 2.2204460492503131e-016 || lerp.r == 1.1102230246251565e-16 || lerp.s == 1.1102230246251565e-16||
			lerp.q == -2.2204460492503131e-016 || lerp.r == -1.1102230246251565e-16 || lerp.s == -1.1102230246251565e-16)
		{
			results.push_back(hex_round(lerp));
		}
	}
	return results;
}

Hex hex_diagonal(int direction /* 0 to 5 */)
{
	//assert (0 <= direction && direction < 6);
	return hex_diagonals[direction];
}

Hex hex_diagonal_neighbor(Hex hex, int direction)
{
	return hex_add(hex, hex_diagonal(direction));
}