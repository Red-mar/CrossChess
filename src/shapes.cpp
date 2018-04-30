#include "shapes.h"
#include <cmath>

#define PI 3.14159265359

Point::Point(float x, float y) : x(x),
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
	return ((p1.x - p0.x) * (p2.y - p0.y) - (p2.x - p0.x) * (p1.y - p0.y));
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