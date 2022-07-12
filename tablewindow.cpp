#include "tablewindow.h"
#include "ui_tablewindow.h"
#include <QStandardItemModel>

tableWindow::tableWindow(DataBase *database, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::tableWindow)
{
    ui->setupUi(this);
    QStandardItemModel *model = new QStandardItemModel(this);

    ui->tableView->setModel(model);
}

tableWindow::~tableWindow()
{
    delete ui;
}
