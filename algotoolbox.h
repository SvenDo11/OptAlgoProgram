#ifndef ALGOTOOLBOX_H
#define ALGOTOOLBOX_H

#include "algorithmrunner.h"
#include <QToolBox>
#include <QComboBox>
#include <QObject>
#include <QWidget>

class AlgoToolBox : public QToolBox
{
    Q_OBJECT
public:
    AlgoToolBox();
public slots:
    void algoUpdated(int index);
    void variantUpdated(int index);
signals:
    void setAlgorithm(Algorithmrunner::algorithm newAlgo);
private:
    void newAlgo();
    QStringList algoList = {"Local Search", "Greedy"};
    QStringList variantListLS = {"Geometrie", "Permutation", "Geometrie Overlap"};
    QStringList variantListGreedy = {"A", "B"};

    QComboBox *algorithmBox;
    QComboBox *variationBox;
};

#endif // ALGOTOOLBOX_H
