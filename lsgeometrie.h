#ifndef LSGEOMETRIE_H
#define LSGEOMETRIE_H

#include "localsearch.h"
#include "rectangleinstance.h"
#include "rectsolution.h"

#define MOVEDOWN 0
#define MOVELEFT 1
#define MOVERIGHT 2
#define MOVEUP 3
#define ROTATE 4

class LSGeometrie : public LocalSearch<RectangleInstance*, RectSolution>
{
public:
    LSGeometrie();

protected:
    void updatedS() override {}
    void keptS() override {}
    RectSolution initialSolution(RectangleInstance *I) override;
    RectSolution neighborhood(RectSolution n) override;
    int cost(RectSolution s) override;
    bool terminate(RectSolution s) override;

    void advanceOp();

private:
    RectangleInstance *I;
    int currentRect = 0;
    int currentOp = 0;
    int iteration = 0;
};

#endif // LSGEOMETRIE_H
