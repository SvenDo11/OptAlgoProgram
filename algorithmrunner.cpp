#include "algorithmrunner.h"

#include "lsgeometrie.h"

Algorithmrunner::Algorithmrunner(QObject *parent)
    : QObject{parent}
{

}

void Algorithmrunner::setAlgorithm(Algorithmrunner::algorithm algo)
{
    currentAlgorithm = algo;
}

void Algorithmrunner::runAlgorithm(RectangleInstance *instance)
{
    switch(currentAlgorithm)
    {
        case Algorithmrunner::algorithm::localSearchGeometrie:
            runLocalSearchGeometrie(instance);
            break;
        default:
            break;
    }
}

void Algorithmrunner::runLocalSearchGeometrie(RectangleInstance *instance)
{
    if(instance == nullptr)
        return;

    LSGeometrie searcher{};
    searcher.runLocalSearch(instance);
};
