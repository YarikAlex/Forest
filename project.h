#ifndef PROJECT_H
#define PROJECT_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QStringList>
#include "database.h"

class Project : public QWidget
{
    Q_OBJECT
public:
    Project(DataBase *dataBase, QWidget *parent = nullptr);
private:
    QWidget *_window;
    QHBoxLayout *_mainLayout;
    QVBoxLayout *_leftLayout;
    QVBoxLayout *_rightLayout;
    DataBase *_dataBase;

    QComboBox *_typeBox, *_materialBox;
    QLineEdit *_numberLine, *_costLine, *_coeffLine, *_primeCostLine, *_totalCostLine;
    QLabel *_typeLabel, *_materialLabel, *_numberLabel, *_costLabel;
    QLabel *_coefficientLabel, *_primeCostLabel, *_totalCostLabel;
    QPushButton *_addNewMaterial;

    QHBoxLayout* createTitleLine(QWidget *parent);
    QHBoxLayout* createMaterialsLine(QWidget *parent);
    QVBoxLayout* createResultBox(QWidget *parent);
    QStringList chooseMaterials(const QString &type);

private slots:
    void typeBox_currentTextChanged(const QString text);

signals:

};

#endif // PROJECT_H
