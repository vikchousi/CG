#include "Triangle.h"

Triangle::Triangle(Point3D _point1, Point3D _point2, Point3D _point3, COLORREF _color) : color(_color) {
	points.push_back(_point1);
	points.push_back(_point2);
	points.push_back(_point3);
}

void Triangle::print(double shift) {
    setcolor(color);
    line(pointsProjection[0].getX() + shift, pointsProjection[0].getY() + shift, pointsProjection[1].getX() + shift, pointsProjection[1].getY() + shift);
    line(pointsProjection[1].getX() + shift, pointsProjection[1].getY() + shift, pointsProjection[2].getX() + shift, pointsProjection[2].getY() + shift);
    line(pointsProjection[2].getX() + shift, pointsProjection[2].getY() + shift, pointsProjection[0].getX() + shift, pointsProjection[0].getY() + shift);
}

void Triangle::transfer(double dx, double dy, double dz) {
    changeCoordinates(points, matrixTransfer(dx, dy, dz));
}

void Triangle::scale(Point3D _center, double sx, double sy, double sz) {
    transfer(-_center.getX(), -_center.getY(), -_center.getZ());
    changeCoordinates(points, matrixScale(sx, sy, sz));
    transfer(_center.getX(), _center.getY(), _center.getZ());
}

void Triangle::rotation(Point3D _center, double angle, Axises axis) {
    transfer(-_center.getX(), -_center.getY(), -_center.getZ());
    changeCoordinates(points, matrixRotation(angle, axis));
    transfer(_center.getX(), _center.getY(), _center.getZ());
}

void Triangle::centerTask() {  
    updateBorders(points);
    center.setX((minBorder.getX() + maxBorder.getX()) / 2.0);
    center.setY((minBorder.getY() + maxBorder.getY()) / 2.0);
    center.setZ((minBorder.getZ() + maxBorder.getZ()) / 2.0);
}

void Triangle::projection(Point3D _center) {
    
    std::vector<Point3D> tmp = pointsProjection;
    bool isNanBorder = false;
    pointsProjection = points;
    transfer(pointsProjection, -_center.getX(), -_center.getY(), 0);
    changeCoordinates(pointsProjection, matrProjection());
    transfer(pointsProjection, _center.getX(), _center.getY(), 0);
    
}

Triangle Triangle::getShadowTriangle(Point3D l) {
    std::vector<Point3D> pointsShadow = points;
    changeCoordinates(pointsShadow, matrShadow(l, maxY));
    return Triangle(pointsShadow[0], pointsShadow[1], pointsShadow[2], WHITE);
}

double Triangle::getMidZ() {
    double midZ = 0;
    for (int i = 0; i < pointsProjection.size(); i++) {
        midZ += pointsProjection[i].getZ();
    }

    return (pointsProjection.size() == 0 ? INT32_MAX : midZ / double(pointsProjection.size()));
}

void Triangle::changeCoordinates(std::vector<Point3D>& _points, double** matr) {
    isNanBorder = false;
    for (int i = 0; i < _points.size(); i++)
    {
        double* curCor = new double[4];
        curCor[0] = _points[i].getX();
        curCor[1] = _points[i].getY();
        curCor[2] = _points[i].getZ();
        curCor[3] = 1;
        mulMat(curCor, matr, 4);
        _points[i].setX(curCor[0] / curCor[3]);
        _points[i].setY(curCor[1] / curCor[3]);
        _points[i].setZ(curCor[2] / curCor[3]);
        delete[] curCor;
        if (_points[i].getX() < 0 || _points[i].getX() > maxX ||
            _points[i].getY() < 0 || _points[i].getY() > maxY) 
            isNanBorder = true;
    }
    delmatr(matr, 4);
}

void Triangle::transfer(std::vector<Point3D>& _points, double dx, double dy, double dz) {
    changeCoordinates(_points, matrixTransfer(dx, dy, dz));
}

void Triangle::updateBorders(std::vector<Point3D>& _points) {

    minBorder = Point3D(INT32_MAX, INT32_MAX, INT32_MAX);
    maxBorder = Point3D(INT32_MIN, INT32_MIN, INT32_MIN);
    for (int i = 0; i < _points.size(); i++)
    {
        if (_points[i].getX() < minBorder.getX())
            minBorder.setX(_points[i].getX());
        if (_points[i].getX() > maxBorder.getX())
            maxBorder.setX(_points[i].getX());

        if (_points[i].getY() < minBorder.getY())
            minBorder.setY(_points[i].getY());
        if (_points[i].getY() > maxBorder.getY())
            maxBorder.setY(_points[i].getY());

        if (_points[i].getZ() < minBorder.getZ())
            minBorder.setZ(_points[i].getZ());
        if (_points[i].getZ() > maxBorder.getZ())
            maxBorder.setZ(_points[i].getZ());
    }
}

void Triangle::painting()
{
    updateBorders(pointsProjection);
    for (int i = 1; i < pointsProjection.size(); i++)
        for (int j = 0; j < pointsProjection.size() - i; j++)
            if (pointsProjection[j].getX() > pointsProjection[j + 1].getX()) {
                Point3D tmp = pointsProjection[j];
                pointsProjection[j] = pointsProjection[j + 1];
                pointsProjection[j + 1] = tmp;
            }
    double k1, b1, k2, b2, k3, b3;
    setLineCoefficients(pointsProjection[0], pointsProjection[2], k1, b1);
    setLineCoefficients(pointsProjection[0], pointsProjection[1], k2, b2);
    setLineCoefficients(pointsProjection[1], pointsProjection[2], k3, b3);
    printLine(pointsProjection[0].getX(), pointsProjection[1].getX(), k1, b1, k2, b2, pointsProjection[0].getY(), pointsProjection[1].getY());
    printLine(pointsProjection[1].getX(), pointsProjection[2].getX(), k1, b1, k3, b3, pointsProjection[0].getY(), pointsProjection[2].getY());
}

void Triangle::setLineCoefficients(Point3D _point1, Point3D _point2, double& k, double& b) {
    if (_point2.getX() - _point1.getX() == 0) {
        k = INT32_MAX;
        return;
    }  
    k = (_point2.getY() - _point1.getY()) / (_point2.getX() - _point1.getX());
    b = _point1.getY() - k * _point1.getX();
}

void Triangle::printLine(double _strart, double _end, double k1, double b1, double k2, double b2, double y1, double y2) {
    int start = ceil(_strart), end = ceil(_end);
    for (int i = start; i <= end; i++) {
        if ((k1 == INT32_MAX && (start == end || (i != end))) &&
            ((k2 * i + b2) >= minBorder.getY() && (k2 * i + b2) <= maxBorder.getY()))
            line(i, y1, i, (k2 * i + b2));
        else if ((k2 == INT32_MAX && (start == end || (i != end))) &&
            ((k1 * i + b1) >= minBorder.getY() && (k1 * i + b1) <= maxBorder.getY()))
            line(i, k1 * i + b1, i, y2);
        else if ((start == end || (i != end)) &&
            (((k1 * i + b1) >= minBorder.getY() && (k1 * i + b1) <= maxBorder.getY()) && 
                ((k2 * i + b2) >= minBorder.getY() && (k2 * i + b2) <= maxBorder.getY())))
            line(i, k1 * i + b1, i, k2 * i + b2);
    }
}