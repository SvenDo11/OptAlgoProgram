#ifndef ALGOTOOLBOX_H
#define ALGOTOOLBOX_H

#include <QToolBox>
#include <QObject>
#include <QWidget>

class AlgoToolBox : public QToolBox
{
    Q_OBJECT
public:
    AlgoToolBox();
public slots:
    void algoUpdated();
    void variantUpdated();
};

#endif // ALGOTOOLBOX_H
