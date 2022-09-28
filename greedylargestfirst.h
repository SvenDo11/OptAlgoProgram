#ifndef GREEDYLARGESTFIRST_H
#define GREEDYLARGESTFIRST_H

#include "greedy.h"
#include "rectangleinstance.h"
#include "rectsolution.h"

#include <QList>

class GreedyLargestFirst : public Greedy<RectangleInstance*, QList<int>, RectSolution>
{
public:
    GreedyLargestFirst();
    GreedyLargestFirst(std::function<void(RectSolution)> func);

protected:
    int getN(RectangleInstance*) override;
    QList<int> sort(RectangleInstance*) override;
    RectSolution initialResult(QList<int>) override;
    bool accept(RectSolution) override;
    RectSolution alter(RectSolution, QList<int>, int) override;
private:
    RectangleInstance *I;
    std::function<void(RectSolution)> drawS = [](RectSolution){};
};

#endif // GREEDYLARGESTFIRST_H
