#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "project.h"
#include "supplier.h"
#include "addnewmaterial.h"
#include "tablewindow.h"
#include <QMenu>
#include <QSpacerItem>
#include <QToolBar>
#include <QAction>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    CreateFileMenu();
    CreateEditMenu();
    CreateTableMenu();

    _db = new DataBase();
    _db->connectDataBase();

    connect(ui->btn_newProject, &QPushButton::clicked, this, &MainWindow::on_newProject);
    connect(ui->tabWidget, &QTabWidget::tabCloseRequested, this, &MainWindow::on_tabCloseRequested);
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

void MainWindow::on_openProject()
{

}

void MainWindow::on_saveProject()
{

}

void MainWindow::on_Quit()
{
    QMessageBox saveRequestBox;
    saveRequestBox.setText(tr("Do you want to save your projects?"));
    saveRequestBox.setStandardButtons(QMessageBox::StandardButton::Save | QMessageBox::StandardButton::Discard | QMessageBox::StandardButton::Cancel);
    saveRequestBox.setDefaultButton(QMessageBox::Save);
    int req = saveRequestBox.exec();
    switch(req)
    {
        case QMessageBox::StandardButton::Save:
            this->statusBar()->showMessage(tr("Project saved"));
        break;
        case QMessageBox::StandardButton::Cancel:
            this->statusBar()->showMessage(tr("The save has been cancelled"));
        break;
        case QMessageBox::StandardButton::Discard:
            this->close();
        break;
        default:
            qDebug()<< "Ups";
        break;
    }
}

void MainWindow::on_addMaterial()
{
    addNewMaterial *window = new addNewMaterial(_db, this);
    window->show();
    connect(window, &addNewMaterial::getNewMaterial, this, &MainWindow::AddNewMaterialDB);
}

void MainWindow::on_addSupplier()
{
    Supplier *supplierForm = new Supplier(this);
    supplierForm->show();
    connect(supplierForm, &Supplier::getSupplier, this, &MainWindow::AddNewSupplierDB);
}

void MainWindow::on_materialTable()
{
    tableWindow *newTable = new tableWindow("materials", materialTableHeaders, this);
    newTable->show();
}

void MainWindow::on_supplierTable()
{
    tableWindow *newTable = new tableWindow("suppliers", supplierTableHeaders, this);
    newTable->show();
}

void MainWindow::on_orderTable()
{

}

void MainWindow::AddNewMaterialDB(const QString& type, const QString& name, const QString& expense)
{
    _db->insertMaterialData(type, name, expense);
}

void MainWindow::AddNewSupplierDB(std::vector<QString> &supplier)
{
    _db->insertSupplierData(supplier);
}

void MainWindow::on_tabCloseRequested(int index)
{
    ui->tabWidget->removeTab(index);
}

void MainWindow::CreateFileMenu()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    QToolBar *fileTool = new QToolBar(tr("File"), this);

    const QIcon newFileIcon = QIcon::fromTheme("projectTheme", QIcon(":/images/newProjectIcon.png"));
    QAction *newFileAction = new QAction(newFileIcon, tr("&New"), this);
    newFileAction->setShortcut(QKeySequence::New);
    newFileAction->setStatusTip(tr("Create new project"));
    connect(newFileAction, &QAction::triggered, this, &MainWindow::on_newProject);
    fileMenu->addAction(newFileAction);
    fileMenu->addSeparator();
    fileTool->addAction(newFileAction);

    const QIcon openFileIcon = QIcon::fromTheme("projectTheme", QIcon(":/images/openProjectIcon.png"));
    QAction *openFileAction = new QAction (openFileIcon, tr("&Open"), this);
    openFileAction->setShortcut(QKeySequence::Open);
    openFileAction->setStatusTip(tr("Open existing project"));
    connect(openFileAction, &QAction::triggered, this, &MainWindow::on_openProject);
    fileMenu->addAction(openFileAction);
    fileTool->addAction(openFileAction);

    const QIcon saveFileIcon = QIcon::fromTheme("projectTheme", QIcon(":/images/saveProjectIcon.png"));
    QAction *saveFileAction = new QAction(saveFileIcon, tr("&Save"), this);
    saveFileAction->setShortcut(QKeySequence::Save);
    saveFileAction->setStatusTip(tr("Save the project to disk"));
    connect(saveFileAction, &QAction::triggered, this, &MainWindow::on_saveProject);
    fileMenu->addAction(saveFileAction);
    fileMenu->addSeparator();
    fileTool->addAction(saveFileAction);

    QAction *quitFileAction = new QAction(tr("&Quit"), this);
    quitFileAction->setShortcut(QKeySequence::Quit);
    connect(quitFileAction, &QAction::triggered, this, &MainWindow::on_Quit);
    fileMenu->addAction(quitFileAction);

    this->addToolBar(fileTool);
}

void MainWindow::CreateEditMenu()
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

void MainWindow::CreateTableMenu()
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

    QAction *orderTable = new QAction(tr("List of orders"));
    orderTable->setStatusTip(tr("Show all orders"));
    connect(orderTable, &QAction::triggered, this, &MainWindow::on_orderTable);
    tablesMenu->addAction(orderTable);
}
