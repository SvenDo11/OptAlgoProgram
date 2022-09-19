#ifndef GEOMETRIENEIGHBOR_H
#define GEOMETRIENEIGHBOR_H

#include "neighborhood.h"
#define MOVEDOWN 0
#define MOVELEFT 1
#define MOVERIGHT 2
#define MOVEUP 3
#define ROTATE 4

class GeometrieNeighbor : public Neighborhood
{
public:
    GeometrieNeighbor();

    std::shared_ptr<RectSolution> neighborSolution(RectangleInstance *I, std::shared_ptr<RectSolution> S);
    int cost(RectangleInstance *I, std::shared_ptr<RectSolution> S);
private:
    void advanceOp(std::shared_ptr<RectSolution> S);
    int currentRect;
    int currentOp;
};

#endif // GEOMETRIENEIGHBOR_H
