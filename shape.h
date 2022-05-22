#ifndef SHAPE_H
#define SHAPE_H

class Shape;

class Coords //класс координаты техмерного пространства
{
private:
    float x;
    float y;
    float z;
public:
    Coords(float _x, float _y, float _z);//конструктор по умолчанию
    ~Coords() {}; //дестрктор
    //получение координат
    float getX() {return x;}
    float getY() {return y;}
    float getZ() {return z;}
    void setX(float _x) {x = _x;}
    void setY(float _y) {y = _y;}
    void setZ(float _z) {z = _z;}
    friend class Shape;
};

class Connection //начало и конец работы
{
private:
    int begin;
    int end;
public:
    Connection(int _begin, int _end);
    ~Connection() {};
    int getBegin() {return begin;}
    int getEnd() {return end;}
    friend class Shape;
};

class Shape//Фигура
{
private:
    Coords **ver;//массив вершин
    Connection **reb;//массив ребер
    int n; //кол-во вершин
    int conN; //кол-во ребер
public:
    //конструктор задает фигуру с _n-вершинами+массив их координат и _conN-ребрами+массив ребер
    Shape(int _n, Coords** _coords, int _conN, Connection** _connections);
    //деструктор
    ~Shape();
    friend class Area;
    Coords* getCoords(int i) {return ver[i];}//возвращ i-ую вершину
    Connection* getConnection(int i) {return reb[i];}//возвращ i-ое ребро
    void SetCoords(int i, float, float, float);
    int getN() {return n;}
    int getConN() {return conN;}
};

#endif // SHAPE_H
