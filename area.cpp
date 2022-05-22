#include "area.h"
#include <QPainter>
#include <QTimerEvent>
#include <iostream>
#include <math.h>

using namespace std;

Area::Area(QWidget *parent):QWidget(parent)
{
    //ограничиваем размер формы
    setFixedSize(QSize(500, 500));
}

void Area::showEvent(QShowEvent *) {
    update();
}

void Area::paintEvent(QPaintEvent *)//событие перерисовки
{
    QPainter painter(this);
    //зададим сцену из 5 рёбер (3 оси координат и 2 отрезка)

    //задание координат вершин сцены
    Coords** shapeCoords = new Coords*[13];
    //оси координатные
    //shapeCoords[0] = new Coords(0, 0, 0);
    //shapeCoords[1] = new Coords(10, 0, 0);
    //shapeCoords[2] = new Coords(0, 10, 0);
    //shapeCoords[3] = new Coords(0, 0, 10);

       shapeCoords[0] = new Coords(5, 0, 0);
       shapeCoords[1] = new Coords(2, 4, 0);
       shapeCoords[2] = new Coords(2, -4, 0);
       shapeCoords[3] = new Coords(2, 2, 2);
       shapeCoords[4] = new Coords(2, 2, -2);
       shapeCoords[5] = new Coords(2, -2, 2);
       shapeCoords[6] = new Coords(2, -2, -2);
       shapeCoords[7] = new Coords(-3, 4, 0);
       shapeCoords[8] = new Coords(-3, -4, 0);
       shapeCoords[9] = new Coords(-3, 2, 2);
       shapeCoords[10] = new Coords(-3, 2, -2);
       shapeCoords[11] = new Coords(-3, -2, 2);
       shapeCoords[12] = new Coords(-3, -2, -2);

    //задание индексов концов ребер
   Connection** shapeConnections = new Connection*[24];
   shapeConnections[0] = new Connection(0, 1);
    shapeConnections[1] = new Connection(0, 2);
    shapeConnections[2] = new Connection(0, 3);
    shapeConnections[3] = new Connection(0, 4);
    shapeConnections[4] = new Connection(0, 5);
    shapeConnections[5] = new Connection(0, 6);
    shapeConnections[6] = new Connection(1, 7);
    shapeConnections[7] = new Connection(2, 8);
    shapeConnections[8] = new Connection(3, 9);
    shapeConnections[9] = new Connection(4, 10);
    shapeConnections[10] = new Connection(5, 11);
    shapeConnections[11] = new Connection(6, 12);
    shapeConnections[12] = new Connection(1, 3);
    shapeConnections[13] = new Connection(3, 5);
    shapeConnections[14] = new Connection(5, 2);
    shapeConnections[15] = new Connection(2, 6);
    shapeConnections[16] = new Connection(6, 4);
    shapeConnections[17] = new Connection(4, 1);
    shapeConnections[18] = new Connection(7, 9);
    shapeConnections[19] = new Connection(9, 11);
    shapeConnections[20] = new Connection(11, 8);
    shapeConnections[21] = new Connection(8, 12);
    shapeConnections[22] = new Connection(12, 10);
    shapeConnections[23] = new Connection(10, 7);


    //создали фигуру 8 вершин с координатами из массива координат и 5 ребер с индексами концов ребер
    shape = new Shape(13, shapeCoords, 24, shapeConnections);


    float** transformMatrix = new float*[4];

    for (int i = 0; i < 4; i++) {
        transformMatrix[i] = new float[4];
        for (int j = 0; j < 4; j++) {
            if (i == j) {
                transformMatrix[i][j] = 1;
            }
            else
                transformMatrix[i][j] = 0;
        }
    }

    //задали координаты точки зрения
    //int viewX = 0;
    //int viewY = 10;
    //int viewZ = 0;


    float _viewX = viewX;
    float _viewY = viewY;
    float _viewZ = viewZ;

    Coords* view = new Coords(_viewX, _viewY, _viewZ);

    //переходим из СКМ->СКН

    //сделали сдвиг, координаты с минусом
    //Coords* view = new Coords(-viewX, -viewY, -viewZ);

    float cos1 = cos(M_PI * alpha/ 180);
    float sin1 = sin(M_PI * alpha / 180);

    //поворот вокруг ОХ
    rotateShapeX(transformMatrix, cos1, sin1);
    float** superCoords = new float*[4];
    for(int i = 0; i < 4 ; i++) {
        superCoords[i] = new float[1];
    }

    superCoords[0][0] = viewX;
    superCoords[0][1] = viewY;
    superCoords[0][2] = viewZ;
    superCoords[0][3] = 1;


    matrixMultiplication(superCoords, 1, 4, transformMatrix, 4, 4);

    view->setX(superCoords[0][0]);
    view->setY(superCoords[0][1]);
    view->setZ(superCoords[0][2]);

    Coords* translateCoords = new Coords(-view->getX(), -view->getY(), -view->getZ());

     for (int i = 0; i < 4; i++) {
         for (int j = 0; j < 4; j++) {
             if (i == j) {
                 transformMatrix[i][j] = 1;
             }
             else
                 transformMatrix[i][j] = 0;
         }
     }



     //переходим из СКМ->СКН

     //сделали сдвиг и получаем координаты
     cout << translateCoords->getX() << ' ' << translateCoords->getY() << ' ' << translateCoords->getZ() << endl;
     translateShape(transformMatrix, translateCoords);
  //сделалли смену ориентации
     scaleShape(transformMatrix, -1, 1, 1);
 //и Меняем направление оси OY (поворот вокруг оси OX2 на 90°).
     rotateShapeX(transformMatrix, 0, 1);
//считаем корень из квадарт координат
     float d = sqrt(view->getX() * view->getX() + view->getY() * view->getY());
 //считаем косинус и синус для матрицы
     float cosU = view->getY() / d;
     float sinU = view->getX() / d;
//Направляем ось OZ3 так, чтобы она пересекла ось OZ (поворот вокруг осиOY3 на угол u).
     rotateShapeY(transformMatrix, cosU, sinU);

     float s = sqrt(d*d + view->getZ() * view->getZ());
     float cosW = d / s;
     float sinW = view->getZ() / s;
 //Поворачиваем ось OZ4 так, чтобы она смотрела в начало координат.
     rotateShapeX(transformMatrix, cosW, sinW);
   //получение фигуры с матрицой с новыми измененными координатами, учитывая преобразования
     setNewCoords(shape, transformMatrix);

     float r = sqrt(view->getX() * view->getX() + view->getY() * view->getY() + view->getZ() * view->getZ());
     //Переход от СКН к СКК Для параллельной проекции xk = xн; yk = yн

     // Переход от СКК к СКЭи
     for (int i = 0; i < 13; i++) {
         Coords* first = shape->getCoords(i);
         float P = 5;//полуразмер окна
         float newXF = first->getX();//r/first->getZ()
         newXF = newXF / P * 250 + 250;
         float newYF = first->getY();//r/first->getZ()
         newYF = newYF / P * 250 + 250;
         shape->SetCoords(i, newXF, 500-newYF, first->getZ());
        // Coords* bamp = shape->getCoords(i);
     }

     for (int i = 0; i < 4; i++) {
         delete [] transformMatrix[i];
     }
     delete [] transformMatrix;
     delete view;

     // Переход от СКЭи к СКЭф, это прорисовка полученных экранных координат на дисплее.
     int conN = shape->getConN();
     for (int i = 0; i < conN; i++)
     {
         painter.setPen(Qt::blue);//голубым рисуем каждую сторону
         Connection* connection = shape->getConnection(i);
         Coords* first = shape->getCoords(connection->getBegin());
         Coords* second = shape->getCoords(connection->getEnd());
         painter.drawLine(first->getX(), first->getY(), second->getX(), second->getY());

     }

     delete shape;
}

