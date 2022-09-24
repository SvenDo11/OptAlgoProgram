#include "lsgeometrie.h"

#include <QRandomGenerator>
#include <cmath>
#include <math.h>

LSGeometrie::LSGeometrie()
{
    drawS = [](RectSolution s) {std::cout << s << std::endl;};
}

LSGeometrie::LSGeometrie(std::function<void(RectSolution)> func): drawS(func){}

RectSolution LSGeometrie::initialSolution(RectangleInstance *instance)
{
    I = instance;

    QRandomGenerator *gen = QRandomGenerator::global();
    RectSolution sol{int(instance->size()), instance->getBoxlength()};

    for(int i = 0; i< instance->size(); i++)
    {
        int w = instance->at(i)->width;
        int h = instance->at(i)->heigth;

        while(true)
        {
            int box = gen->bounded(0, instance->size());
            int x   = (w >= instance->getBoxlength()) ? 0 : gen->bounded(0, instance->getBoxlength()-w);
            int y   = (h >= instance->getBoxlength()) ? 0 : gen->bounded(0, instance->getBoxlength()-h);

            rectType newRect = rectType(x, y, box, w, h);

            if(sol.isValid(newRect))
            {
               sol.addRect(i, newRect);
               break;
            }
        }
    }

    return sol;
}

RectSolution LSGeometrie::neighborhood(RectSolution s)
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
        if(newS.isValid(currentRect, *rect))
            return newS;
        else
        {
            if(nextIsLast())
                return s;
            advanceOp();
        }
    }
}

void LSGeometrie::advanceOp()
{
    currentOp++;
    if(currentOp > ROTATE)
    {
        currentOp = PREVBOX;
        currentRect++;
        if(currentRect >= I->size())
        {
            currentRect = 0;
        }
    }
}

double LSGeometrie::cost(RectSolution s)
{
    double cost = 0;

    // Max cost for all boxes with one
    double maxboxcost = s.boxes.length() * log(s.boxes.length()-1);
    int fac = 1;
    for(fac = 1; fac < maxboxcost; fac *= 10);

    for(const QList<int> &box: s.boxes)
    {
        if(!box.empty())
        {
            cost += fac;
            cost += log(s.boxes.length() - box.length());
        }
    }

    double maxheight = 1.5 * pow(s.boxLength, 2);
    for(fac = 1; fac < maxheight; fac *= 10);
    fac *= 10;
    cost *= fac;

    for(rectType &rec: s.rectangles)
    {
        cost += pow((rec.x + rec.w/2), 2) + pow((rec.y + rec.h/2), 2);
        //cost += pow(rec.x, 2) + pow(rec.y,2);
    }
    std::cout << "Cost: " << cost << std::endl;
    return cost;
}

bool LSGeometrie::terminate(RectSolution s)
{
    if(updated)
    {
        std::cout << "\n=========\n" << s << std::endl;
        updated = false;
    }
    iteration = iteration + 1;
    if(iteration % 10 == 0)
        drawS(s);
    /**
    if(iteration == 1000)
    {
        std::cout << "iteration limit reached" << std::endl;
        return true;
    }
    */
    // check if all neighbors have been checked without an improvement
    if(nextIsLast())
        return true;

    return false;
}

bool LSGeometrie::nextIsLast()
{

    return ((currentRect == lastUpdatedRect
            && currentOp + 1 == lastUpdatedOp) // next op in current rect
        || (currentRect + 1 == lastUpdatedRect
            && currentOp == ROTATE
            && lastUpdatedOp == PREVBOX)); // next op in next rect
}

void LSGeometrie::switchBox(RectSolution &sol, int id, int boxid)
{
    rectType *rect = &sol.rectangles[id];
    sol.boxes[rect->box].removeOne(id);
    sol.boxes[boxid].append(id);
    rect->box = boxid;
}

void LSGeometrie::updatedS()
{
    lastUpdatedOp = currentOp;
    lastUpdatedRect = currentRect;

    std::cout << "Updated S to newS: " << std::endl;
    updated =true;
}

void LSGeometrie::keptS()
{
    if(!nextIsLast())
        advanceOp();
}
