#include "algorithmrunner.h"

#include "lsgeometrie.h"
#include "lspermutation.h"

#include <QtConcurrent/QtConcurrentRun>

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

void Algorithmrunner::drawSRequested(RectSolution S)
{
    emit updateRectangles(S);
}
