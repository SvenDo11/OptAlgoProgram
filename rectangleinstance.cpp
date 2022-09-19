#include "rectangleinstance.h"

#include <iostream>

RectangleInstance::RectangleInstance(int size, int L): QVarLengthArray<Rect*>(size)
{
    boxLength = L;
}

RectangleInstance::~RectangleInstance()
{
    for(Rect *r: *this)
    {
        delete r;
    }
}

void RectangleInstance::add_rectangle(int id, int width, int heigth)
{
    Rect *newElem = new Rect(width, heigth);

    replace(id, newElem);
}

int RectangleInstance::getBoxlength()
{
    return boxLength;
}

std::ostream& operator<<(std::ostream& os, RectangleInstance *rec)
{
    os << "size: " << rec->size() << "; ";
    os << "L: " << rec->boxLength;
    os << "\n[";
    for(Rect *r: *rec)
    {
        os << r << ",";
    }
    os << "]" << std::endl;
    return os;
}
