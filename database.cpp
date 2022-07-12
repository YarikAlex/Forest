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

bool DataBase::InsertMaterialData(uint materialType, const QString &name, const QString &expense)
{
    QSqlQuery query;
    QString data = "INSERT INTO materials (type_id, material_name, expense) VALUES (:Type, :Name, :Expense)";
    query.prepare(data);
    query.bindValue(":Type", materialType);
    query.bindValue(":Name", name);
    query.bindValue(":Expense", expense.toDouble());
    if(!query.exec())
    {
        qDebug() << "DataBase: error insert into table materials";
        qDebug() << query.lastError().text();
        return false;
    }
    else
    {
        qDebug() << "DataBase: data into table materials successfully added.";
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
    QSqlQuery query("SELECT type_name "
                    "FROM materialTypes;");
    QStringList typesList;
    if(query.exec())
    {
        while(query.next())
        {
            QString name = query.value(0).toString();
            typesList.push_back(name);
        }
     }
    else
        qDebug() << "DataBase: query in GetType in not exec";

    return typesList;
}

QStringList DataBase::ChooseMaterials(const QString &text)
{
    QSqlQuery query("SELECT material_name, materialTypes.type_name "
                    "FROM materials "
                    "INNER JOIN materialTypes ON materialTypes.type_id = materials.type_id "
                    "WHERE type_name = '" + text + "';");
    QStringList materialsList;
    if(query.exec())
    {
        while(query.next())
        {
            QString name = query.value(0).toString();
            materialsList.push_back(name);
        }
    }
    else
        qDebug() << "DataBase: query in ChooseMaterials in not exec";
    return materialsList;
}

double DataBase::GetExpense(const QString &material)
{
    QSqlQuery query("SELECT expense "
                    "FROM materials "
                    "WHERE material_name = '" + material + "';");
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
        if(!this->CreateTable(_tableMaterialTypesQuery) ||
           !this->CreateTable(_tableMaterialsQuery) ||
           !this->CreateTable(_tableOrdersQuery) ||
           !this->CreateTable(_tableSuppliersQuery))
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
