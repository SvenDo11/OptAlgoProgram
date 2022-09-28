#ifndef ALGORITHMRUNNER_H
#define ALGORITHMRUNNER_H

#include "rectangleinstance.h"
#include "rectsolution.h"
#include <QObject>
#include <QtConcurrent/QtConcurrentRun>

class Algorithmrunner : public QObject
{
    Q_OBJECT
public:
    enum algorithm { localSearchGeometrie, localSearchPermutation, localSearchGeometrieOverlap, greedyLargestFirst};

    explicit Algorithmrunner(QObject *parent = nullptr);

    void runAlgorithm(RectangleInstance *instance);

public slots:
    void setAlgorithm(Algorithmrunner::algorithm algo);
    void drawSRequested(RectSolution S);
    void requestStop();

signals:
    void updateRectangles(RectSolution S);
    void message(QString msg, int timeout = 0);

protected:
    void execute(RectangleInstance *instance);

private:
    algorithm currentAlgorithm;
    int cnt = 0;

    bool stopRequest = false;
};

#endif // ALGORITHMRUNNER_H
