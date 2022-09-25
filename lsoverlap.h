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

protected:
    RectSolution initialSolution(RectangleInstance *I) override;
    RectSolution neighborhood(RectSolution n) override;
    double cost(RectSolution s) override;

private:
    double allowedOverlap;
};

#endif // LSOVERLAP_H