void Area::timerEvent(QTimerEvent *) {

    alpha += 1;//поварачиваем угол для движения
    if (alpha > 30)//поворот на 30 градусов
         killTimer(myTimer);// если угол больше 30, останавливаемся
    else
        update();// обновляем внешний вид

}

void Area::hideEvent(QHideEvent *) {
    killTimer(myTimer);           // удаляем таймер
}

void Area::start_prog() {
     myTimer = startTimer(50); // создаем таймер 50
}

void Area::setNewCoords(Shape *shape, float** changeMatrix)
{
    //получение матрицы с новыми измененными координатами, учитывая преобразования
    int n = shape->getN();
    Coords **coords = new Coords*[n];
    float **newMatrix = new float*[1];
    newMatrix[0] = new float[4];
    for (int i = 0; i < n; i++) {
        coords[i] = shape->getCoords(i);
    }
    for (int i = 0; i < n; i++) {
        newMatrix[0][0] = coords[i]->getX();
        newMatrix[0][1] = coords[i]->getY();
        newMatrix[0][2] = coords[i]->getZ();
        newMatrix[0][3] = 1;
        matrixMultiplication(newMatrix, 1, 4, changeMatrix, 4, 4);
        shape->SetCoords(i, newMatrix[0][0], newMatrix[0][1], newMatrix[0][2]);
    }
    delete [] newMatrix[0];
    delete [] newMatrix;
    delete [] coords;
}

