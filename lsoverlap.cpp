#include "lsoverlap.h"

#include <QRandomGenerator>
#include <math.h>

LSOverlap::LSOverlap()
{

}
LSOverlap::LSOverlap(std::function<void(RectSolution)> func): LSGeometrie(func)
{

}
LSOverlap::LSOverlap(std::function<void(RectSolution)> drawSFunc, std::function<bool()> stopFunc):
    LSGeometrie(drawSFunc, stopFunc)
{

}

RectSolution LSOverlap::initialSolution(RectangleInstance *instance)
{
    I = instance;

    QRandomGenerator *gen = QRandomGenerator::global();
    RectSolution sol{int(instance->size()), instance->getBoxlength()};

    for(int i = 0; i< instance->size(); i++)
    {
        int w = instance->at(i)->width;
        int h = instance->at(i)->heigth;

        int box = gen->bounded(0, instance->size());
        int x   = (w >= instance->getBoxlength()) ? 0 : gen->bounded(0, instance->getBoxlength()-w);
        int y   = (h >= instance->getBoxlength()) ? 0 : gen->bounded(0, instance->getBoxlength()-h);

        rectType newRect = rectType(x, y, box, w, h);

        sol.addRect(i, newRect);
    }

    return sol;
}

RectSolution LSOverlap::neighborhood(RectSolution s)
{
    RectSolution newS;
    while(true)
    {
        newS = RectSolution(s);
        rectType *rect = &newS.rectangles[currentRect];
        int temp = 0;
        switch(currentOp)
        {
            case PREVBOX:
            {
                int boxID = rect->box;
                if(boxID-1 < 0)
                    rect->box = -1;
                else
                {
                    for(boxID = boxID-1; boxID > 0; boxID--)
                        if(!newS.boxes[boxID].isEmpty())
                            break;
                    switchBox(newS, currentRect, boxID);
                    rect->x = newS.boxLength - rect->w;
                    rect->y = newS.boxLength - rect->h;
                }
                break;
            }
            case NEXTBOX:
            {
                int boxID = rect->box;
                if(boxID+1 >= newS.boxes.length())
                    rect->box = -1;
                else
                {
                    for(boxID = boxID + 1; boxID < newS.boxes.length()-1; boxID++)
                        if(!newS.boxes[boxID].isEmpty())
                            break;
                    switchBox(newS, currentRect, boxID);
                    rect->x = newS.boxLength - rect->w;
                    rect->y = newS.boxLength - rect->h;
                }
                break;
            }
            case MOVEDOWN:
                rect->y = rect->y - 1;
                break;
            case MOVELEFT:
                rect->x = rect->x - 1;
                break;
            case MOVERIGHT:
                rect->y = rect->y + 1;
                break;
            case MOVEUP:
                rect->x = rect->x + 1;
                break;
            case ROTATE:
                temp = rect->w;
                rect->w = rect->h;
                rect->h = temp;
                break;
            default:
                assert(1 == 0);
                break;
        }
        if(newS.isContained(*rect))
            return newS;
        else
        {
            if(nextIsLast())
                return s;
            advanceOp();
        }
    }
    return newS;
}

bool LSOverlap::terminate(RectSolution s)
{
    bool term = LSGeometrie::terminate(s);

    if(iteration % 10 == 0)
        allowedOverlap -= 0.05;
    return term;
}

double LSOverlap::cost(RectSolution s)
{
    double cost = 0;

    // Punish overlap
    for(QList<int> box: s.boxes)
    {
        for(int i = 0; i < box.length()-1; ++i)
        {
            for(int j = i+1; j < box.length(); ++j)
            {
                double overlap = calcOverlap(s.rectangles[box[i]], s.rectangles[box[j]]);
                if(overlap > allowedOverlap)
                    cost += overlap * PENALTY;
            }
        }
    }
    int fac = 1;
    //for(fac = 1; fac < (PENALTY * pow(s.rectangles.length(), 2)); fac *= 10);

    // Max cost for all boxes with one
    double maxboxcost = s.boxes.length() * log(s.boxes.length()-1);
    for(fac = 1; fac < maxboxcost; fac *= 10);

    for(const QList<int> &box: s.boxes)
    {
        if(!box.empty())
        {
            cost += fac;
            cost += log(s.boxes.length()+1 - box.length());
        }
    }

    double maxheight = 1.5 * pow(s.boxLength, 2);
    for(fac = 1; fac < maxheight; fac *= 10);
    fac *= 10;
    cost *= fac;

    for(rectType &rec: s.rectangles)
    {
        cost += pow((rec.x + rec.w/2), 2) + pow((rec.y + rec.h/2), 2);
    }
    return cost;
}

double LSOverlap::calcOverlap(const rectType &rec1, const rectType &rec2)
{
    if(rec1.box != rec2.box)
        return 0.0;

    int overlapX = std::min(rec1.x+rec1.w, rec2.x+rec2.w) - std::max(rec1.x, rec2.x);
    if(overlapX < 0)
        overlapX = 0;

    int overlapY = std::min(rec1.y+rec1.h, rec2.y+rec2.h) - std::max(rec1.y, rec2.y);
    if(overlapY < 0)
        overlapY = 0;

    int overlapArea = overlapX * overlapY;
    if(overlapArea == 0)
        return 0.0;
    int maxArea = std::max((rec1.w*rec1.h), (rec2.w*rec2.h));
    return ((double) overlapArea)/((double) maxArea);
}
