#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "project.h"
#include "addnewmaterial.h"
#include <QMenuBar>
#include <QSpacerItem>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _db = new DataBase();
    _db->connectDataBase();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_3_clicked()
{
    Project *project = new Project(_db, this);
    ui->tabWidget->addTab(project, tr("Новый проект"));
    ui->tabWidget->setCurrentIndex(ui->tabWidget->count()-1);

}

void MainWindow::on_newProject_triggered()
{
    on_pushButton_3_clicked();
}

void MainWindow::on_addNewMaterialDB_clicked()
{
    addNewMaterial *window = new addNewMaterial(_db, this);
    window->show();
    connect(window, &addNewMaterial::getNewMaterial, this, &MainWindow::addNewMaterialDB);
}

void MainWindow::addNewMaterialDB(const QString& type, const QString& name, const QString& expense)
{
    _db->insertData(type, name, expense);
}
