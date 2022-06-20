#include "project.h"
#include <QSqlQuery>
#include <QDebug>


Project::Project(DataBase* dataBase, QWidget *parent)
    : QWidget{parent}, _dataBase(dataBase)
{
    createTitleLine();
    createMaterialsLine();
    createResultLine();

    _area = new QScrollArea(this);
    _area->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    _area->setWidgetResizable(true);
    leftPosition.setX(_typeBox->x());
    leftPosition.setY(_typeBox->geometry().height()+_typeLabel->geometry().height()+2*shift);
    _area->setGeometry(QRect{leftPosition, areaSize});
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
    _typeLabel = new QLabel(this);
    _typeLabel->setGeometry(QRect{leftPosition, comboboxSize});
    _typeLabel->setText(tr("Type"));
    _typeLabel->setAlignment(Qt::AlignHCenter);
    leftPosition.setX(leftPosition.x() + _typeLabel->geometry().width() + shift);

    _materialLabel = new QLabel(this);
    _materialLabel->setGeometry(QRect{leftPosition, comboboxSize});
    _materialLabel->setText(tr("Material"));
    _materialLabel->setAlignment(Qt::AlignHCenter);
    leftPosition.setX(leftPosition.x() + _materialLabel->geometry().width() + shift);

    _areaLabel = new QLabel(this);
    _areaLabel->setGeometry(QRect{leftPosition, lineEditSize});
    _areaLabel->setText(tr("Number"));
    _areaLabel->setAlignment(Qt::AlignHCenter);
    leftPosition.setX(leftPosition.x() + _areaLabel->geometry().width() + shift);

    _priceLable = new QLabel(this);
    _priceLable->setGeometry(QRect{leftPosition, lineEditSize});
    _priceLable->setText(tr("Price"));
    _priceLable->setAlignment(Qt::AlignHCenter);
}

void Project::createMaterialsLine()
{
    leftPosition.setX(_typeLabel->x());
    leftPosition.setY(_typeLabel->geometry().height() + shift);
    _typeBox = new QComboBox(this);
    _typeBox->setGeometry(QRect{leftPosition, comboboxSize});
    _typeBox->addItems(_dataBase->getType());
    _typeBox->setPlaceholderText(tr("Type"));

    leftPosition.setX(_materialLabel->x());
    leftPosition.setY(_materialLabel->geometry().height() + shift);
    _materialBox = new QComboBox(this);
    _materialBox->setGeometry(QRect{leftPosition, comboboxSize});
    _materialBox->addItems(chooseMaterials(_typeBox->currentText()));
    _materialBox->setPlaceholderText(tr("Material"));

    leftPosition.setX(_areaLabel->x());
    leftPosition.setY(_areaLabel->geometry().height()+shift);
    _areaLine = new QLineEdit(this);
    _areaLine->setGeometry(QRect{leftPosition, lineEditSize});
    _areaLine->setAlignment(Qt::AlignHCenter);
    _areaLine->setPlaceholderText(tr("Number"));

    leftPosition.setX(_priceLable->x());
    leftPosition.setY(_priceLable->geometry().height()+shift);
    _priceLine = new QLineEdit(this);
    _priceLine->setGeometry(QRect{leftPosition, lineEditSize});
    _priceLine->setAlignment(Qt::AlignHCenter);
    _priceLine->setPlaceholderText(tr("Price"));

    leftPosition.setX(leftPosition.x() + _priceLine->geometry().width() + shift);
    leftPosition.setY(_priceLine->y());
    _addNewMaterial = new QPushButton(this);
    _addNewMaterial->setGeometry(QRect{leftPosition, addButtonSize});
    _addNewMaterial->setText("+");
}

