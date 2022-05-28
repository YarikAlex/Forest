#include "project.h"
#include <QSqlQuery>
#include <QDebug>


Project::Project(DataBase* dataBase, QWidget *parent)
    : QWidget{parent}, _dataBase(dataBase)
{
    createTitleLine();
    createMaterialsLine();
    createResultBox();

    _area = new QScrollArea(this);
    _area->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    _area->setWidgetResizable(true);
    _area->setGeometry(_typeBox->x(), _typeBox->geometry().height()+_typeLabel->geometry().height()+10, _areaWidth, 400);
    _area->setBackgroundRole(QPalette::Light);

    _wdg = new QWidget();
    _area->setWidget(_wdg);

    _layoutWidget = new QVBoxLayout();
    _spacer = new QSpacerItem(10, _area->geometry().height()-100);
    _spacer->expandingDirections();
    _layoutWidget->addSpacerItem(_spacer);
    _wdg->setLayout(_layoutWidget);

    connect(_typeBox, &QComboBox::currentTextChanged, this, &Project::typeBoxCurrentTextChanged);
    connect(_addNewMaterial, &QPushButton::clicked, this, &Project::onBtnAddMaterials);
}

void Project::createTitleLine()
{
    uint position = 0;
    const ushort shift = 5;
    _typeLabel = new QLabel(this);
    _typeLabel->setGeometry(10, 5, 150, 25);
    _typeLabel->setText(tr("Тип"));
    position = position + _typeLabel->x() + _typeLabel->geometry().width()+shift;

    _materialLabel = new QLabel(this);
    _materialLabel->setGeometry(position, 5, 150, 25);
    _materialLabel->setText(tr("Материал"));
    position = position + _materialLabel->geometry().width()+shift;

    _areaLabel = new QLabel(this);
    _areaLabel->setGeometry(position, 5, 80, 25);
    _areaLabel->setText(tr("Площадь"));
    position = position + _areaLabel->geometry().width()+shift;

    _priceLable = new QLabel(this);
    _priceLable->setGeometry(position, 5, 80, 25);
    _priceLable->setText(tr("Цена"));
}

void Project::createMaterialsLine()
{
    ushort shift = 5;
    _typeBox = new QComboBox(this);
    _typeBox->setGeometry(_typeLabel->x(), _typeLabel->geometry().height() + shift,
                          _typeLabel->geometry().width(), _typeLabel->geometry().height());
    _typeBox->addItems(_dataBase->getType());

    _materialBox = new QComboBox(this);
    _materialBox->setGeometry(_materialLabel->x(), _materialLabel->geometry().height() + shift,
                              _materialLabel->geometry().width(), _materialLabel->geometry().height());
    _materialBox->addItems(chooseMaterials(_typeBox->currentText()));

    _areaLine = new QLineEdit(this);
    _areaLine->setGeometry(_areaLabel->x(), _areaLabel->geometry().height()+shift,
                           _areaLabel->geometry().width(), _areaLabel->geometry().height());

    _priceLine = new QLineEdit(this);
    _priceLine->setGeometry(_priceLable->x(), _priceLable->geometry().height()+shift,
                            _priceLable->geometry().width(), _priceLable->geometry().height());

    _addNewMaterial = new QPushButton(this);
    _addNewMaterial->setGeometry(_priceLine->x()+_priceLine->geometry().width()+shift, _priceLine->y(), 30, 25);
    _addNewMaterial->setText("+");
    _areaWidth = _addNewMaterial->x() + _addNewMaterial->geometry().width();
}

void Project::createResultBox()
{
     uint position = _priceLable->x()+200;
     ushort shift = 5;

    _koeffLabel = new QLabel(this);
    _koeffLabel->setGeometry(position, _priceLable->y(), 100, 25);
    _koeffLabel->setText(tr("Коэффициент"));
    position += _koeffLabel->geometry().width()+shift;

    _primeCostLabel = new QLabel(this);
    _primeCostLabel->setGeometry(position, _priceLable->y(), 100, 25);
    _primeCostLabel->setText(tr("Себестоимость"));
    position += _primeCostLabel->geometry().width()+shift;

    _totalCostLabel = new QLabel(this);
    _totalCostLabel->setGeometry(position, _priceLable->y(), 110, 25);
    _totalCostLabel->setText(tr("Стоимость проекта"));

    _koeffLine = new QLineEdit(this);
    _koeffLine->setGeometry(_koeffLabel->x(), _koeffLabel->y()+30, 100, 25);

    _primeCostLine = new QLineEdit(this);
    _primeCostLine->setGeometry(_primeCostLabel->x(), _primeCostLabel->y()+30, 100, 25);
    _primeCostLine->setReadOnly(true);
    _primeCostLine->setText(QString::number(_calculator.GetPrimeCost()));

    _totalCostLine = new QLineEdit(this);
    _totalCostLine->setGeometry(_totalCostLabel->x(), _totalCostLabel->y()+30, 110, 25);
    _totalCostLine->setReadOnly(true);
    _totalCostLine->setText(QString::number(_calculator.GetTotalCost(_koeffLine->text().toDouble())));

    connect(_koeffLine, &QLineEdit::textChanged, this, &Project::koeffLineTextChanged);
}

QStringList Project::chooseMaterials(const QString &type)
{
    return _dataBase->chooseMaterials(type);
}

//slots
void Project::typeBoxCurrentTextChanged(const QString &text)
{
    _materialBox->clear();
    _materialBox->addItems(chooseMaterials(text));
}

void Project::onBtnAddMaterials()
{
    //Запрос в БД на получение расхода
    double expence = _dataBase->getExpense(_typeBox->currentText(), _materialBox->currentText());

    QHBoxLayout *innerLayout = new QHBoxLayout();
    innerLayout->setAlignment(Qt::AlignLeft);

    QLabel *count = new QLabel(QString ("%1.").arg(_layoutWidget->count()));
    innerLayout->addWidget(count);

    QLabel *type = new QLabel(_typeBox->currentText());
    type->setFixedHeight(25);
    innerLayout->addWidget(type);

    QLabel *material = new QLabel(_materialBox->currentText());
    innerLayout->addWidget(material);

    QLabel *number = new QLabel(_areaLine->text() + " м2");
    innerLayout->addWidget(number);

    QLabel *weight = new QLabel(QString::number(_calculator.CalcMaterialWeight(_areaLine->text().toDouble(), expence)) + " кг");
    innerLayout->addWidget(weight);

    QLabel *price = new QLabel(_priceLine->text() + " руб.");
    innerLayout->addWidget(price);

    QLabel *cost = new QLabel(QString::number(_calculator.CalcMaterialCost(_areaLine->text().toDouble(), expence, _priceLine->text().toDouble())) + " руб.");
    innerLayout->addWidget(cost);
    _primeCostLine->setText(QString::number(_calculator.GetPrimeCost()));
    _totalCostLine->setText(QString::number(_calculator.GetTotalCost(_koeffLine->text().toDouble())));

    QPushButton *btnDelete = new QPushButton("-");
    btnDelete->setFixedWidth(30);
    innerLayout->addWidget(btnDelete);

    _layoutWidget->insertLayout(_layoutWidget->count()-1, innerLayout);
    _spacer->changeSize(10, _spacer->geometry().height() - type->geometry().height());
}

void Project::koeffLineTextChanged(const QString& newKoeff)
{
    _totalCostLine->setText(QString::number(_calculator.GetTotalCost(newKoeff.toDouble())));
}

