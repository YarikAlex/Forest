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
#include <QRect>
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

    QComboBox *_typeBox, *_materialBox;
    QLineEdit *_areaLine, *_priceLine, *_costLine, *_indexLine, *_primeCostLine, *_totalCostLine;
    QLabel *_typeLabel, *_materialLabel, *_areaLabel,*_priceLable, *_costLabel;
    QLabel *_indexLabel, *_primeCostLabel, *_totalCostLabel;
    QPushButton *_addNewMaterial;
    QChar _dot = '.';
    QChar _comma = ',';

    void createTitleLine();
    void createMaterialsLine();
    void createResultLine();
    void createClientLine();
    QStringList chooseMaterials(const QString &type);
    QString& checkDot(QString& text);

    //размеры элементов
    const ushort _shift = 5;
    const ushort _addinfLableHeight = 25;
    const ushort _spacerWidth = 10;
    QPoint _leftPosition{10, 5};
    QPoint _rightPosition{600, 5};
    QSize _comboboxSize{150, 25};
    QSize _lineEditSize{60, 25};
    QSize _addButtonSize{30, 25};
    QSize _areaSize{550, 400};

private slots:
    void typeBoxCurrentTextChanged(const QString& text);
    void onBtnAddMaterials();
    void indexLineTextChanged(const QString &);
    void onDeleteButton();

signals:

};

#endif // PROJECT_H
