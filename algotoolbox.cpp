#include "algotoolbox.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QComboBox>

AlgoToolBox::AlgoToolBox()
{
    QVBoxLayout *runOptionLayout = new QVBoxLayout;
    runOptionLayout->setAlignment(Qt::AlignTop);

    QLabel *algorithmLabel = new QLabel(tr("Algorithm:"));
    runOptionLayout->addWidget(algorithmLabel);
    algorithmBox = new QComboBox;
    algorithmBox->addItems(algoList);
    runOptionLayout->addWidget(algorithmBox);

    QLabel *variationLabel = new QLabel(tr("Variation:"));
    runOptionLayout->addWidget(variationLabel);
    variationBox = new QComboBox;
    variationBox->addItems(variantListLS);
    runOptionLayout->addWidget(variationBox);

    QWidget *runOptionWidget = new QWidget;
    runOptionWidget->setLayout(runOptionLayout);

    connect(algorithmBox, &QComboBox::currentIndexChanged,
            this, &AlgoToolBox::algoUpdated);
    connect(variationBox, &QComboBox::currentIndexChanged,
            this, &AlgoToolBox::variantUpdated);

    // Animation settings
    QVBoxLayout *animationLayout = new QVBoxLayout;
    animationLayout->setAlignment(Qt::AlignTop);

    QLabel *animationLabel = new QLabel(tr("Update Visuals:"));
    timeBtn = new QRadioButton(tr("Time Intervall"));
    timeBtn->setChecked(true);
    connect(timeBtn, &QRadioButton::toggled,
            this, &AlgoToolBox::animationUpdated);
    iterBtn = new QRadioButton(tr("Iteration Invervall"));
    connect(iterBtn, &QRadioButton::toggled,
            this, &AlgoToolBox::animationUpdated);
    stepBtn = new QRadioButton(tr("User Steptrough"));
    connect(stepBtn, &QRadioButton::toggled,
            this, &AlgoToolBox::animationUpdated);
    noneBtn = new QRadioButton(tr("None"));
    connect(noneBtn, &QRadioButton::toggled,
            this, &AlgoToolBox::animationUpdated);

    intervalLabel = new QLabel(tr("Update Interval:"));

    intervalBox = new QSpinBox;
    intervalBox->setRange(0, 1000000);
    intervalBox->setValue(20);

    animationLayout->addWidget(animationLabel);
    animationLayout->addWidget(timeBtn);
    animationLayout->addWidget(iterBtn);
    animationLayout->addWidget(stepBtn);
    animationLayout->addWidget(noneBtn);
    animationLayout->addWidget(intervalLabel);
    animationLayout->addWidget(intervalBox);

    QWidget *animationWidget = new QWidget;
    animationWidget->setLayout(animationLayout);

    this->setMinimumWidth(runOptionWidget->sizeHint().width());
    this->addItem(runOptionWidget, tr("Algorithms"));
    this->addItem(animationWidget, tr("Animation"));
}

void AlgoToolBox::algoUpdated(int index)
{
    std::cout<< "called algo with index: " << index << std::endl;
    switch(index)
    {
    case 0:
    {
        // Local Search
        variationBox->clear();
        variationBox->addItems(variantListLS);
        variationBox->setCurrentIndex(0);
        break;
    }
    case 1:
    {
        // Greedy
        variationBox->clear();
        variationBox->addItems(variantListGreedy);
        variationBox->setCurrentIndex(0);
        break;
    }
    }
}

void AlgoToolBox::variantUpdated(int index)
{
    std::cout << "called variant with index: " << index << std::endl;
    if(index != -1)
        newAlgo();
}

void AlgoToolBox::newAlgo()
{
    switch(algorithmBox->currentIndex())
    {
    case 0:
    {
        // local search
        switch(variationBox->currentIndex())
        {
        case 0:
        {
            // Geometrie
            emit setAlgorithm(Algorithmrunner::algorithm::localSearchGeometrie);
            break;
        }
        case 1:
        {
            // Permutation
            emit setAlgorithm(Algorithmrunner::algorithm::localSearchPermutation);
            break;
        }
        case 2:
            // overlap
            emit setAlgorithm(Algorithmrunner::algorithm::localSearchGeometrieOverlap);
            break;
        }
        break;
    }
    case 1:
    {
        // greedy
        switch(variationBox->currentIndex())
        {
        case 0:
        {
            emit setAlgorithm(Algorithmrunner::algorithm::greedyLargestFirst);
            break;
        }
        }
        break;
    }
    }
}

void AlgoToolBox::animationUpdated(bool checked)
{
    if(!checked)
        return;

    typedef Algorithmrunner::animation animation;
    animation newAnimation = animation::none;
    if(timeBtn->isChecked())
    {
        newAnimation = animation::timeBased;
        hideInterval(false);
    }
    else if(iterBtn->isChecked())
    {
        newAnimation = animation::iterationBased;
        hideInterval(false);
    }
    else if(stepBtn->isChecked())
    {
        newAnimation = animation::step;
        hideInterval(true);
    }
    else
    {
        newAnimation = animation::none;
        hideInterval(true);
    }

    emit setAnimation(newAnimation);
}

void AlgoToolBox::hideInterval(bool flag)
{
    intervalLabel->setHidden(flag);
    intervalBox->setHidden(flag);
}

void AlgoToolBox::intervallUpdated(int value)
{
    emit setInterval(value);
}
