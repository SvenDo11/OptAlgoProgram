#include "lsoverlap.h"

#include <QRandomGenerator>

LSOverlap::LSOverlap()
{

}
LSOverlap::LSOverlap(std::function<void(RectSolution)> func): LSGeometrie(func)
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

double LSOverlap::cost(RectSolution s)
{
    return 0.0;
}
