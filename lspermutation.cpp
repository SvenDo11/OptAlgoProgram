#include "lspermutation.h"


LSPermutation::LSPermutation(): I(nullptr), S(nullptr), newS(nullptr),
    drawS([](RectSolution s){}), currentRect(0), currentOp(0), lastUpdatedRect(0), lastUpdatedOp(0)
{

}

LSPermutation::LSPermutation(std::function<void(RectSolution)> func):
    I(nullptr), S(nullptr), newS(nullptr),
    drawS(func), currentRect(0), currentOp(0), lastUpdatedRect(0), lastUpdatedOp(0)
{

}
LSPermutation::LSPermutation(std::function<void(RectSolution)> drawSFunc, std::function<bool()> stopFunc):
    I(nullptr), S(nullptr), newS(nullptr),
    drawS(drawSFunc), stopRequested(stopFunc), currentRect(0), currentOp(0), lastUpdatedRect(0), lastUpdatedOp(0)
{

}

LSPermutation::~LSPermutation()
{
    if(S != nullptr)
        delete S;
    if(newS != nullptr)
        delete newS;
}

void LSPermutation::updatedS()
{
    lastUpdatedRect = currentRect;
    lastUpdatedOp = currentOp;

    delete S;
    S = newS;
    newS = nullptr;
}
void LSPermutation::keptS()
{
    delete newS;
    newS = nullptr;
}
Permutation LSPermutation::initialSolution(RectangleInstance *instance)
{
    I = instance;
    currentRect = 0;
    currentOp = 1;
    lastUpdatedRect = 0;
    lastUpdatedRect = 1;

    Permutation perm(I->size());
    for(int i = 0; i < I->size(); ++i)
    {
        perm[i] = i;
    }
    if(S != nullptr)
    {
        delete S;
    }
    S = genSolution(perm, nullptr);
    perm.sol = S;

    return perm;
}
Permutation LSPermutation::neighborhood(Permutation perm)
{
    currentOp++;
    if(currentOp > I->size())
    {
        currentRect++;
        if(currentRect >= I->size() - 1)
            currentRect = 0;
        currentOp = currentRect + 1;
    }

    Permutation newPerm(I->size());
    int rotateID = -1;
    for(int i = 0; i < I->size(); ++i)
    {
        newPerm[i] = perm[i];
    }
    if(currentOp < I->size())
    {
        newPerm[currentRect] = perm[currentOp];
        newPerm[currentOp] = perm[currentRect];
    }
    else
    {
        rotateID = currentRect;
    }

    if(newS != nullptr)
        delete newS;
    newS = genSolution(newPerm, S, rotateID);
    newPerm.sol = newS;

    return newPerm;
}
double LSPermutation::cost(Permutation s)
{
    if(s.sol == nullptr)
        return 0.0;
    double cost = 0;
    for(QList<int> &box: s.sol->boxes)
        if(!box.isEmpty())
            cost++;
    return cost;
}
bool LSPermutation::terminate(Permutation s)
{
    drawS(*s.sol);
    // check if all neighbors have been checked without an improvement
    return nextIsLast() || stopRequested();
}

bool LSPermutation::nextIsLast()
{
    // next op in current rect
    if(currentRect == lastUpdatedRect
            && currentOp + 1 == lastUpdatedOp)
        return true;
    // next rect first op
    if(currentRect + 1 == lastUpdatedRect
            && currentOp == I->size()
            && lastUpdatedOp == lastUpdatedRect + 1)
        return true;
    //next rect first op for first rect
    if(currentRect == I->size()-1
            && currentOp == I->size()
            && lastUpdatedRect == 0
            && lastUpdatedOp == 1)
        return true;
    return false;
}
RectSolution* LSPermutation::genSolution(Permutation perm, RectSolution *sol, int rotateID)
{
    RectSolution *newS = new RectSolution(I->length(), I->getBoxlength());
    int i = 0;
    if(sol != nullptr)
    {
        for(i = 0; i < currentRect; i++)
        {
            int id = perm[i];
            rectType rec(sol->rectangles[id]);
            newS->addRect(id, rec);
        }
    }
    for(; i < newS->rectangles.length(); ++i)
    {
        int id = perm[i];
        int y = 0;
        int w = (sol == nullptr) ? I->value(id)->width : sol->rectangles[id].w;
        int h = (sol == nullptr) ? I->value(id)->heigth : sol->rectangles[id].h;
        if(id == rotateID)
        {
            int temp = w;
            w = h;
            h = temp;
        }
        int x = I->getBoxlength()-w;

        rectType rec(x, y, 0, w, h);
        bool foundY = false;
        // find right y height, for right box.
        for(int b = 0; b < newS->boxes.length(); ++b)
        {
           rec.box = b;
           for(int j = 0; j < newS->boxLength - h; j++)
           {
               rec.y = j;
               if(newS->isValid(rec))
               {
                   foundY = true;
                   break;
               }
           }
           if(foundY)
               break;
       }

       // Push as far to the left as posible
       for(int newX = x; newX >= 0; newX--)
       {
           int oldX = rec.x;
           rec.x = newX;
            if(!newS->isValid(rec))
            {
                rec.x = oldX;
                break;
            }
       }
       newS->addRect(id, rec);
    }
    return newS;
}