void Project::createResultLine()
{
    _indexLabel = new QLabel(this);
    _indexLabel->setGeometry(QRect{rightPosition, lineEditSize});
    _indexLabel->setText(tr("Index"));
    _indexLabel->setAlignment(Qt::AlignHCenter);

    rightPosition.setX(rightPosition.x()+_indexLabel->geometry().width()+shift);
    _primeCostLabel = new QLabel(this);
    _primeCostLabel->setGeometry(QRect{rightPosition, lineEditSize});
    _primeCostLabel->setText(tr("Prime cost"));
    _primeCostLabel->setAlignment(Qt::AlignHCenter);

    rightPosition.setX(rightPosition.x()+_primeCostLabel->geometry().width()+shift);
    _totalCostLabel = new QLabel(this);
    _totalCostLabel->setGeometry(QRect{rightPosition, lineEditSize});
    _totalCostLabel->setText(tr("Total cost"));
    _totalCostLabel->setAlignment(Qt::AlignHCenter);

    rightPosition.setX(_indexLabel->x());
    rightPosition.setY(_indexLabel->geometry().height()+shift);
    _indexLine = new QLineEdit(this);
    _indexLine->setGeometry(QRect{rightPosition, lineEditSize});
    _indexLine->setAlignment(Qt::AlignHCenter);
    _indexLine->setPlaceholderText(tr("Index"));

    rightPosition.setX(_primeCostLabel->x());
    rightPosition.setY(_primeCostLabel->geometry().height()+shift);
    _primeCostLine = new QLineEdit(this);
    _primeCostLine->setGeometry(QRect{rightPosition, lineEditSize});
    _primeCostLine->setReadOnly(true);
    _primeCostLine->setText(QString::number(_calculator.GetPrimeCost()));
    _primeCostLine->setAlignment(Qt::AlignHCenter);

    rightPosition.setX(_totalCostLabel->x());
    rightPosition.setY(_totalCostLabel->geometry().height()+shift);
    _totalCostLine = new QLineEdit(this);
    _totalCostLine->setGeometry(QRect{rightPosition, lineEditSize});
    _totalCostLine->setReadOnly(true);
    _totalCostLine->setText(QString::number(_calculator.GetTotalCost(_indexLine->text().toDouble())));
    _totalCostLine->setAlignment(Qt::AlignHCenter);

    connect(_indexLine, &QLineEdit::textChanged, this, &Project::indexLineTextChanged);
}

QStringList Project::chooseMaterials(const QString &type)
{
    return _dataBase->chooseMaterials(type);
}

QString& Project::checkDot(QString &text)
{
    text.replace(_comma, _dot);
    return text;
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
    QString areaText = _areaLine->text();
    QString priceText = _priceLine->text();
    QString indexText = _indexLine->text();

    QHBoxLayout *innerLayout = new QHBoxLayout();
    innerLayout->setAlignment(Qt::AlignLeft);

    QLabel *count = new QLabel(QString ("%1.").arg(_layoutWidget->count()));
    innerLayout->addWidget(count);

    QLabel *type = new QLabel(_typeBox->currentText());
    type->setFixedHeight(addinfLableHeight);
    innerLayout->addWidget(type);

    QLabel *material = new QLabel(_materialBox->currentText());
    innerLayout->addWidget(material);

    QLabel *number = new QLabel(checkDot(areaText) + tr(" м2"));
    innerLayout->addWidget(number);

    QLabel *weight = new QLabel(QString::number(_calculator.CalcMaterialWeight(checkDot(areaText).toDouble(), expence)) + " кг");
    innerLayout->addWidget(weight);

    QLabel *price = new QLabel(checkDot(priceText) + tr(" руб."));
    innerLayout->addWidget(price);

    QLabel *cost = new QLabel(QString::number(_calculator.CalcMaterialCost(checkDot(areaText).toDouble(), expence, checkDot(priceText).toDouble())) + " руб.");
    innerLayout->addWidget(cost);
    _primeCostLine->setText(QString::number(_calculator.GetPrimeCost()));
    _totalCostLine->setText(QString::number(_calculator.GetTotalCost(checkDot(indexText).toDouble())));

    QPushButton *btnDelete = new QPushButton("-");
    btnDelete->setFixedWidth(addinfLableHeight);
    innerLayout->addWidget(btnDelete);

    _layoutWidget->insertLayout(_layoutWidget->count()-1, innerLayout);
    _spacer->changeSize(spacerWidth, _spacer->geometry().height() - type->geometry().height());
}

void Project::indexLineTextChanged(const QString& newKoeff)
{
    _totalCostLine->setText(QString::number(_calculator.GetTotalCost(newKoeff.toDouble())));
}

