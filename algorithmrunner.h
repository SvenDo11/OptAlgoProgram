#ifndef ALGORITHMRUNNER_H
#define ALGORITHMRUNNER_H

#include "rectangleinstance.h"
#include "rectsolution.h"
#include <QObject>
#include <QtConcurrent/QtConcurrentRun>
#include <QWaitCondition>
#include <QTime>

class Algorithmrunner : public QObject
{
    Q_OBJECT
public:
    enum algorithm { localSearchGeometrie, localSearchPermutation, localSearchGeometrieOverlap,
                     greedyLargestFirst, greedyBestFit};
    enum animation { timeBased, iterationBased, step, none};

    explicit Algorithmrunner(QObject *parent = nullptr);

    void runAlgorithm(RectangleInstance *instance);

public slots:
    void setAlgorithm(Algorithmrunner::algorithm algo);
    void drawSRequested(RectSolution S);
    void requestStop();
    void advance();
    void setAnimation(Algorithmrunner::animation newAnimation);
    void setInterval(int interval);

signals:
    void updateRectangles(RectSolution S);
    void message(QString msg, int timeout = 0);

protected:
    void execute(RectangleInstance *instance);

private:
    algorithm currentAlgorithm;
    int cnt = 0;

    bool isRunning = false;
    bool stopRequest = false;

    animation animationType = timeBased;
    QTime lastUpdated = QTime(0,0);
    int currentItteration = 0;
    int updateInterval;

    QMutex mut;
    QWaitCondition condVar;
};

#endif // ALGORITHMRUNNER_H
