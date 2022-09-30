#include "animationtoolbox.h"

#include <QVBoxLayout>
#include <QLabel>

AnimationToolBox::AnimationToolBox()
{
    QVBoxLayout *animationLayout = new QVBoxLayout;
    animationLayout->setAlignment(Qt::AlignTop);

    QLabel *animationLabel = new QLabel(tr("Update Visuals:"));
    animationLayout->addWidget(animationLabel);
    timeBtn = new QRadioButton(tr("Time Intervall"));

    iterBtn = new QRadioButton(tr("Iteration Invervall"));

    stepBtn =new QRadioButton(tr("User Steptrough"));

    animationLayout->addWidget(timeBtn);
    animationLayout->addWidget(iterBtn);
    animationLayout->addWidget(stepBtn);

    QWidget *animationWidget = new QWidget;
    animationWidget->setLayout(animationLayout);
    this->addItem(animationWidget, tr("Animation"));
}
