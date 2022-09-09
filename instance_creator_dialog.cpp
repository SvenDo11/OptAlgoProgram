#include "instance_creator_dialog.h"

#include "rectangleinstance.h"

#include <QFormLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QIntValidator>
#include <QSpinBox>
#include <QDialogButtonBox>
#include <QGridLayout>
#include <QFrame>
#include <QRandomGenerator>
#include <QDateTime>

#include <iostream>

Instance_creator_dialog::Instance_creator_dialog(QWidget *parent): QDialog(parent)
{
    QVBoxLayout *lyt_main = new QVBoxLayout(this);

    QFormLayout *lyt_meta = new QFormLayout(this);
    QLabel *amount_label = new QLabel(QString("Amount Rectangles:"), this);
    amount_box = new QSpinBox(this);
    amount_box->setRange(1, 10000);
    lyt_meta->addRow(amount_label, amount_box);

    QLabel *length_label = new QLabel(QString("Boxlength L:"), this);
    length_box = new QSpinBox(this);
    length_box->setRange(1, MAX_LENGTH);
    lyt_meta->addRow(length_label, length_box);
    lyt_main->addLayout(lyt_meta);

    for(int i = 0; i < 2; ++i)
    {
        QFrame *hline = new QFrame(this);
        hline->setFrameShape(QFrame::HLine);
        lyt_main->addWidget(hline);

        QFormLayout *lyt_form = new QFormLayout(this);
        QLabel *label = new QLabel( i ? "Height:" : "Width:", this);
        QLabel *min_label = new QLabel(QString("Min"), this);
        QSpinBox *min_box = new QSpinBox(this);
        min_box->setRange(1, MAX_LENGTH);
        QLabel *max_label = new QLabel(QString("Max"), this);
        QSpinBox *max_box = new QSpinBox(this);
        max_box->setRange(1, MAX_LENGTH);

        lyt_main->addWidget(label);
        lyt_form->addRow(min_label, min_box);
        lyt_form->addRow(max_label, max_box);
        lyt_main->addLayout(lyt_form);

        if(i)
        {
            height_min_box = min_box;
            height_max_box = max_box;
        }
        else
        {
            width_min_box = min_box;
            width_max_box = max_box;
        }
    }

    QDialogButtonBox *buttonBox = new QDialogButtonBox
            ( QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
              Qt::Horizontal, this );
    lyt_main->addWidget(buttonBox);

    bool conn = connect(buttonBox, &QDialogButtonBox::accepted,
                   this, &Instance_creator_dialog::create_instance);
    Q_ASSERT(conn);
    conn = connect(buttonBox, &QDialogButtonBox::rejected,
                   this, &Instance_creator_dialog::reject);
    Q_ASSERT(conn);

    setLayout(lyt_main);
}

void Instance_creator_dialog::create_instance()
{
    if(recInstance != nullptr)
        delete recInstance;

    int amount = amount_box->value();
    int L = length_box->value();
    int width_min = width_min_box->value();
    int width_max = width_max_box->value();
    int height_min = height_min_box->value();
    int height_max = height_max_box->value();

    QRandomGenerator *gen = QRandomGenerator::global();
    recInstance = new RectangleInstance(amount, L);

    for(int i = 0; i < amount; ++i)
    {
        recInstance->add_rectangle(i,
                                   gen->bounded(width_min, width_max),
                                   gen->bounded(height_min, height_max));
    }

    std::cout << recInstance << std::endl;

    close();
}
