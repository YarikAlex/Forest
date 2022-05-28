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
#include <QSpacerItem>
#include <QScrollArea>
#include <QWidget>
#include "database.h"
#include "calculator.h"

class Project : public QWidget
{
    Q_OBJECT
public:
    Project(DataBase *dataBase, QWidget *parent = nullptr);
private:
    QVBoxLayout *_layoutWidget;
    DataBase *_dataBase;
    Calculator _calculator;
    QSpacerItem *_spacer;
    QScrollArea *_area;
    QWidget *_wdg;
    int _areaWidth = 0;

    QComboBox *_typeBox, *_materialBox;
    QLineEdit *_areaLine, *_priceLine, *_costLine, *_koeffLine, *_primeCostLine, *_totalCostLine;
    QLabel *_typeLabel, *_materialLabel, *_areaLabel,*_priceLable, *_costLabel;
    QLabel *_koeffLabel, *_primeCostLabel, *_totalCostLabel;
    QPushButton *_addNewMaterial;

    void createTitleLine();
    void createMaterialsLine();
    void createResultBox();
    QStringList chooseMaterials(const QString &type);

private slots:
    void typeBoxCurrentTextChanged(const QString& text);
    void onBtnAddMaterials();
    void koeffLineTextChanged(const QString &);

signals:

};

#endif // PROJECT_H
