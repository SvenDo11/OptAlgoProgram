#ifndef LSOVERLAP_H
#define LSOVERLAP_H

#include "localsearch.h"
#include "rectangleinstance.h"
#include "rectsolution.h"

class LSOverlap : public LocalSearch<RectangleInstance*, RectSolution>
{
public:
    LSOverlap();
    LSOverlap(std::function<void(RectSolution)> func);

protected:
    void updatedS() override;
    void keptS() override;
    RectSolution initialSolution(RectangleInstance *I) override;
    RectSolution neighborhood(RectSolution n) override;
    double cost(RectSolution s) override;
    bool terminate(RectSolution s) override;

private:
    std::function<void(RectSolution)> drawS;
    RectangleInstance *I;
};

#endif // LSOVERLAP_H
