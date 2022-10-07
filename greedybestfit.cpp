#include "greedybestfit.h"
#include <list>

GreedyBestFit::GreedyBestFit()
{

}

GreedyBestFit::GreedyBestFit(std::function<void(RectSolution)> func):
    drawS(func)
{

}

int GreedyBestFit::getN(RectangleInstance* instance)
{
    return instance->size();
}

QList<int> GreedyBestFit::sort(RectangleInstance* instance)
{
    freeBox = 0;
    typedef struct area{
        int id, area;
        bool operator<(struct area other)
        {
            return area < other.area;
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

RectSolution GreedyBestFit::initialResult(QList<int> list)
{
    return RectSolution{static_cast<int>(list.size()), I->getBoxlength()};
}

bool GreedyBestFit::accept(RectSolution sol)
{
    bool valid = sol.isValid();
    if(valid)
        drawS(sol);
    return valid;
}

RectSolution GreedyBestFit::alter(RectSolution sol, QList<int> list, int itt)
{
    int id = list[itt];
    int w = I->value(id)->width;
    int h = I->value(id)->heigth;
    int x = I->getBoxlength()-w;
    int y = I->getBoxlength()-h;
    int baseArea = pow(I->getBoxlength(), 2) - (w * h);

    rectType rec(x, y, 0, w, h);
    QList<int> costs = {};
    // Determine remaining area for each box
    for(int b = 0; b <= freeBox; ++b)
    {
        rec.box = b;
        if(sol.isValid(rec))
        {
            int cost = baseArea;
            for(int id: sol.boxes[b])
            {
                rectType &r = sol.rectangles[id];
                cost -= r.w * r.h;
            }
            costs.append(cost);
        }
        else
            costs.append(-1);
    }

    // find best fit
    int box = 0;
    for(int b = 0; b < costs.length(); b++)
    {
        if((costs[b] != -1 && costs[b] < costs[box]) ||
            (costs[b] != -1 && costs[box] == -1))
            box = b;
    }
    rec.box = box;

    if(box == freeBox)
        freeBox++;

    for(int newY = y; newY >=0; newY--)
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
    sol.addRect(id, rec);

    return sol;
}
