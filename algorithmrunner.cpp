#include "algorithmrunner.h"

#include "lsgeometrie.h"
#include "lspermutation.h"
#include "lsoverlap.h"
#include "greedylargestfirst.h"

#include <QtConcurrent/QtConcurrentRun>

Algorithmrunner::Algorithmrunner(QObject *parent)
    : QObject{parent}, currentAlgorithm(Algorithmrunner::algorithm::localSearchGeometrie),
      animationType(Algorithmrunner::animation::timeBased),
      updateInterval(20)
{

}

void Algorithmrunner::setAlgorithm(Algorithmrunner::algorithm algo)
{
    currentAlgorithm = algo;
}

void Algorithmrunner::runAlgorithm(RectangleInstance *instance)
{
    if(isRunning)
        return;
    currentItteration = 0;
    isRunning = true;
    QFuture<void> fut = QtConcurrent::run(&Algorithmrunner::execute, this, instance);
}

void Algorithmrunner::execute(RectangleInstance *instance)
{
    if(instance == nullptr)
        return;

    QString algorithmName = "";
    RectSolution sol;
    auto drawFunc = [this](RectSolution s){drawSRequested(s);};
    auto stopFunc = [this](){return stopRequest;};
    switch(currentAlgorithm)
    {
        case Algorithmrunner::algorithm::localSearchGeometrie:
        {
            LSGeometrie searcher(drawFunc, stopFunc);
            sol = searcher.runLocalSearch(instance);
            algorithmName = "Local Search Geometrie";
            break;
        }
        case Algorithmrunner::algorithm::localSearchPermutation:
        {
            LSPermutation searcher(drawFunc, stopFunc);
            Permutation perm = searcher.runLocalSearch(instance);
            sol = RectSolution(*(perm.sol));
            algorithmName = "Local Search Permutation";
            break;
        }
        case Algorithmrunner::algorithm::localSearchGeometrieOverlap:
        {
            LSOverlap searcher(drawFunc, stopFunc);
            sol = searcher.runLocalSearch(instance);
            algorithmName = "Local Search Geometrie Overlap";
            break;
        }
        case Algorithmrunner::algorithm::greedyLargestFirst:
        {
            GreedyLargestFirst searcher(drawFunc);
            sol = searcher.runGreedyAlgorithm(instance);
            algorithmName = "Greedy Largest First";
            break;
        }
        default:
            break;
    }
    emit message("Finished " + algorithmName, 5000);
    if(animationType != Algorithmrunner::animation::none)
        emit updateRectangles(sol);
    stopRequest = false;
    isRunning = false;
}

void Algorithmrunner::drawSRequested(RectSolution S)
{
    currentItteration++;
    switch(animationType)
    {
    case Algorithmrunner::animation::timeBased:
        if(QTime::currentTime() >= lastUpdated.addSecs(updateInterval))
        {
            emit updateRectangles(S);
            lastUpdated = QTime::currentTime();
        }
        break;
    case Algorithmrunner::animation::iterationBased:
        if(currentItteration % updateInterval == 0)
        {
            emit updateRectangles(S);
        }
        break;
    case Algorithmrunner::animation::step:
        emit updateRectangles(S);
        mut.lock();
        condVar.wait(&mut);
        mut.unlock();
        break;
    case Algorithmrunner::animation::none:
        break;
    }
}

void Algorithmrunner::requestStop()
{
    stopRequest = true;
}

void Algorithmrunner::advance()
{
    condVar.wakeOne();
}

void Algorithmrunner::setAnimation(Algorithmrunner::animation newAnimation)
{
    animationType = newAnimation;
}
void Algorithmrunner::setInterval(int newInterval)
{
    updateInterval = newInterval;
}
