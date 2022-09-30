#ifndef ALGOTOOLBOX_H
#define ALGOTOOLBOX_H

#include "algorithmrunner.h"
#include <QToolBox>
#include <QComboBox>
#include <QRadioButton>
#include <QObject>
#include <QWidget>
#include <QSpinBox>
#include <QLabel>

class AlgoToolBox : public QToolBox
{
    Q_OBJECT
public:
    AlgoToolBox();
public slots:
    void algoUpdated(int index);
    void variantUpdated(int index);
    void animationUpdated(bool checked);
    void intervallUpdated(int value);

signals:
    void setAlgorithm(Algorithmrunner::algorithm newAlgo);
    void setAnimation(Algorithmrunner::animation newAnimation);
    void setInterval(int intervalS);
private:
    void newAlgo();
    void hideInterval(bool flag);

    QStringList algoList = {"Local Search", "Greedy"};
    QStringList variantListLS = {"Geometrie", "Permutation", "Geometrie Overlap"};
    QStringList variantListGreedy = {"Largest First", "B"};

    QComboBox *algorithmBox;
    QComboBox *variationBox;

    QRadioButton *noneBtn;
    QRadioButton *timeBtn;
    QRadioButton *iterBtn;
    QRadioButton *stepBtn;

    QLabel *intervalLabel;
    QSpinBox *intervalBox;
};

#endif // ALGOTOOLBOX_H
