#include "algorithmrunner.h"

#include "lsgeometrie.h"
#include "lspermutation.h"
#include "lsoverlap.h"

#include <QtConcurrent/QtConcurrentRun>

Algorithmrunner::Algorithmrunner(QObject *parent)
    : QObject{parent}
{

}

void Algorithmrunner::setAlgorithm(Algorithmrunner::algorithm algo)
{
    currentAlgorithm = algo;
    std::cout << "Algorithmrunner set algorithm to: " << algo << std::endl;
}

void Algorithmrunner::runAlgorithm(RectangleInstance *instance)
{
    QFuture<void> fut;
    switch(currentAlgorithm)
    {
        case Algorithmrunner::algorithm::localSearchGeometrie:
        {
            fut = QtConcurrent::run(&Algorithmrunner::runLocalSearchGeometrie, this, instance);
            break;
        }
        case Algorithmrunner::algorithm::localSearchPermutation:
        {
            fut = QtConcurrent::run(&Algorithmrunner::runLocalSearchPermutation, this, instance);
            break;
        }
        case Algorithmrunner::algorithm::localSearchGeometrieOverlap:
        {
            fut = QtConcurrent::run(&Algorithmrunner::runLocalSearchOverlap, this, instance);
            break;
        }
        default:
            break;
    }
}

void Algorithmrunner::runLocalSearchGeometrie(RectangleInstance *instance)
{
    if(instance == nullptr)
        return;

    LSGeometrie searcher([this](RectSolution s){drawSRequested(s);});
    searcher.runLocalSearch(instance);
};

void Algorithmrunner::runLocalSearchPermutation(RectangleInstance *instance)
{
    if(instance == nullptr)
        return;

    LSPermutation searcher([this](RectSolution s){drawSRequested(s);});
    searcher.runLocalSearch(instance);
}

void Algorithmrunner::runLocalSearchOverlap(RectangleInstance *instance)
{
    if(instance == nullptr)
        return;
    LSOverlap searcher([this](RectSolution s){drawSRequested(s);});
    searcher.runLocalSearch(instance);
}

void Algorithmrunner::drawSRequested(RectSolution S)
{
    emit updateRectangles(S);
}
