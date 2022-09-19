#include "lstest.h"
#include <cmath>

LSTest::LSTest(int x, int y): state(0), offsetX(x), offsetY(y)
{
}

int LSTest::initialSolution(int i)
{
    return i;
}

int LSTest::neighborhood(int s)
{
    int newS = s;
    switch(state)
    {
        case 0:
        {
            newS = s+1;
            break;
        }
        case 1:
        {
            newS = s-1;
            break;
        }
    }
    return newS;
}

int LSTest::cost(int s)
{
    return std::pow((s-offsetX), 2) + offsetY;
}

bool LSTest::terminate(int s)
{
    return state == 2;
}

void LSTest::updatedS()
{

}

void LSTest::keptS()
{
    state++;
}
