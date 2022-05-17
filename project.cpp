#include "project.h"
#include <QSqlQuery>

Project::Project(DataBase* dataBase, QWidget *parent)
    : QWidget{parent}, _dataBase(dataBase)
{
    _window = new QWidget(this);

    _mainLayout = new QHBoxLayout(_window);
    _leftLayout = new QVBoxLayout(_window);
    _leftLayout->addLayout(createTitleLine(_window));
    _leftLayout->addLayout(createMaterialsLine(_window));
    _leftLayout->addSpacing(100);

    _rightLayout = new QVBoxLayout(_window);
    _rightLayout->addLayout(createResultBox(_window));
    _mainLayout->addLayout(_leftLayout);
    _mainLayout->addSpacing(100);
    _mainLayout->addLayout(_rightLayout);

    connect(_typeBox, &QComboBox::currentTextChanged, this, &Project::typeBox_currentTextChanged);

}

QHBoxLayout *Project::createTitleLine(QWidget *parent)
{
    QHBoxLayout *lineLayout = new QHBoxLayout(parent);

    _typeLabel = new QLabel(this);
    _materialLabel = new QLabel(this);
    _numberLabel = new QLabel(this);
    _costLabel = new QLabel(this);

    _typeLabel->setText(tr("Тип"));
    _materialLabel->setText(tr("Материал"));
    _numberLabel->setText(tr("Количество"));
    _costLabel->setText(tr("Cтоимость"));

    _typeLabel->setFixedSize(105, 25);
    _materialLabel->setFixedSize(100, 25);
    _numberLabel->setFixedSize(100, 25);
    _costLabel->setFixedSize(100, 25);

    lineLayout->addWidget(_typeLabel);
    lineLayout->addWidget(_materialLabel);
    lineLayout->addWidget(_numberLabel);
    lineLayout->addWidget(_costLabel);

    return lineLayout;
}

QHBoxLayout *Project::createMaterialsLine(QWidget *parent)
{
    QHBoxLayout *lineLayout = new QHBoxLayout(parent);
    _typeBox = new QComboBox(this);
    _materialBox = new QComboBox(this);
    _numberLine = new QLineEdit(this);
    _costLine = new QLineEdit(this);
    _addNewMaterial = new QPushButton(this);

    _typeBox->setFixedSize(130, 25);
    _typeBox->addItems(_dataBase->getType());
    _materialBox->setFixedSize(100, 25);
    _materialBox->addItems(chooseMaterials(_typeBox->currentText()));
    _numberLine->setFixedSize(100, 25);
    _costLine->setFixedSize(100, 25);
    _costLine->setReadOnly(true);
    _addNewMaterial->setFixedSize(30, 25);
    _addNewMaterial->setText("+");

    lineLayout->addWidget(_typeBox);
    lineLayout->addWidget(_materialBox);
    lineLayout->addWidget(_numberLine);
    lineLayout->addWidget(_costLine);
    lineLayout->addWidget(_addNewMaterial);

    return lineLayout;
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
void Project::typeBox_currentTextChanged(const QString text)
{
    _materialBox->clear();
    _materialBox->addItems(chooseMaterials(text));
}

