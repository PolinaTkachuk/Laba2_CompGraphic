#ifndef AREA_H
#define AREA_H

#include <QWidget>
#include <shape.h>

//ЗАДАЧА 9(Карандаш)
//Фигура: «карандаш», грифель которого лежит на оси x, длина карандаша 6
//единиц измерения, а толщина – 12 единиц измерения.
//Проекция: параллельная.
//Движение: поворот вокруг оси x на 30 градусов.Вид из точки зрения (0, 10, 0)


class Area : public QWidget
{
    Q_OBJECT
private:
    Shape* shape;

    //координаты точки зрения
    float viewX = 0;
    float viewY = 10;
    float viewZ = 0;

    float alpha=0;//угол поворота
    int myTimer;// идентификатор таймера
    void setNewCoords(Shape* shape, float**);
    void translateShape(float** oldMatrix, Coords* value);
    void rotateShapeX(float** oldMatrix, float cosV, float sinV);
    void rotateShapeY(float** oldMatrix, float cosV, float sinV);
    void rotateShapeZ(float** oldMatrix, float cosV, float sinV);
    void scaleShape(float** oldMatrix, float valueX, float valueY, float valueZ);
    void matrixMultiplication(float**, int, int, float**, int, int);
public:
    Area(QWidget *parent = 0);
    ~Area() {
       // delete shape;
         killTimer(myTimer);
    };
public slots:
    void start_prog();
protected:
    //обработчики событий
    void paintEvent(QPaintEvent *event); //событие перерисовки
    void timerEvent(QTimerEvent *event); //событие таймера
    void showEvent(QShowEvent *event); // событие начала
    void hideEvent(QHideEvent *event); // событие конца
};

#endif // AREA_H
