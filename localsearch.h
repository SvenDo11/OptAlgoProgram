#ifndef LOCALSEARCH_H
#define LOCALSEARCH_H

template<typename InputT, typename SolutionT>
class LocalSearch
{
public:
    LocalSearch(){}

    SolutionT runLocalSearch(InputT instance)
    {
        SolutionT s = initialSolution(instance);
        int currentCost = cost(s);

        while(!terminate(s))
        {
            SolutionT newS = neighborhood(s);
            int newCost = cost(newS);

            if(newCost < currentCost)
            {
                s = newS;
                currentCost = newCost;

                updatedS();
            }
            else
            {
                keptS();
            }
        }
        return s;
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
    virtual int cost(SolutionT s) = 0;
    virtual bool terminate(SolutionT s) = 0;
};

#endif // LOCALSEARCH_H
