#ifndef RECTSOLUTION_H
#define RECTSOLUTION_H

#include <QVarLengthArray>
#include <QList>

#include <iostream>

typedef struct rectType
{
    rectType(int posX, int posY, int box, int width, int heigth):
        x(posX), y(posY), w(width), h(heigth), box(box){}
    rectType():
        x(0), y(0), w(0), h(0), box(0){}
    int x;
    int y;
    int w;
    int h;
    int box;

    friend std::ostream& operator<<(std::ostream& os, rectType *rec)
    {
        os << "x: " << rec->x << ", y: " << rec->y
           << ", w: " << rec->w << ", h: " << rec->h;
        return os;
    }
} rectType;

class RectSolution
{
public:
    RectSolution(int rectAmount, int boxLength);
    RectSolution(RectSolution const &other);
    ~RectSolution();

    bool isValid(rectType* newRect);
    bool isValid(int id, rectType* newRect);
    void addRect(int id, rectType* newRect);
    void addRect(int id, int x, int y, int w, int h, int box);

    QVarLengthArray<QList<int>> boxes;
    QVarLengthArray<rectType*> rectangles;

    int boxLength;

    friend std::ostream& operator<<(std::ostream& os, RectSolution sol);
private:
    bool isOverlapping(int a1, int a2, int b1, int b2);
};

#endif // RECTSOLUTION_H
