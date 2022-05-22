#include "shape.h"

Coords::Coords(float _x, float _y, float _z)
{
    x = _x;
    y = _y;
    z = _z;
}

Connection::Connection(int _begin, int _end) {
    begin = _begin;
    end = _end;
}

Shape::Shape(int _n, Coords** _coords, int _conN, Connection** _connections)
{
    n = _n;
    ver = _coords;
    conN = _conN;
    reb = _connections;
}

void Shape::SetCoords(int i, float newX, float newY, float newZ) {
    ver[i]->x = newX;
    ver[i]->y = newY;
    ver[i]->z = newZ;
}

Shape::~Shape() {
    for (int i = 0; i < n; i++) {
            delete ver[i];
            delete reb[i];
        }
        delete []ver;
        delete []reb;
}
