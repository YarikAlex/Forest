#include "project.h"
#include <QSqlQuery>
#include <QDebug>


Project::Project(DataBase* dataBase, QWidget *parent)
    : QWidget{parent}, _dataBase(dataBase)
{
    createTitleLine();
    createMaterialsLine();

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


    //_rightLayout = new QVBoxLayout(this);
    //_rightLayout->addLayout(createResultBox(this));
    //_mainLayout->addLayout(_leftLayout);
    //_mainLayout->addSpacing(50);
    //_mainLayout->addLayout(_rightLayout);

    connect(_typeBox, &QComboBox::currentTextChanged, this, &Project::typeBoxCurrentTextChanged);
    connect(_addNewMaterial, &QPushButton::clicked, this, &Project::onBtnAddMaterials);
}

void Project::createTitleLine()
{
    uint count = 0;
    const ushort shift = 5;
    _typeLabel = new QLabel(this);
    _typeLabel->setGeometry(10, 5, 130, 25);
    _typeLabel->setText(tr("Тип"));
    count = count + _typeLabel->x() + _typeLabel->geometry().width()+shift;

    _materialLabel = new QLabel(this);
    _materialLabel->setGeometry(count, 5, 100, 25);
    _materialLabel->setText(tr("Материал"));
    count = count + _materialLabel->geometry().width()+shift;

    _areaLabel = new QLabel(this);
    _areaLabel->setGeometry(count, 5, 80, 25);
    _areaLabel->setText(tr("Площадь"));
    count = count + _areaLabel->geometry().width()+shift;

    _priceLable = new QLabel(this);
    _priceLable->setGeometry(count, 5, 80, 25);
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

QVBoxLayout *Project::createResultBox(QWidget *parent)
{
    QVBoxLayout *lineLayout = new QVBoxLayout(parent);

    _coefficientLabel = new QLabel(this);
    _primeCostLabel = new QLabel(this);
    _totalCostLabel = new QLabel(this);
    _coeffLine = new QLineEdit(this);
    _primeCostLine = new QLineEdit(this);
    _totalCostLine = new QLineEdit(this);

    _coefficientLabel->setText(tr("Коэфф"));
    _coefficientLabel->setFixedSize(50, 25);
    _primeCostLabel->setText(tr("Себестоимость"));
    _primeCostLabel->setFixedSize(100, 25);
    _totalCostLabel->setText(tr("Стоимость"));
    _totalCostLabel->setFixedSize(100, 25);
    _coeffLine->setFixedSize(50, 25);
    _primeCostLine->setFixedSize(100, 25);
    _primeCostLine->setReadOnly(true);
    _totalCostLine->setFixedSize(100, 25);
    _totalCostLine->setReadOnly(true);

    lineLayout->addWidget(_coefficientLabel);
    lineLayout->addWidget(_coeffLine);
    lineLayout->addWidget(_primeCostLabel);
    lineLayout->addWidget(_primeCostLine);
    lineLayout->addWidget(_totalCostLabel);
    lineLayout->addWidget(_totalCostLine);

    return lineLayout;
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

    QLabel *weight = new QLabel(QString::number(_areaLine->text().toDouble() * expence) + " кг");
    innerLayout->addWidget(weight);

    QLabel *price = new QLabel(_priceLine->text() + " руб.");
    innerLayout->addWidget(price);

    QLabel *cost = new QLabel(QString::number((_areaLine->text().toDouble() * expence) * _priceLine->text().toDouble()) + " руб.");
    innerLayout->addWidget(cost);

    QPushButton *btnDelete = new QPushButton("-");
    btnDelete->setFixedWidth(30);
    innerLayout->addWidget(btnDelete);

    _layoutWidget->insertLayout(_layoutWidget->count()-1, innerLayout);
    _spacer->changeSize(10, _spacer->geometry().height() - type->geometry().height());
}

