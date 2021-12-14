#pragma once
#include "Figure.h"
#include "Rect.h"
#include "Hexagon.h"

class Prism : public Figure
{
public:
	Prism(Point3D _point1, Point3D _point2, Point3D _point3, Point3D _point4,
		Point3D _point5, Point3D _point6, Point3D _point7, Point3D _point8,
		Point3D _point9, Point3D _point10, Point3D _point11, Point3D _point12,
		COLORREF _color1, COLORREF _color2, COLORREF _color3, COLORREF _color4,
		COLORREF _color5, COLORREF _color6, COLORREF _color7, COLORREF _color8);
};

