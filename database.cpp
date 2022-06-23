#include "database.h"

DataBase::DataBase(QObject *parent) : QObject{parent} {}

DataBase::~DataBase() {}

//public metods
void DataBase::ConnectDataBase()
{
    if(!QFile("../Databases/ForestDataBase.db").exists())
    {
        this->RestoreDatabase();
    }
    else
    {
        this->OpenDataBase();
    }
}

bool DataBase::InsertMaterialData(const QString &table, const QString &name, const QString &expense)
{
    QSqlQuery query;
    QString data = "INSERT INTO " + FindTypeTable(table) + "(name, expenses) VALUES (:Name, :Expense)";
    query.prepare(data);
    query.bindValue(":Name", name);
    query.bindValue(":Expense", expense.toDouble());
    if(!query.exec())
    {
        qDebug() << "DataBase: error insert into table " << table;
        qDebug() << query.lastError().text();
        return false;
    }
    else
    {
        qDebug() << "DataBase: data into " << table << " successfully added.";
        return true;
    }
    return false;
}

bool DataBase::InsertSupplierData(std::vector<QString>& supplier) const
{
    QSqlQuery query;
    QString data = "INSERT INTO suppliers (surname, name, phone, city, street, house, site)"
                   "VALUES(:SURNAME, :NAME, :PHONE, :CITY, :STREET, :HOUSE, :SITE)";
    query.prepare(data);
    query.bindValue(":SURNAME", supplier[0]);
    query.bindValue(":NAME", supplier[1]);
    query.bindValue(":PHONE", supplier[2]);
    query.bindValue(":CITY", supplier[3]);
    query.bindValue(":STREET", supplier[4]);
    query.bindValue(":HOUSE", supplier[5]);
    query.bindValue(":SITE", supplier[6]);
    if(!query.exec())
    {
        qDebug() << "DataBase: error insert into table suppliers";
        qDebug() << query.lastError().text();
        return false;
    }
    else
    {
        qDebug() << "DataBase: data into suppliers successfully added.";
        return true;
    }
    return false;
}

QStringList DataBase::GetType()
{
    QStringList types;
    for(auto &iter: _typeList)
    {
        types.push_back(iter.second);
    }
    return types;
}

QStringList DataBase::ChooseMaterials(const QString &text)
{
    QSqlQuery query("SELECT name FROM " + FindTypeTable(text));
    QStringList materialsList;
    while(query.next())
    {
        QString name = query.value(0).toString();
        materialsList.push_back(name);
    }
    return materialsList;
}

double DataBase::GetExpense(const QString &table, const QString &material)
{
    QSqlQuery query("SELECT expenses FROM " + FindTypeTable(table) + " WHERE name = '" + material + "';");
    double result = 0;
    if(query.next())
        result = query.value(0).toDouble();
    return result;
}

//private metods
bool DataBase::CreateTable(const QString& table)
{
    QSqlQuery query;
    if(!query.exec(table))
    {
        qDebug() << "DataBase: error of create table " << table;
        qDebug() << query.lastError().text();
        return false;
    }
    else
    {
        qDebug() << "DataBase: table " << table << " successfully created.";
        return true;
    }
    return false;
}

bool DataBase::OpenDataBase()
{
    _database = QSqlDatabase::addDatabase("QSQLITE");
    _database.setHostName("DataBase");
    _database.setDatabaseName("../Databases/ForestDataBase.db");
    if(_database.open()) return true;
    else return false;
}

bool DataBase::RestoreDatabase()
{
    if(this->OpenDataBase())
    {
        if(!this->CreateTable(_tableMossQuery) ||
           !this->CreateTable(_tableStabilizedPlantsQuery) ||
           !this->CreateTable(_tableArtificialPlantsQuery) ||
           !this->CreateTable(_tableBasesQuery) ||
           !this->CreateTable(_tableDecorationsQuery) ||
           !this->CreateTable(_tableSuppliersQuery) ||
           !this->CreateTable(_tableMossDeliveryQuery) ||
           !this->CreateTable(_tableStabilizedPlantsDeliveryQuery) ||
           !this->CreateTable(_tableArtificialPlantsDeliveryQuery) ||
           !this->CreateTable(_tableBasesDeliveryQuery) ||
           !this->CreateTable(_tableDecorationsDeliveryQuery))
        {
            return false;
        }
        else return true;
    }
    else
    {
        return false;
    }
}

void DataBase::CloseDataBase()
{
    _database.close();
}

QString DataBase::FindTypeTable(const QString& text)
{
    for(auto &iter: _typeList)
    {
        if(text == iter.second)
            return iter.first;
    }
    return QString {};
}
