#ifndef TABLEWINDOW_H
#define TABLEWINDOW_H

#include <QDialog>
#include <QSqlRelationalTableModel>
#include <QSqlRelation>
#include "database.h"

#include <vector>

namespace Ui {
class tableWindow;
}

class tableWindow : public QDialog
{
    Q_OBJECT

public:
    explicit tableWindow(const QString &tableName, const std::vector<QString> &headers, QWidget *parent = nullptr);
    explicit tableWindow(DataBase *db);
    ~tableWindow();

private slots:
    void on_btnOkClicked();

private:
    Ui::tableWindow *ui;
    QSqlRelationalTableModel *_model;
};

#endif // TABLEWINDOW_H
