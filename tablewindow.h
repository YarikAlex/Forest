#ifndef TABLEWINDOW_H
#define TABLEWINDOW_H

#include <QDialog>
#include "database.h"

namespace Ui {
class tableWindow;
}

class tableWindow : public QDialog
{
    Q_OBJECT

public:
    explicit tableWindow(DataBase *database, QWidget *parent = nullptr);
    ~tableWindow();

private:
    Ui::tableWindow *ui;
};

#endif // TABLEWINDOW_H
