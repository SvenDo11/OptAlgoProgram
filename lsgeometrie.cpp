#include "lsgeometrie.h"

#include <QRandomGenerator>

LSGeometrie::LSGeometrie()
{

}

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
            int x   = gen->bounded(0, instance->getBoxlength()-w);
            int y   = gen->bounded(0, instance->getBoxlength()-h);

            rectType *newRect = new rectType(x, y, box, w, h);

            if(sol.isValid(newRect))
            {
               sol.addRect(i, newRect);
               break;
            }
            else
            {
                delete newRect;
            }
        }
    }

    return sol;
}

RectSolution LSGeometrie::neighborhood(RectSolution s)
{
    RectSolution newS(s);
    rectType *rect = newS.rectangles[currentRect];
    int temp = 0;
    while(true)
    {
        switch(currentOp)
        {
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
        if(newS.isValid(currentRect, rect))
            break;
        else
            advanceOp();
    }

    return newS;
}

void LSGeometrie::advanceOp()
{
    currentOp++;
    if(currentOp > ROTATE)
    {
        currentOp = MOVEDOWN;
        currentRect++;
        if(currentRect >= I->size())
        {
            currentRect = 0;
        }
    }
}

int LSGeometrie::cost(RectSolution s)
{
    return 0;
}

bool LSGeometrie::terminate(RectSolution s)
{
    std::cout << "\n=========\nSolution:\n" << s << std::endl;
    iteration = iteration + 1;
    return iteration >= 2;
}
