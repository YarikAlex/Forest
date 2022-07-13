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
    void on_pushButton_3_clicked();
    void on_newProject_triggered();
    void on_addNewMaterialDB_clicked();
    void addNewMaterialDB(uint type, const QString& name, const QString& expense);
    void addNewSupplierDB(std::vector<QString>&);
    void on_btn_addSupplier_clicked();

private:
    Ui::MainWindow  *ui;
    DataBase        *_db;
};
#endif // MAINWINDOW_H
