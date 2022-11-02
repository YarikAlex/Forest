#include "supplier.h"
#include "ui_supplier.h"


Supplier::Supplier(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Supplier)
{
    ui->setupUi(this);
}

Supplier::~Supplier()
{
    delete ui;
}

void Supplier::on_btn_cancel_clicked()
{
    this->close();
}

void Supplier::on_btn_add_clicked()
{
    //surname, name, phone, city, street, house, site
    std::vector<QString> supplier;
    supplier.push_back(ui->edit_surname->text());
    supplier.push_back(ui->edit_name->text());
    supplier.push_back(ui->edit_phone->text());
    supplier.push_back(ui->edit_city->text());
    supplier.push_back(ui->edit_street->text());
    supplier.push_back(ui->edit_house->text());
    supplier.push_back(ui->edit_site->text());
    emit getSupplier(supplier);
    this->close();
}

