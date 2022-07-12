#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
#include "database.h"
#include "addnewmaterial.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_newProject();
    void on_openProject();
    void on_saveProject();
    void on_Quit();
    void on_addMaterial();
    void AddNewMaterialDB(const QString& type, const QString& name, const QString& expense);
    void AddNewSupplierDB(std::vector<QString>&);
    void on_addSupplier();
    void on_materialTable();
    void on_supplierTable();
    void on_tabCloseRequested(int index);

private:
    Ui::MainWindow  *ui;
    DataBase        *_db;

    void CreateFileMenu();
    void CreateEditMenu();
    void CreateTableMenu();
};
#endif // MAINWINDOW_H
