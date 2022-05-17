#include "database.h"

DataBase::DataBase(QObject *parent) : QObject{parent} {}

DataBase::~DataBase() {}

//public metods
void DataBase::connectDataBase()
{
    if(!QFile("../Databases/ForestDataBase.db").exists())
    {
        this->restoreDatabase();
    }
    else
    {
        this->openDataBase();
    }
}

bool DataBase::insertData(const QString &table, const QString &name, const QString &expense)
{
    QSqlQuery query;
    QString data = "INSERT INTO " + findTypeTable(table) + "(name, expenses) VALUES (:Name, :Expense)";
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

QStringList DataBase::getType()
{
    QStringList types;
    for(auto iter: _typeList)
    {
        types.push_back(iter.second);
    }
    return types;
}

QStringList DataBase::chooseMaterials(const QString &text)
{
    QSqlQuery query("SELECT name FROM " + findTypeTable(text));
    QStringList materialsList;
    while(query.next())
    {
        QString name = query.value(0).toString();
        materialsList.push_back(name);
    }
    return materialsList;
}

//private metods
bool DataBase::createTable(const QString& table)
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

bool DataBase::openDataBase()
{
    _database = QSqlDatabase::addDatabase("QSQLITE");
    _database.setHostName("DataBase");
    _database.setDatabaseName("../Databases/ForestDataBase.db");
    if(_database.open()) return true;
    else return false;
}

bool DataBase::restoreDatabase()
{
    if(this->openDataBase())
    {
        if(!this->createTable(_tableMossQuery) ||
           !this->createTable(_tableStabilizedPlantsQuery) ||
           !this->createTable(_tableArtificialPlantsQuery) ||
           !this->createTable(_tableBasesQuery) ||
           !this->createTable(_tableDecorationsQuery) ||
           !this->createTable(_tableSuppliersQuery) ||
           !this->createTable(_tableMossDeliveryQuery) ||
           !this->createTable(_tableStabilizedPlantsDeliveryQuery) ||
           !this->createTable(_tableArtificialPlantsDeliveryQuery) ||
           !this->createTable(_tableBasesDeliveryQuery) ||
           !this->createTable(_tableDecorationsDeliveryQuery))
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

void DataBase::closeDataBase()
{
    _database.close();
}

QString DataBase::findTypeTable(const QString& text)
{
    for(auto iter: _typeList)
    {
        if(text == iter.second)
            return iter.first;
    }
    return QString {};
}
