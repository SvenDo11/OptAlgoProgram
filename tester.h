#ifndef TESTER_H
#define TESTER_H

#include "algorithmrunner.h"
#include "testrunner.h"

#include <QDialog>
#include <QObject>
#include <QSpinBox>
#include <sstream>
#include <QScrollArea>
#include <QTextBrowser>


typedef Algorithmrunner::algorithm algorithm;

class Tester : public QDialog
{
    Q_OBJECT
public:
    Tester(QWidget *parent = nullptr);

public slots:
    void runConcurrent();

    void print(const std::string &msg);
private:
    QSpinBox *instanceBox;
    QSpinBox *amountBox;
    QSpinBox *lengthBox;
    QSpinBox *minWBox;
    QSpinBox *maxWBox;
    QSpinBox *minHBox;
    QSpinBox *maxHBox;
    QSpinBox *stopBox;

    QScrollArea *scrollArea;
    QTextBrowser *logBox;
    std::stringstream outputStr;

    TestRunner *runner;
};

#endif // TESTER_H
