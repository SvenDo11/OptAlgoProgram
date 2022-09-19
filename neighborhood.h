#ifndef NEIGHBORHOOD_H
#define NEIGHBORHOOD_H

#include "rectsolution.h"
#include "rectangleinstance.h"

class Neighborhood
{
public:
    Neighborhood();

    std::shared_ptr<RectSolution> randomSolution(RectangleInstance *I);
    virtual std::shared_ptr<RectSolution> neighborSolution(RectangleInstance *I, std::shared_ptr<RectSolution> sol) = 0;
    virtual int cost(RectangleInstance *I, std::shared_ptr<RectSolution> S) = 0;
};

#endif // NEIGHBORHOOD_H
