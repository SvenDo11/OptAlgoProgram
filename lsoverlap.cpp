#include "lsoverlap.h"

#include <QRandomGenerator>

LSOverlap::LSOverlap(): drawS([](RectSolution){})
{

}
LSOverlap::LSOverlap(std::function<void(RectSolution)> func): drawS(func)
{

}

void LSOverlap::updatedS()
{
}

void LSOverlap::keptS()
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

RectSolution LSOverlap::neighborhood(RectSolution n)
{
}

double LSOverlap::cost(RectSolution s)
{
}

bool LSOverlap::terminate(RectSolution s)
{
}
