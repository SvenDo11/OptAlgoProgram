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
    rectType(const rectType &other)
    {
        x = other.x;
        y = other.y;
        w = other.w;
        h = other.h;
        box = other.box;
    }
    rectType &operator= (const rectType &other)
    {
        x = other.x;
        y = other.y;
        w = other.w;
        h = other.h;
        box = other.box;
        return *this;
    }
    int x;
    int y;
    int w;
    int h;
    int box;

    friend std::ostream& operator<<(std::ostream& os, rectType rec)
    {
        os << "x: " << rec.x << ", y: " << rec.y
           << ", w: " << rec.w << ", h: " << rec.h << ", box: " << rec.box;
        return os;
    }
} rectType;

class RectSolution
{
public:
    RectSolution();
    RectSolution(int rectAmount, int boxLength);
    RectSolution(const RectSolution &other);
    ~RectSolution();

    RectSolution& operator=(const RectSolution& other);

    bool isValid(rectType newRect);
    bool isValid(int id, rectType newRect);
    void addRect(int id, rectType newRect);
    void addRect(int id, int x, int y, int w, int h, int box);

    QVarLengthArray<QList<int>> boxes;
    QVarLengthArray<rectType> rectangles;

    int boxLength;

    friend std::ostream& operator<<(std::ostream& os, RectSolution sol);
private:
    bool isOverlapping(int a1, int a2, int b1, int b2);
};

#endif // RECTSOLUTION_H
