#ifndef RECTANGLEINSTANCE_H
#define RECTANGLEINSTANCE_H

#include <QVarLengthArray>

#include <iostream>

typedef struct Rect
{
    Rect(int w, int h): width(w), heigth(h){}
    int width;
    int heigth;

    friend std::ostream& operator<<(std::ostream& os, Rect *rec)
    {
        os << "(" << std::to_string(rec->width) << "," << std::to_string(rec->heigth) << ")";
        return os;
    }
} Rect;

class RectangleInstance : public QVarLengthArray<Rect*>
{
public:
    RectangleInstance(int size, int boxLength);
    ~RectangleInstance();

    void add_rectangle(int id, int width, int heigth);
    int getBoxlength();
    void fillWithRandom(int wMin, int wMax, int hMin, int hMax);

    friend std::ostream& operator<<(std::ostream& os, RectangleInstance *rec);
private:
    int boxLength;
};

#endif // RECTANGLEINSTANCE_H
