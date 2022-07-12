#include "addnewmaterial.h"
#include "ui_addnewmaterial.h"

addNewMaterial::addNewMaterial(DataBase *dataBase,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addNewMaterial)
{
    ui->setupUi(this);
    ui->ui_typeMaterial->addItems(dataBase->GetType());
}

addNewMaterial::~addNewMaterial()
{
    delete ui;
}

void addNewMaterial::on_addButton_clicked()
{
    emit getNewMaterial(ui->ui_typeMaterial->currentIndex() + 1, ui->ui_materialName->text(), ui->ui_expenseMaterial->text());
    this->close();
}

void addNewMaterial::on_cancelButton_clicked()
{
    this->close();
}
