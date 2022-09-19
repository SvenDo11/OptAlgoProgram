#include "neighborhood.h"

#include <QRandomGenerator>
#include <memory>

QRandomGenerator *gen = QRandomGenerator::global();

Neighborhood::Neighborhood()
{

}

std::shared_ptr<RectSolution> Neighborhood::randomSolution(RectangleInstance *I)
{
    std::shared_ptr<RectSolution> sol(new RectSolution(I->size(), I->getBoxlength()));

    for(int i = 0; i< I->size(); i++)
    {
        int w = I->at(i)->width;
        int h = I->at(i)->heigth;

        while(true)
        {
            int box = gen->bounded(0, I->size());
            int x   = gen->bounded(0, I->getBoxlength()-w);
            int y   = gen->bounded(0, I->getBoxlength()-h);

            rectType *newRect = new rectType(x, y, box, w, h);

            if(sol->isValid(newRect))
            {
               sol->addRect(i, newRect);
               break;
            }
            else
            {
                delete newRect;
            }
        }
    }
    return sol;
}
