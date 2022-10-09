#include "testrunner.h"

#include "lsgeometrie.h"
#include "lspermutation.h"
#include "lsoverlap.h"
#include "greedylargestfirst.h"
#include "greedybestfit.h"

TestRunner::TestRunner(QObject *parent)
    : QObject{parent}
{

}

void TestRunner::run(int amountInstances, int amountRectangles,
                    int boxLength, int wMin, int wMax,
                    int hMin, int hMax, int stopTime)
{
    if(wMin > wMax || hMin > hMax)
    {
        emit print("Min Value needs to be less than Max Value!\nAborted!");
        return;
    }
    emit print("Running " + std::to_string(amountInstances) + " tests with:\n"
          +"    Amount Rectangles: " + std::to_string(amountRectangles) + "\n"
          +"    Boxlength L: " + std::to_string(boxLength) + "\n"
          +"    " + std::to_string(wMin) + " <= Width <= " +std::to_string(wMax) + "\n"
          +"    " + std::to_string(hMin) + " <= Height <= " +std::to_string(hMax) + "\n"
          );

    for(int currentInstance = 0; currentInstance < amountInstances; ++currentInstance)
    {
        emit print("=============================\nRunning instance "
              + std::to_string(currentInstance) + ":\n");
        // Create instance
        RectangleInstance *instance = new RectangleInstance(amountRectangles, boxLength);
        instance->fillWithRandom(wMin, wMax, hMin, hMax);

        int costs[5] = {0};
        bool valid[5] = {false};
        qint64 runTimes[5] = {0};
        // run algorithms
        QFuture<int> futs[5];
        for(int i = 0; i < 5; i++)
            futs[i] = QtConcurrent::run(&TestRunner::runAlgorithm, this, instance, algoList[i], stopTime ,&valid[i], &runTimes[i]);

        // check results
        for(int i = 0; i < 5; i++)
            costs[i] = futs[i].result();

        // Write results
        emit print("Results:\nName, Is Valid, Cost(#Boxes), Runtime(ms)\n");
        for(int i = 0; i < 5; ++i)
        {
            emit print(strName(algoList[i]) + ", " + std::to_string(valid[i]) + ", "
                  + std::to_string(costs[i]) + " , " + std::to_string(runTimes[i]) + "\n");
        }
        delete instance;
    }
}

int TestRunner::runAlgorithm(RectangleInstance *I, algorithm algo, int stopTime, bool *valid, qint64 *runTime)
{
    QElapsedTimer timer;
    RectSolution sol;
    int itter = 0;
    std::function<bool()> stopFnct = [&timer, &stopTime](){if(stopTime <= 0) return false; else return timer.elapsed() >= stopTime;};
    std::function<void(RectSolution)> drawFnct = [&itter](RectSolution){itter++;};
    switch(algo)
    {
        case(algorithm::localSearchGeometrie):
        {
            LSGeometrie searcher = LSGeometrie(drawFnct, stopFnct);
            timer.start();
            sol = searcher.runLocalSearch(I);
            *runTime = timer.elapsed();
            break;
        }
        case(algorithm::localSearchGeometrieOverlap):
        {
            LSOverlap searcher = LSOverlap(drawFnct, stopFnct);
            timer.start();
            sol = searcher.runLocalSearch(I);
            *runTime = timer.elapsed();
            break;
        }
        case(algorithm::localSearchPermutation):
        {
            LSPermutation searcher = LSPermutation(drawFnct, stopFnct);
            timer.start();
            Permutation perm = searcher.runLocalSearch(I);
            sol = RectSolution(*perm.sol);
            *runTime = timer.elapsed();
            break;
        }
        case(algorithm::greedyLargestFirst):
        {
            GreedyLargestFirst searcher = GreedyLargestFirst(drawFnct);
            timer.start();
            sol = searcher.runGreedyAlgorithm(I);
            *runTime = timer.elapsed();
            break;
        }
        case(algorithm::greedyBestFit):
        {
            GreedyBestFit searcher = GreedyBestFit(drawFnct);
            timer.start();
            sol = searcher.runGreedyAlgorithm(I);
            *runTime = timer.elapsed();
            break;
        }
    }
    *valid = sol.isValid();
    int cost = sol.usedBoxes();
    emit print(strName(algo) + " is done after " + std::to_string(itter) +  " itterations!\n");
    return cost;
}

std::string TestRunner::strName(algorithm algo)
{
    switch(algo)
    {
        case algorithm::localSearchGeometrie:
            return "Local Search Geometrie  ";
        case algorithm::localSearchPermutation:
            return "Local Search Permutation";
        case algorithm::localSearchGeometrieOverlap:
            return "Local Search Overlap    ";
        case algorithm::greedyLargestFirst:
            return "Greedy Largest First    ";
        case algorithm::greedyBestFit:
            return "Greedy Best Fit         ";
    }
    return "";
}
