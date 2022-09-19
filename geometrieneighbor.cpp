#include "geometrieneighbor.h"

GeometrieNeighbor::GeometrieNeighbor():currentRect(0), currentOp(0)
{

}

std::shared_ptr<RectSolution> GeometrieNeighbor::neighborSolution(RectangleInstance *I, std::shared_ptr<RectSolution> sol)
{
    std::shared_ptr<RectSolution> newSol = std::make_shared<RectSolution>(*sol);
    rectType *rect = newSol->rectangles[currentRect];
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
        if(newSol->isValid(currentRect, rect))
            break;
        else
            advanceOp(sol);
    }
    return newSol;
}

int GeometrieNeighbor::cost(RectangleInstance *I, std::shared_ptr<RectSolution> S)
{
    int cost = 0;
    for(const QList<int> &box: S->boxes)
    {
        if(!box.empty())
            cost++;
    }
    return cost;
}

void GeometrieNeighbor::advanceOp(std::shared_ptr<RectSolution> S)
{
    currentOp++;
    if(currentOp > ROTATE)
    {
        currentOp = MOVEDOWN;
        currentRect++;
        if(currentRect >= S->rectangles.length())
        {
            //TODO: End of all rects, maybe do something special here
            currentRect = 0;
        }
    }
}
