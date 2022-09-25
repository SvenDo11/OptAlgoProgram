#ifndef LSPERMUTATION_H
#define LSPERMUTATION_H

#include "localsearch.h"
#include "qobjectdefs.h"
#include "rectangleinstance.h"
#include "rectsolution.h"

typedef struct Permutation
{
    Permutation()
    {
        perm.resize(0);
        sol = nullptr;
    }
    Permutation(int size)
    {
        perm.resize(size);
        sol = nullptr;
    }
    int &operator[] (int i)
    {
        return perm[i];
    }
    std::vector<int> perm;
    RectSolution *sol;
} Permutation;

class LSPermutation : public LocalSearch<RectangleInstance*, Permutation>
{
public:
    LSPermutation();
    LSPermutation(std::function<void(RectSolution)> func);
protected:
    void updatedS() override;
    void keptS() override;
    Permutation initialSolution(RectangleInstance *I) override;
    Permutation neighborhood(Permutation n) override;
    double cost(Permutation s) override;
    bool terminate(Permutation s) override;

    RectSolution* genSolution(Permutation perm, RectSolution *sol, int rotateID = -1);
    bool nextIsLast();

private:
    RectangleInstance *I;
    RectSolution *S;
    RectSolution *newS;

    std::function<void(RectSolution)> drawS;

    int currentRect;
    int currentOp;
    int lastUpdatedRect;
    int lastUpdatedOp;
};

#endif // LSPERMUTATION_H
