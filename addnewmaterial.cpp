#include "addnewmaterial.h"
#include "ui_addnewmaterial.h"

addNewMaterial::addNewMaterial(DataBase *dataBase,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addNewMaterial)
{
    ui->setupUi(this);
    ui->ui_typeMaterial->addItems(dataBase->getType());
}

addNewMaterial::~addNewMaterial()
{
    delete ui;
}

void addNewMaterial::on_addButton_clicked()
{
    emit getNewMaterial(ui->ui_typeMaterial->currentText(), ui->ui_materialName->text(), ui->ui_expenseMaterial->text());
    this->close();
}
