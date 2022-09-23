#ifndef LSTEST_H
#define LSTEST_H

#include "localsearch.h"

class LSTest : public LocalSearch<int, int>
{
public:
    LSTest(int x, int y);

protected:
    void updatedS() override;
    void keptS() override;
    int initialSolution(int i) override;
    int neighborhood(int s) override;
    double cost(int s) override;
    bool terminate(int s) override;

private:
    int state;
    int offsetX;
    int offsetY;
};

#endif // LSTEST_H
