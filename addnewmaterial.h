#ifndef ADDNEWMATERIAL_H
#define ADDNEWMATERIAL_H

#include <QDialog>
#include "database.h"

namespace Ui {
class addNewMaterial;
}

class addNewMaterial : public QDialog
{
    Q_OBJECT

public:
    explicit addNewMaterial(DataBase *dataBase, QWidget *parent = nullptr);
    ~addNewMaterial();

signals:
    void getNewMaterial(QString type, QString name, QString expenses);

private slots:
    void on_addButton_clicked();

private:
    Ui::addNewMaterial *ui;

};

#endif // ADDNEWMATERIAL_H
