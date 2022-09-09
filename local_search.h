#ifndef LOCAL_SEARCH_H
#define LOCAL_SEARCH_H

#include <functional>

template<typename InputT, typename SolutionT>
void local_search(InputT I,
                  std::function<SolutionT(InputT)> initial_solution,
                  std::function<SolutionT(InputT, SolutionT)> neighborhood,
                  std::function<int(InputT, SolutionT)> cost,
                  std::function<bool()> terminate)
{
    // Initialize Parameter
    SolutionT s = initial_solution(I);
    int current_cost = cost(s);

    // Main Loop
    while(terminate())
    {
        SolutionT new_s = neighborhood(I, s);

        int new_cost = cost(new_s);

        if(new_cost < current_cost)
        {
            s = new_s;
            current_cost = new_cost;
        }
    }
}
#endif // LOCAL_SEARCH_H
