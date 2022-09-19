#ifndef INSTANCE_CREATOR_DIALOG_H
#define INSTANCE_CREATOR_DIALOG_H

#include "rectangleinstance.h"

#include <QDialog>
#include <QObject>
#include <QSpinBox>

#define MAX_LENGTH 1000

class Instance_creator_dialog : public QDialog
{
    Q_OBJECT
public:
    Instance_creator_dialog(QWidget *parent = nullptr);
    ~Instance_creator_dialog(){if(recInstance != nullptr) delete recInstance;}

    void create_instance();
    RectangleInstance *getInstance();

signals:
    void newInstance(RectangleInstance *instance);

private:
    QSpinBox *amount_box;
    QSpinBox *length_box;
    QSpinBox *width_min_box;
    QSpinBox *width_max_box;
    QSpinBox *height_min_box;
    QSpinBox *height_max_box;

    RectangleInstance *recInstance = nullptr;
};

#endif // INSTANCE_CREATOR_DIALOG_H
