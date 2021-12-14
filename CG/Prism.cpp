#include "Prism.h"

Prism::Prism(Point3D _point1, Point3D _point2, Point3D _point3, Point3D _point4,
	Point3D _point5, Point3D _point6, Point3D _point7, Point3D _point8,
	Point3D _point9, Point3D _point10, Point3D _point11, Point3D _point12,
	COLORREF _color1, COLORREF _color2, COLORREF _color3, COLORREF _color4,
	COLORREF _color5, COLORREF _color6, COLORREF _color7, COLORREF _color8) {

	baseFigures.push_back(new Hexagon(_point1, _point2, _point3, _point4, _point5, _point6, _color1));
	baseFigures.push_back(new Hexagon(_point7, _point8, _point9, _point10, _point11, _point12, _color2));
	baseFigures.push_back(new Rect(_point1, _point2, _point7, _point8, _color3));
	baseFigures.push_back(new Rect(_point2, _point3, _point8, _point9, _color4));
	baseFigures.push_back(new Rect(_point3, _point4, _point9, _point10, _color5));
	baseFigures.push_back(new Rect(_point4, _point5, _point10, _point11, _color6));
	baseFigures.push_back(new Rect(_point5, _point6, _point11, _point12, _color7));
	baseFigures.push_back(new Rect(_point6, _point1, _point12, _point7, _color8));
}