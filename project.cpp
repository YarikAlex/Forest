#include "project.h"
#include <QSqlQuery>
#include <QDebug>

Project::Project(DataBase* dataBase, QWidget *parent)
    : QWidget{parent}, _dataBase(dataBase)
{
    CreateTitleLine();
    CreateMaterialsLine();
    CreateResultLine();
    CreateClientLine();

    _area = new QScrollArea(this);
    _area->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    _area->setWidgetResizable(true);
    _leftPosition.setX(_typeBox->x());
    _leftPosition.setY(_typeBox->geometry().height()+_typeLabel->geometry().height()+2*_shift);
    _area->setGeometry(QRect{_leftPosition, _areaSize});
    _area->setBackgroundRole(QPalette::Light);

    _wdg = new QWidget();
    _area->setWidget(_wdg);

    _layoutWidget = new QVBoxLayout();
    _spacer = new QSpacerItem(_spacerWidth, _area->geometry().height()-100);
    _spacer->expandingDirections();
    _layoutWidget->addSpacerItem(_spacer);
    _wdg->setLayout(_layoutWidget);


    connect(_typeBox, &QComboBox::currentTextChanged, this, &Project::typeBoxCurrentTextChanged);
    connect(_addNewMaterial, &QPushButton::clicked, this, &Project::onBtnAddMaterials);
    connect(this, &Project::deleteMaterial, this, &Project::onSubtractMaterial);
}

void Project::CreateTitleLine()
{
    _typeLabel = new QLabel(this);
    _typeLabel->setGeometry(QRect{_leftPosition, _comboboxSize});
    _typeLabel->setText(tr("Type"));
    _typeLabel->setAlignment(Qt::AlignHCenter);
    _leftPosition.setX(_leftPosition.x() + _typeLabel->geometry().width() + _shift);

    _materialLabel = new QLabel(this);
    _materialLabel->setGeometry(QRect{_leftPosition, _comboboxSize});
    _materialLabel->setText(tr("Material"));
    _materialLabel->setAlignment(Qt::AlignHCenter);
    _leftPosition.setX(_leftPosition.x() + _materialLabel->geometry().width() + _shift);

    _areaLabel = new QLabel(this);
    _areaLabel->setGeometry(QRect{_leftPosition, _lineEditSize});
    _areaLabel->setText(tr("Number"));
    _areaLabel->setAlignment(Qt::AlignHCenter);
    _leftPosition.setX(_leftPosition.x() + _areaLabel->geometry().width() + _shift);

    _priceLable = new QLabel(this);
    _priceLable->setGeometry(QRect{_leftPosition, _lineEditSize});
    _priceLable->setText(tr("Price"));
    _priceLable->setAlignment(Qt::AlignHCenter);
}

void Project::CreateMaterialsLine()
{
    _leftPosition.setX(_typeLabel->x());
    _leftPosition.setY(_typeLabel->geometry().height() + _shift);
    _typeBox = new QComboBox(this);
    _typeBox->setGeometry(QRect{_leftPosition, _comboboxSize});
    _typeBox->addItems(_dataBase->GetType());
    _typeBox->setPlaceholderText(tr("Type"));

    _leftPosition.setX(_materialLabel->x());
    _leftPosition.setY(_materialLabel->geometry().height() + _shift);
    _materialBox = new QComboBox(this);
    _materialBox->setGeometry(QRect{_leftPosition, _comboboxSize});
    _materialBox->addItems(ChooseMaterials(_typeBox->currentText()));
    _materialBox->setPlaceholderText(tr("Material"));

    _leftPosition.setX(_areaLabel->x());
    _leftPosition.setY(_areaLabel->geometry().height()+_shift);
    _areaLine = new QLineEdit(this);
    _areaLine->setGeometry(QRect{_leftPosition, _lineEditSize});
    _areaLine->setAlignment(Qt::AlignHCenter);
    _areaLine->setPlaceholderText(tr("Number"));

    _leftPosition.setX(_priceLable->x());
    _leftPosition.setY(_priceLable->geometry().height()+_shift);
    _priceLine = new QLineEdit(this);
    _priceLine->setGeometry(QRect{_leftPosition, _lineEditSize});
    _priceLine->setAlignment(Qt::AlignHCenter);
    _priceLine->setPlaceholderText(tr("Price"));

    _leftPosition.setX(_leftPosition.x() + _priceLine->geometry().width() + _shift);
    _leftPosition.setY(_priceLine->y());
    _addNewMaterial = new QPushButton(this);
    _addNewMaterial->setGeometry(QRect{_leftPosition, _addButtonSize});
    _addNewMaterial->setText("+");
}

