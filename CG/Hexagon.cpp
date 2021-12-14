#include "Hexagon.h"

Hexagon::Hexagon(Point3D _point1, Point3D _point2, Point3D _point3, Point3D _point4, Point3D _point5, Point3D _point6, COLORREF _color) {
	triangles.push_back(Triangle(_point1, _point2, _point6, _color));
	triangles.push_back(Triangle(_point2, _point3, _point6, _color));
	triangles.push_back(Triangle(_point3, _point4, _point6, _color));
	triangles.push_back(Triangle(_point4, _point5, _point6, _color));
}