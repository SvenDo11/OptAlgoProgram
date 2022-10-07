#ifndef LOCALSEARCH_H
#define LOCALSEARCH_H

template<typename InputT, typename SolutionT>
class LocalSearch
{
public:
    LocalSearch(){}

    SolutionT runLocalSearch(InputT instance)
    {
        currentS = initialSolution(instance);
        currentCost = cost(currentS);

        while(!terminate(currentS))
        {
            newS = neighborhood(currentS);
            double newCost = cost(newS);

            if(newCost < currentCost)
            {
                currentS = newS;
                currentCost = newCost;

                updatedS();
            }
            else
            {
                keptS();
            }
        }
        return currentS;
    }

    SolutionT operator() (InputT instance)
    {
        return runLocalSearch(instance);
    }

protected:
    virtual void updatedS() {}
    virtual void keptS() {}
    virtual SolutionT initialSolution(InputT i) = 0;
    virtual SolutionT neighborhood(SolutionT n) = 0;
    virtual double cost(SolutionT s) = 0;
    virtual bool terminate(SolutionT s) = 0;

    SolutionT currentS, newS;
    double currentCost;
};

#endif // LOCALSEARCH_H