void Project::CreateResultLine()
{
    _indexLabel = new QLabel(this);
    _indexLabel->setGeometry(QRect{_rightPosition, _lineEditSize});
    _indexLabel->setText(tr("Index"));
    _indexLabel->setAlignment(Qt::AlignHCenter);

    _rightPosition.setX(_rightPosition.x()+_indexLabel->geometry().width()+_shift);
    _primeCostLabel = new QLabel(this);
    _primeCostLabel->setGeometry(QRect{_rightPosition, _lineEditSize});
    _primeCostLabel->setText(tr("Prime cost"));
    _primeCostLabel->setAlignment(Qt::AlignHCenter);

    _rightPosition.setX(_rightPosition.x()+_primeCostLabel->geometry().width()+_shift);
    _totalCostLabel = new QLabel(this);
    _totalCostLabel->setGeometry(QRect{_rightPosition, _lineEditSize});
    _totalCostLabel->setText(tr("Total cost"));
    _totalCostLabel->setAlignment(Qt::AlignHCenter);

    _rightPosition.setX(_indexLabel->x());
    _rightPosition.setY(_indexLabel->geometry().height()+_shift);
    _indexLine = new QLineEdit(this);
    _indexLine->setGeometry(QRect{_rightPosition, _lineEditSize});
    _indexLine->setAlignment(Qt::AlignHCenter);
    _indexLine->setPlaceholderText(tr("Index"));

    _rightPosition.setX(_primeCostLabel->x());
    _rightPosition.setY(_primeCostLabel->geometry().height()+_shift);
    _primeCostLine = new QLineEdit(this);
    _primeCostLine->setGeometry(QRect{_rightPosition, _lineEditSize});
    _primeCostLine->setReadOnly(true);
    _primeCostLine->setText(QString::number(_calculator.GetPrimeCost()));
    _primeCostLine->setAlignment(Qt::AlignHCenter);

    _rightPosition.setX(_totalCostLabel->x());
    _rightPosition.setY(_totalCostLabel->geometry().height()+_shift);
    _totalCostLine = new QLineEdit(this);
    _totalCostLine->setGeometry(QRect{_rightPosition, _lineEditSize});
    _totalCostLine->setReadOnly(true);
    _totalCostLine->setText(QString::number(_calculator.GetTotalCost(_indexLine->text().toDouble())));
    _totalCostLine->setAlignment(Qt::AlignHCenter);

    _rightPosition.setX(_indexLine->x());
    _rightPosition.setY(_indexLine->y() + _lineEditSize.height() + _shift);

    connect(_indexLine, &QLineEdit::textChanged, this, &Project::indexLineTextChanged);
}

void Project::CreateClientLine()
{
    _projectName = new QLabel(this);
    _projectName->setText(tr("Project name:"));
    _projectName->setGeometry(QRect{_rightPosition, _comboboxSize});
    _rightPosition.setX(_projectName->x());
    _rightPosition.setY(_projectName->y() + _comboboxSize.height() + _shift);

    _customerName = new QLabel(this);
    _customerName->setText(tr("Customer: "));
    _customerName->setGeometry(QRect{_rightPosition, _comboboxSize});
}

QStringList Project::ChooseMaterials(const QString &type)
{
    return _dataBase->ChooseMaterials(type);
}

QString& Project::CheckDot(QString &text) const
{
    text.replace(_comma, _dot);
    return text;
}

//slots
void Project::typeBoxCurrentTextChanged(const QString &text)
{
    _materialBox->clear();
    _materialBox->addItems(ChooseMaterials(text));
}

void Project::onBtnAddMaterials()
{
    //Запрос в БД на получение расхода
    double expence = _dataBase->GetExpense(_materialBox->currentText());
    QString areaText = _areaLine->text();
    QString priceText = _priceLine->text();
    //QString indexText = _indexLine->text();

    QHBoxLayout *innerLayout = new QHBoxLayout();
    innerLayout->setAlignment(Qt::AlignLeft);

    QLabel *type = new QLabel(_typeBox->currentText());
    type->setFixedHeight(_addinfLableHeight);
    innerLayout->addWidget(type);

    QLabel *material = new QLabel(_materialBox->currentText());
    innerLayout->addWidget(material);

    QLabel *number = new QLabel(CheckDot(areaText) + tr(" м2"));
    innerLayout->addWidget(number);

    QLabel *weight = new QLabel(QString::number(_calculator.CalcMaterialWeight(CheckDot(areaText).toDouble(), expence)) + " кг");
    innerLayout->addWidget(weight);

    QLabel *price = new QLabel(CheckDot(priceText) + tr(" руб."));
    innerLayout->addWidget(price);

    QLabel *cost = new QLabel(QString::number(_calculator.CalcMaterialCost(CheckDot(areaText).toDouble(), expence, CheckDot(priceText).toDouble())));
    innerLayout->addWidget(cost);
    innerLayout->setObjectName(cost->text());
    _primeCostLine->setText(QString::number(_calculator.GetPrimeCost()));
    emit _indexLine->textChanged(_indexLine->text());

    QPushButton *btnDelete = new QPushButton("-");
    btnDelete->setObjectName(QString ("%1").arg(_layoutWidget->count()));
    btnDelete->setFixedWidth(_addinfLableHeight);
    connect(btnDelete, &QPushButton::clicked, this, &Project::onDeleteButton);
    innerLayout->addWidget(btnDelete);

    _layoutWidget->insertLayout(_layoutWidget->count()-1, innerLayout);
    _spacer->changeSize(_spacerWidth, _spacer->geometry().height() - _addinfLableHeight);
}

void Project::indexLineTextChanged(const QString& newIndex)
{
    QString index = newIndex;
    _totalCostLine->setText(QString::number(_calculator.GetTotalCost(CheckDot(index).toDouble())));
}

void Project::onDeleteButton()
{
    auto currentRow = _layoutWidget->itemAt(sender()->objectName().toInt()-1);
    QString materialCost = currentRow->layout()->objectName();
    while(!currentRow->layout()->isEmpty())
        delete currentRow->layout()->itemAt(0)->widget();
    _spacer->changeSize(_spacerWidth, _spacer->geometry().height() + _addinfLableHeight);
    emit deleteMaterial(materialCost);
    emit _indexLine->textChanged(_indexLine->text());
}

void Project::onSubtractMaterial(QString &cost)
{
    QString newPrice {QString::number(_calculator.SubtractMaterial(CheckDot(cost).toDouble()))};
    _primeCostLine->setText(newPrice);
}

