#include "rectsolution.h"

#include <iostream>

RectSolution::RectSolution(int rectAmount, int boxLength): boxLength(boxLength)
{
    boxes.resize(rectAmount);
    rectangles.resize(rectAmount);
}

RectSolution::RectSolution(RectSolution const &other)
{
    //std::cout << "Copyed a RectSolution" << std::endl;
    boxLength = other.boxLength;

    boxes.resize(other.boxes.length());
    rectangles.resize(other.rectangles.length());

    for(int i = 0; i < other.rectangles.length(); ++i)
    {
        rectType *rect = new rectType(*other.rectangles[i]);
        addRect(i, rect);
    }
}

RectSolution::~RectSolution()
{
    for(auto rect: rectangles)
        delete rect;
}

bool RectSolution::isValid(rectType *newRect)
{
    return isValid(-1, newRect);
}

bool RectSolution::isValid(int id, rectType *newRect)
{
    if(newRect->x + newRect->w > boxLength
            && newRect->x + newRect->w > boxLength)
        return false;

    QList<int> box = boxes[newRect->box];
    for(int i: box)
    {
        if(i == id)
            continue;

        rectType *rect = rectangles[i];
        if(isOverlapping(rect->x, rect->x + rect->w, newRect->x, newRect->x + newRect->w)
                &&isOverlapping(rect->y, rect->y + rect->h, newRect->y, newRect->y + newRect->h))
            return false;
    }
    return true;
}

void RectSolution::addRect(int id, rectType *newRect)
{
    boxes[newRect->box].append(id);
    rectangles[id] = newRect;
}

void RectSolution::addRect(int id, int x, int y, int w, int h, int box)
{
    rectType *rect = new rectType(x, y, box, w, h);
    addRect(id, rect);
}

bool RectSolution::isOverlapping(int a1, int a2, int b1, int b2)
{
    return a2 > b1 && b2 > a1;
}

std::ostream& operator<<(std::ostream& os, RectSolution sol)
{
    int i = 0;
    os << "Solution:\n";
    for(QList<int> box: sol.boxes)
    {
        os << "  Box" << std::to_string(i) <<": [";
        for(int rectID: box)
        {
            os << "\n    {" << sol.rectangles[rectID] << "}";
        }
        os << "  ]\n";
        i++;
    }
    return os;
}
