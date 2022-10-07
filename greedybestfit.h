#ifndef GREEDYBESTFIT_H
#define GREEDYBESTFIT_H

#include "greedy.h"
#include "rectangleinstance.h"
#include "rectsolution.h"

class GreedyBestFit : public Greedy<RectangleInstance*, QList<int>, RectSolution>
{
public:
    GreedyBestFit();
    GreedyBestFit(std::function<void(RectSolution)> func);

protected:
    int getN(RectangleInstance*) override;
    QList<int> sort(RectangleInstance*) override;
    RectSolution initialResult(QList<int>) override;
    bool accept(RectSolution) override;
    RectSolution alter(RectSolution, QList<int>, int) override;
private:
    RectangleInstance *I;
    int freeBox = 0;
    std::function<void(RectSolution)> drawS = [](RectSolution){};
};

#endif // GREEDYBESTFIT_H
