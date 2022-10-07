#ifndef LSOVERLAP_H
#define LSOVERLAP_H

#include "lsgeometrie.h"
#include "rectangleinstance.h"
#include "rectsolution.h"

#define PREVBOX 0
#define NEXTBOX 1
#define MOVEDOWN 2
#define MOVELEFT 3
#define MOVERIGHT 4
#define MOVEUP 5
#define ROTATE 6

//class LSOverlap : public LocalSearch<RectangleInstance*, RectSolution>
class LSOverlap : public LSGeometrie
{
public:
    LSOverlap();
    LSOverlap(std::function<void(RectSolution)> func);
    LSOverlap(std::function<void(RectSolution)> drawSFunc, std::function<bool()> stopFunc);

    static double calcOverlap(const rectType &rec1, const rectType &rec2);
protected:
    RectSolution initialSolution(RectangleInstance *I) override;
    RectSolution neighborhood(RectSolution n) override;
    double cost(RectSolution s) override;
    bool terminate(RectSolution s) override;

    RectSolution fixOverlaps(RectSolution);

private:
    double allowedOverlap;
    bool hardFix = false;
    int iteration = 0;
    int PENALTY = 100;
};

#endif // LSOVERLAP_H
