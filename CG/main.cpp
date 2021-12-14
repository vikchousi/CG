#include "graphics.h"
#include "Prism.h"
#include "Parallelepiped.h"
#include <stdlib.h>
#include <iostream>
#include <algorithm>

using namespace std;

void hud(vector<Figure*>& figures) {
    vector<BaseFigure*> triangles;
    for (int i = 0; i < figures.size(); i++) {
        figures[i]->projection();
        vector<BaseFigure*> tmp = figures[i]->getTriandles();
        for (auto triangle : tmp)
            triangles.push_back(triangle);
    }
    for (int i = 1; i < triangles.size(); i++) {
        for (int j = 0; j < triangles.size() - i; j++)
            if (triangles[j]->getMidZ() < triangles[j + 1]->getMidZ())
                swap(triangles[j], triangles[j + 1]);
    }

    for (int i = 0; i < triangles.size(); i++) {
        triangles[i]->print();
        triangles[i]->painting();
    }
}

void shadow(vector<Figure*>& figures, Point3D l) {
    for (int i = 0; i < figures.size(); i++)
        figures[i]->parintShadow(l);
}

void setMax(vector<Figure*>& figures, int maxX, int maxY) {
    for (int i = 0; i < figures.size(); i++)
        figures[i]->setMax(maxX, maxY);
}

void drowTask(vector<Figure*>& figures, Point3D& l) {
    cleardevice();
    hud(figures);
    shadow(figures, l);
}

void transfer(vector<Figure*>& figures, int number, double dx, double dy, double dz) {
    for (int i = 0; i < figures.size(); i++)
        if (number == 0 || i == number - 1)
            figures[i]->transfer(dx, dy, dz);
}

void scale(vector<Figure*>& figures, int number, double sx, double sy, double sz) {
    for (int i = 0; i < figures.size(); i++)
        if (number == 0 || i == number - 1)
            figures[i]->scale(sx, sy, sz);
}

void rotation(vector<Figure*>& figures, int number, double angle, Axises axis) {
    for (int i = 0; i < figures.size(); i++)
        if (number == 0 || i == number - 1)
            figures[i]->rotation(angle, axis);
}

vector<Figure*> createTask() {
    Parallelepiped* parallelepiped = new Parallelepiped(
        Point3D(150, 200, 200), Point3D(250, 200, 200), Point3D(250, 300, 200), Point3D(150, 300, 200),
        Point3D(150, 200, 350), Point3D(250, 200, 350), Point3D(250, 300, 350), Point3D(150, 300, 350),
        MAGENTA, MAGENTA, BROWN, LIGHTRED, LIGHTMAGENTA, YELLOW);
    Prism* prism = new Prism(
        Point3D(375, 250, 200), Point3D(400, 200, 200), Point3D(450, 200, 200), Point3D(475, 250, 200), Point3D(450, 300, 200), Point3D(400, 300, 200),
        Point3D(375, 250, 350), Point3D(400, 200, 350), Point3D(450, 200, 350), Point3D(475, 250, 350), Point3D(450, 300, 350), Point3D(400, 300, 350),
        GREEN, GREEN, CYAN, LIGHTBLUE, LIGHTGREEN, LIGHTCYAN, LIGHTBLUE, LIGHTGREEN);
    vector<Figure*> figures;
    figures.push_back(parallelepiped);
    figures.push_back(prism);
    return figures;
}

int main() {
    int gm, gd = DETECT;
    char a[2] = " ";
    initgraph(&gd, &gm, a);
    const int maxX = getmaxx() - 10, maxY = getmaxy() - 10;
    vector<Figure*> figures = createTask();
    setMax(figures, maxX, maxY);
    double range = 10, rel = 1.10, angle = 10;
    Point3D light(290, 0, 0);
    drowTask(figures, light);
    bool isExit = false;
    int number = 0;
    cout << "Instructions" << endl;
    cout << "----------------" << endl;
    cout << "Click on the key" << endl << endl;
    cout << "2  -  to select two objects" << endl;
    cout << "1  -  to select left objects" << endl;
    cout << "3  -  to select right objects" << endl << endl;
    cout << "w  -  to transfer up" << endl;
    cout << "s  -  to transfer down" << endl;
    cout << "a  -  to transfer left" << endl;
    cout << "d  -  to transfer right" << endl << endl;
    cout << "+  -  to change size to larger" << endl;
    cout << "-  -  to change size to smaller" << endl << endl;
    cout << "9  -  to spin left in the x-plane" << endl;
    cout << "0  -  to spin right in the x-plane" << endl << endl;
    cout << "<- -  to spin left" << endl;
    cout << "-> -  to spin right" << endl;
    cout << "^ -  to spin up" << endl;
    cout << "v  -  to spin down" << endl << endl;
    cout << "escape - to exit the program" << endl;
    while (!isExit)
    {
        switch (getch())
        {
        case 50:
            number = 0;
            break;
        case 49:
            number = 1;
            break;
        case 51:
            number = 2;
            break;
        case 119: 
            transfer(figures, number, 0, -range, 0);
            drowTask(figures, light);
            break;
        case 115: 
            transfer(figures, number, 0, range, 0);
            drowTask(figures, light);
            break;
        case 97: 
            transfer(figures, number, -range, 0, 0);
            drowTask(figures, light);
            break;
        case 100: 
            transfer(figures, number, range, 0, 0);
            drowTask(figures, light);
            break;
        case 45:
            scale(figures, number, 1.0 / rel, 1.0 / rel, 1.0 / rel);
            drowTask(figures, light);
            break;
        case 61:
            scale(figures, number, rel, rel, rel);
            drowTask(figures, light);
            break;
        case 57:     
            rotation(figures, number, -angle, Axises::Z);
            drowTask(figures, light);
            break;
        case 48: 
            rotation(figures, number, angle, Axises::Z);
            drowTask(figures, light);
            break;
        case 72:    
            rotation(figures, number, -angle, Axises::X);
            drowTask(figures, light);
            break;
        case 80:
            rotation(figures, number, angle, Axises::X);
            drowTask(figures, light);
            break;
        case 75: 
            rotation(figures, number, angle, Axises::Y);
            drowTask(figures, light);
            break;
        case 77:
            rotation(figures, number, -angle, Axises::Y);
            drowTask(figures, light);
            break;
        case 27:
            isExit = true;
            break;
        }
    }
}