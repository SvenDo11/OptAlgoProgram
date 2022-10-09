#include "greedylargestfirst.h"
#include <list>

GreedyLargestFirst::GreedyLargestFirst()
{

}
GreedyLargestFirst::GreedyLargestFirst(std::function<void(RectSolution)> func):
    drawS(func)
{

}

int GreedyLargestFirst::getN(RectangleInstance* instance)
{
    return instance->size();
}

QList<int> GreedyLargestFirst::sort(RectangleInstance* instance)
{
    typedef struct area{
        int id, area;
        bool operator<(struct area other)
        {
            return area > other.area;
        }
    } area;

    I = instance;
    QList<int> result;
    std::list<area> arr;
    for(int i = 0; i < I->size(); ++i)
    {
        Rect *rec = I->value(i);
        arr.push_back(area{i, rec->width * rec->heigth});
    }
    arr.sort();
    for(area a: arr)
    {
        result.append(a.id);
    }
    return result;
}

RectSolution GreedyLargestFirst::initialResult(QList<int> list)
{
    return RectSolution{static_cast<int>(list.size()), I->getBoxlength()};
}

bool GreedyLargestFirst::accept(RectSolution sol)
{
    for(QList<int> box: sol.boxes)
    {
        for(int i = 0; i < box.length(); ++i)
        {
            rectType rec = sol.rectangles[box[i]];
            if(!sol.isValid(box[i], rec))
                return false;
        }
    }
    drawS(sol);
    return true;
}

RectSolution GreedyLargestFirst::alter(RectSolution sol, QList<int> list, int itt)
{
    int id = list[itt];
    int w = I->value(id)->width;
    int h = I->value(id)->heigth;
    int x = I->getBoxlength()-w;
    int y = I->getBoxlength()-h;

    rectType rec(x, y, 0, w, h);
    // find right box.
    for(int b = 0; b < sol.boxes.length(); ++b)
    {
        rec.box = b;
        if(sol.isValid(rec))
            break;
        // Check rotated rectangle
        int oldW = rec.w;
        rec.w = rec.h;
        rec.h = oldW;
        if(sol.isValid(rec))
            break;
    }
    // Push down
    for(int newY = y; newY >= 0; newY--)
    {
        int oldY = rec.y;
        rec.y = newY;
        if(!sol.isValid(rec))
        {
            rec.y = oldY;
            break;
        }
    }
    // Push as far to the left as posible
    for(int newX = x; newX >= 0; newX--)
    {
        int oldX = rec.x;
        rec.x = newX;
        if(!sol.isValid(rec))
        {
            rec.x = oldX;
            break;
        }
    }
    // Push down
    for(int newY = rec.y; newY >= 0; newY--)
    {
        int oldY = rec.y;
        rec.y = newY;
        if(!sol.isValid(rec))
        {
            rec.y = oldY;
            break;
        }
    }
    sol.addRect(id, rec);

    return sol;
}
