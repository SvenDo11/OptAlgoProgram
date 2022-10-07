#ifndef TESTRUNNER_H
#define TESTRUNNER_H

#include "algorithmrunner.h"
#include "rectangleinstance.h"

#include <QObject>

typedef Algorithmrunner::algorithm algorithm;
class TestRunner : public QObject
{
    Q_OBJECT
public:
    explicit TestRunner(QObject *parent = nullptr);

    void run(int amountInstances, int amountRectangles,
            int boxLength, int wMin, int wMax,
            int hMin, int hMax, int stopTime = -1);
signals:
    void print(const std::string &msg);
protected:
    int runAlgorithm(RectangleInstance *I, algorithm algo, int stopTime, bool *valid, qint64 *runtime);
    static std::string strName(algorithm algo);
private:
    const algorithm algoList[5] = {algorithm::localSearchGeometrie,
                                   algorithm::localSearchPermutation,
                                   algorithm::localSearchGeometrieOverlap,
                                   algorithm::greedyLargestFirst,
                                   algorithm::greedyBestFit};
};

#endif // TESTRUNNER_H
