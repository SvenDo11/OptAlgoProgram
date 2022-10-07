#include "tester.h"

#include "rectangleinstance.h"

#include <QVBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QDialogButtonBox>

Tester::Tester(QWidget *parent): QDialog(parent)
{
    QVBoxLayout *lyt_main = new QVBoxLayout;

    QFormLayout *lyt_meta = new QFormLayout();
    QLabel *instanceLabel = new QLabel(QString("Amount Instances:"));
    instanceBox = new QSpinBox();
    instanceBox->setRange(1, 10000);
    instanceBox->setValue(2);
    lyt_meta->addRow(instanceLabel, instanceBox);

    QLabel *stopLabel = new QLabel(QString("Timeout in sec (-1 = none):"));
    stopBox = new QSpinBox;
    stopBox->setRange(-1, 10000000);
    stopBox->setValue(-1);
    lyt_meta->addRow(stopLabel, stopBox);

    QLabel *amount_label = new QLabel(QString("Amount Rectangles:"));
    amountBox = new QSpinBox();
    amountBox->setRange(1, 10000);
    amountBox->setValue(100);
    lyt_meta->addRow(amount_label, amountBox);

    QLabel *length_label = new QLabel(QString("Boxlength L:"));
    lengthBox = new QSpinBox();
    lengthBox->setRange(1, 10000000);
    lengthBox->setValue(20);
    lyt_meta->addRow(length_label, lengthBox);
    lyt_main->addLayout(lyt_meta);

    for(int i = 0; i < 2; ++i)
    {
        QFrame *hline = new QFrame();
        hline->setFrameShape(QFrame::HLine);
        lyt_main->addWidget(hline);

        QFormLayout *lyt_form = new QFormLayout();
        QLabel *label = new QLabel( i ? "Height:" : "Width:");
        QLabel *min_label = new QLabel(QString("Min"));
        QSpinBox *min_box = new QSpinBox();
        min_box->setRange(1, 10000000);
        min_box->setValue(2);
        QLabel *max_label = new QLabel(QString("Max"));
        QSpinBox *max_box = new QSpinBox();
        max_box->setRange(1, 10000000);
        max_box->setValue(16);

        lyt_main->addWidget(label);
        lyt_form->addRow(min_label, min_box);
        lyt_form->addRow(max_label, max_box);
        lyt_main->addLayout(lyt_form);

        if(i)
        {
            minHBox = min_box;
            maxHBox = max_box;
        }
        else
        {
            minWBox = min_box;
            maxWBox = max_box;
        }
    }

    scrollArea = new QScrollArea;
    logBox = new QTextBrowser;
    scrollArea->setWidget(logBox);
    logBox->setMinimumWidth(500);
    logBox->setMinimumHeight(100);
    scrollArea->adjustSize();
    scrollArea->setWidgetResizable(true);
    lyt_main->addWidget(scrollArea);

    QDialogButtonBox *buttonBox = new QDialogButtonBox
            ( QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
              Qt::Horizontal);
    lyt_main->addWidget(buttonBox);

    bool conn = connect(buttonBox, &QDialogButtonBox::accepted,
                   this, &Tester::runConcurrent);
    Q_ASSERT(conn);
    conn = connect(buttonBox, &QDialogButtonBox::rejected,
                   this, &Tester::reject);
    Q_ASSERT(conn);

    setLayout(lyt_main);

    runner = new TestRunner(this);
    connect(runner, &TestRunner::print,
            this, &Tester::print);
}

void Tester::runConcurrent()
{
    // Get instance parameter
    int amountInstances = instanceBox->value();
    int amountRectangles = amountBox->value();
    int boxLength = lengthBox->value();
    int wMin = minWBox->value();
    int wMax = maxWBox->value();
    int hMin = minHBox->value();
    int hMax = maxHBox->value();
    int timeout = stopBox->value();
    timeout = (timeout > 0) ? timeout * 1000: -1;

    QFuture<void> fut = QtConcurrent::run(&TestRunner::run, runner, amountInstances,
                                          amountRectangles, boxLength, wMin, wMax, hMin, hMax, timeout);
}

void Tester::print(const std::string &msg)
{
    outputStr << msg;
    logBox->setText(outputStr.str().c_str());
}
