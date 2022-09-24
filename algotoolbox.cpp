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

    this->setMinimumWidth(runOptionWidget->sizeHint().width());
    this->addItem(runOptionWidget, tr("Algorithms"));
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
    }
    }
}
