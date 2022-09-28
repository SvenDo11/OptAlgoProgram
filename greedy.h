#ifndef GREEDY_H
#define GREEDY_H

template<typename InputType, typename ListType, typename ResultType>
class Greedy
{
public:
    Greedy(){}
    ResultType runGreedyAlgorithm(InputType I)
    {
        ListType values = sort(I);
        int n = getN(I);
        ResultType result = initialResult(values);

        for(int i = 0; i < n; ++i)
        {
            ResultType newResult = alter(result, values, i);
            if(accept(newResult))
            {
                result = newResult;
            }
        }
        return result;
    }

protected:
    virtual int getN(InputType) = 0;
    virtual ListType sort(InputType) = 0;
    virtual ResultType initialResult(ListType) = 0;
    virtual bool accept(ResultType) = 0;
    virtual ResultType alter(ResultType, ListType, int) = 0;
};

#endif // GREEDY_H
