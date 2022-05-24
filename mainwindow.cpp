#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "project.h"
#include "supplier.h"
#include "addnewmaterial.h"
#include <QMenu>
#include <QSpacerItem>
#include <QToolBar>
#include <QAction>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    createFileMenu();
    createEditMenu();
    createTableMenu();

    _db = new DataBase();
    _db->connectDataBase();

    connect(ui->btn_newProject, &QPushButton::clicked, this, &MainWindow::on_newProject);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_newProject()
{
    Project *project = new Project(_db, this);
    ui->tabWidget->addTab(project, tr("New project"));
    ui->tabWidget->setCurrentIndex(ui->tabWidget->count()-1);
}

void MainWindow::on_Quit()
{
    this->close();
}

void MainWindow::on_addMaterial()
{
    addNewMaterial *window = new addNewMaterial(_db, this);
    window->show();
    connect(window, &addNewMaterial::getNewMaterial, this, &MainWindow::addNewMaterialDB);
}

void MainWindow::on_addSupplier()
{
    Supplier *supplierForm = new Supplier(this);
    supplierForm->show();
    connect(supplierForm, &Supplier::getSupplier, this, &MainWindow::addNewSupplierDB);
}

void MainWindow::on_materialTable()
{

}

void MainWindow::on_supplierTable()
{

}

void MainWindow::addNewMaterialDB(const QString& type, const QString& name, const QString& expense)
{
    _db->insertMaterialData(type, name, expense);
}

void MainWindow::addNewSupplierDB(std::vector<QString> &supplier)
{
    _db->insertSupplierData(supplier);
}

void MainWindow::createFileMenu()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    QToolBar *fileTool = new QToolBar(tr("File"), this);

    QAction *newFileAction = new QAction(tr("&New"), this);
    newFileAction->setShortcut(QKeySequence::New);
    newFileAction->setStatusTip(tr("Create new file"));
    connect(newFileAction, &QAction::triggered, this, &MainWindow::on_newProject);
    fileMenu->addAction(newFileAction);
    fileMenu->addSeparator();
    fileTool->addAction(newFileAction);

    QAction *openFileAction = new QAction (tr("&Open"), this);
    openFileAction->setShortcut(QKeySequence::Open);
    openFileAction->setStatusTip(tr("Open existing file"));
    fileMenu->addAction(openFileAction);
    fileTool->addAction(openFileAction);

    QAction *saveFileAction = new QAction(tr("&Save"), this);
    saveFileAction->setShortcut(QKeySequence::Save);
    saveFileAction->setStatusTip(tr("Save the project to disk"));
    fileMenu->addAction(saveFileAction);
    fileMenu->addSeparator();
    fileTool->addAction(saveFileAction);

    QAction *quitFileAction = new QAction(tr("&Quit"), this);
    quitFileAction->setShortcut(QKeySequence::Quit);
    connect(quitFileAction, &QAction::triggered, this, &MainWindow::on_Quit);
    fileMenu->addAction(quitFileAction);

    this->addToolBar(fileTool);
}

void MainWindow::createEditMenu()
{
    QMenu *editMenu = menuBar()->addMenu(tr("&Edit"));
    QToolBar *editTool = new QToolBar(tr("Edit"), this);

    const QIcon newMaterialIcon = QIcon::fromTheme("databaseTheme", QIcon(":/images/newMaterialIcon.png"));
    QAction *addMaterialAction = new QAction(newMaterialIcon, tr("New material"), this);
    addMaterialAction->setStatusTip(tr("Add new material in database"));
    connect(addMaterialAction, &QAction::triggered, this, &MainWindow::on_addMaterial);
    editMenu->addAction(addMaterialAction);
    editTool->addAction(addMaterialAction);

    const QIcon newSupplierIcon = QIcon::fromTheme("databaseTheme", QIcon(":/images/newSupplierIcon.png"));
    QAction *addSupplierAction = new QAction(newSupplierIcon, tr("New supplier"), this);
    addSupplierAction->setStatusTip(tr("Add new supplier in database"));
    connect(addSupplierAction, &QAction::triggered, this, &MainWindow::on_addSupplier);
    editMenu->addAction(addSupplierAction);
    editTool->addAction(addSupplierAction);

    this->addToolBar(editTool);
}

void MainWindow::createTableMenu()
{
    QMenu *tablesMenu = menuBar()->addMenu(tr("&Tables"));

    QAction *materialTable = new QAction(tr("List of materials"));
    materialTable->setStatusTip(tr("Show all materials"));
    connect(materialTable, &QAction::triggered, this, &MainWindow::on_materialTable);
    tablesMenu->addAction(materialTable);

    QAction *supplierTable = new QAction(tr("List of suppliers"));
    supplierTable->setStatusTip(tr("Show all suppliers"));
    connect(supplierTable, &QAction::triggered, this, &MainWindow::on_supplierTable);
    tablesMenu->addAction(supplierTable);
}
