#include "tablewindow.h"
#include "ui_tablewindow.h"

tableWindow::tableWindow(const QString &tableName, const std::vector<QString> &headers, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::tableWindow)
{
    ui->setupUi(this);
    _model = new QSqlRelationalTableModel(this);
    _model->setTable(tableName);
    if(tableName == "materials")
        _model->setRelation(1, QSqlRelation("materialTypes", "type_id", "type_name"));

    for(int header = 0; header < _model->columnCount(); ++header)
    {
        _model->setHeaderData(header, Qt::Horizontal, headers[header]);
    }
    _model->select();

    ui->tableView->setModel(_model);
    ui->tableView->hideColumn(0);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->horizontalHeader()->setStretchLastSection(true);

    connect(ui->btnOk, &QPushButton::clicked, this, &tableWindow::on_btnOkClicked);
}

tableWindow::tableWindow(DataBase *db)
{
   // ui->tableView->setModel(db.GetOrders());
}

tableWindow::~tableWindow()
{
    delete ui;
}

void tableWindow::on_btnOkClicked()
{
    this->close();
}

