#include "rectangleinstance.h"

#include <iostream>
#include <QRandomGenerator>

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

void RectangleInstance::fillWithRandom(int wMin, int wMax, int hMin, int hMax)
{
    QRandomGenerator *gen = QRandomGenerator::global();

    for(int i = 0; i < this->size(); ++i)
    {
        this->add_rectangle(i,
                            gen->bounded(wMin, wMax+1),
                            gen->bounded(hMin, hMax+1));
    }
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
