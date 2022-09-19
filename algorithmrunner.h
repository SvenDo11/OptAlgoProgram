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
    enum algorithm { localSearchGeometrie};

    explicit Algorithmrunner(QObject *parent = nullptr);

    void runAlgorithm(RectangleInstance *instance);

    void runLocalSearchGeometrie(RectangleInstance *instance);
public slots:
    void setAlgorithm(Algorithmrunner::algorithm algo);

signals:
    void updateRectangles(RectSolution S);
    void message(QString msg, int timeout = 0);

private:
    algorithm currentAlgorithm;
    int cnt = 0;
};

#endif // ALGORITHMRUNNER_H
