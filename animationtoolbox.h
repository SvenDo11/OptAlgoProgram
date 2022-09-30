#ifndef ANIMATIONTOOLBOX_H
#define ANIMATIONTOOLBOX_H

#include <QToolBox>
#include <QObject>
#include <QRadioButton>

class AnimationToolBox : public QToolBox
{
    Q_OBJECT
public:
    AnimationToolBox();
private:
    QRadioButton *noneBtn;
    QRadioButton *timeBtn;
    QRadioButton *iterBtn;
    QRadioButton *stepBtn;
};

#endif // ANIMATIONTOOLBOX_H