void Area::translateShape(float** oldMatrix, Coords* value)
//СКМ сдвигаем так, чтобы точка зрения стала началом координат.
//Соответствующая матрица сдвига умножается на исходную матрицу
{
    float** newMatrix = new float*[4];
    //заполняем матрицу на диагонали 1 последняя строчка-коорд точки зрения с минусом
    for (int i = 0; i < 4; i++) {
        newMatrix[i] = new float[4];
        for (int j = 0; j < 4; j++) {
            if (i == j) {
                newMatrix[i][j] = 1;
            }
            else
                newMatrix[i][j] = 0;
        }
    }
    newMatrix[3][0] = value->getX();
    newMatrix[3][1] = value->getY();
    newMatrix[3][2] = value->getZ();
    //перемножение новой и старой матрицы
    matrixMultiplication(oldMatrix, 4, 4, newMatrix, 4, 4);
    for (int i = 0; i < 4; i++) {
        delete [] newMatrix[i];
    }
    delete [] newMatrix;
}

void Area::rotateShapeX(float** oldMatrix, float cosV, float sinV)
//Ось yн имеет тенденцию вверх.
// направление оси OY (поворот вокруг оси OX2 на 90°).
//Угол поворота положительный, т.к. меняется не координаты точки, а система координат и
//система левая, а не правая (дважды смена знака)
{
    float** newMatrix = new float*[4];
    for (int i = 0; i < 4; i++) {
        newMatrix[i] = new float[4];
        for (int j = 0; j < 4; j++) {
            if (i == j) {
                newMatrix[i][j] = 1;
            }
            else
                newMatrix[i][j] = 0;
        }
    }
    newMatrix[1][1] = cosV;
    newMatrix[1][2] = -sinV;
    newMatrix[2][1] = sinV;
    newMatrix[2][2] = cosV;
    matrixMultiplication(oldMatrix, 4, 4, newMatrix, 4, 4);
    for (int i = 0; i < 4; i++) {
        delete [] newMatrix[i];
    }
    delete [] newMatrix;
}

void Area::rotateShapeY(float** oldMatrix, float cosV, float sinV)
{
    //поворот вокруг ОУ
    float** newMatrix = new float*[4];
    for (int i = 0; i < 4; i++) {
        newMatrix[i] = new float[4];
        for (int j = 0; j < 4; j++) {
            if (i == j) {
                newMatrix[i][j] = 1;
            }
            else
                newMatrix[i][j] = 0;
        }
    }
    newMatrix[0][0] = cosV;
    newMatrix[0][2] = sinV;
    newMatrix[2][0] = -sinV;
    newMatrix[2][2] = cosV;
    matrixMultiplication(oldMatrix, 4, 4, newMatrix, 4, 4);
    for (int i = 0; i < 4; i++) {
        delete [] newMatrix[i];
    }
    delete [] newMatrix;
}
void Area::rotateShapeZ(float** oldMatrix, float cosV, float sinV)
{
    //поворот вокруг ОZ
    float** newMatrix = new float*[4];
    for (int i = 0; i < 4; i++) {
        newMatrix[i] = new float[4];
        for (int j = 0; j < 4; j++) {
            if (i == j) {
                newMatrix[i][j] = 1;
            }
            else
                newMatrix[i][j] = 0;
        }
    }
    newMatrix[0][0] = cosV;
    newMatrix[0][1] = -sinV;
    newMatrix[1][0] = sinV;
    newMatrix[1][1] = cosV;
    matrixMultiplication(oldMatrix, 4, 4, newMatrix, 4, 4);
    for (int i = 0; i < 4; i++) {
        delete [] newMatrix[i];
    }
    delete [] newMatrix;
}
void Area::scaleShape(float** oldMatrix, float valueX, float valueY, float valueZ)
//2. СКН – левая.Смена ориентации системы (из правой в левую) происходит за счет
//изменения направление оси OX (зеркальное отражение)
{
    float** newMatrix = new float*[4];
    for (int i = 0; i < 4; i++) {
        newMatrix[i] = new float[4];
        for (int j = 0; j < 4; j++) {
            if (i == j) {
                newMatrix[i][j] = 1;
            }
            else
                newMatrix[i][j] = 0;
        }
    }
    newMatrix[0][0] = valueX;
    newMatrix[1][1] = valueY;
    newMatrix[2][2] = valueZ;
    matrixMultiplication(oldMatrix, 4, 4, newMatrix, 4, 4);
    for (int i = 0; i < 4; i++) {
        delete [] newMatrix[i];
    }
    delete [] newMatrix;
}

void Area::matrixMultiplication(float **first, int firstRow, int firstColumn, float** second, int secondRow, int secondColumn) {
    //умножение матрриц
    float** matrixCopy = new float*[firstRow];

    for (int i = 0; i < firstRow; i++) {
        matrixCopy[i] = new float[firstColumn];
        for (int j = 0; j < firstColumn; j++) {
            matrixCopy[i][j] = first[i][j];
            first[i][j] = 0;
        }
    }
    for (int i = 0; i < firstRow; i++) {
        for (int j = 0; j < secondColumn; j++) {
            for (int k = 0; k < firstColumn; k++) {
                first[i][j] += matrixCopy[i][k] * second[k][j];
            }
        }
    }
    for (int i = 0; i < firstRow; i++) {
        delete [] matrixCopy[i];
    }
    delete [] matrixCopy;
}
