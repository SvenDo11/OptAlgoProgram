#ifndef LSGEOMETRIE_H
#define LSGEOMETRIE_H

#include "localsearch.h"
#include "rectangleinstance.h"
#include "rectsolution.h"

#define PREVBOX 0
#define NEXTBOX 1
#define MOVEDOWN 2
#define MOVELEFT 3
#define MOVERIGHT 4
#define MOVEUP 5
#define ROTATE 6

class LSGeometrie : public LocalSearch<RectangleInstance*, RectSolution>
{
public:
    LSGeometrie();
    LSGeometrie(std::function<void(RectSolution)> func);

protected:
    void updatedS() override;
    void keptS() override;
    RectSolution initialSolution(RectangleInstance *I) override;
    RectSolution neighborhood(RectSolution n) override;
    double cost(RectSolution s) override;
    bool terminate(RectSolution s) override;

    void advanceOp();
    bool nextIsLast();
    void switchBox(RectSolution &sol, int id, int newBoxID);

    RectangleInstance *I;
    int currentRect = 0;
    int currentOp = 0;
    int iteration = 0;

    std::function<void(RectSolution)> drawS;

    int lastUpdatedRect = 0;
    int lastUpdatedOp = 0;

    bool updated = true;
};

#endif // LSGEOMETRIE_H
