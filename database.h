#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QStandardItemModel>
#include <QDebug>
#include <QFile>
#include <vector>
#include <utility>


class DataBase : public QObject
{
    Q_OBJECT
public:
    explicit DataBase(QObject *parent = nullptr);
    ~DataBase();

    void ConnectDataBase();
    bool InsertMaterialData(uint materialType, const QString &name, const QString &expense);
    bool InsertSupplierData(std::vector<QString> &supplier)const;
    QStringList GetType();
    QStringList GetMaterials(const QString& text);
    double GetExpense(const QString& material);
    QStandardItemModel* GetOrders();

private:
    QSqlDatabase _database;
    std::vector<QString> _ordersTableHeaders = {tr("Date"), tr("Surname"), tr("Name"), tr("Material"), tr("Count"), tr("Price")};
    std::vector<std::pair<QString, QString>> _typeList {{"moss", tr("Мхи")},
                                         {"stabPlants", tr("Стабилизированные")},
                                         {"artPlants", tr("Искуственные")},
                                         {"bases", tr("Основания")},
                                         {"decorations", tr("Украшения")}};

    bool CreateTable(const QString& table);
    bool OpenDataBase();
    bool RestoreDatabase();
    void CloseDataBase();


    QString _tableMaterialTypesQuery = "CREATE TABLE materialTypes ("
                                        "type_id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
                                        "type_name TEXT NOT NULL);";

    QString _tableMaterialsQuery = "CREATE TABLE materials ("
                                          "material_id INTEGER PRIMARY KEY AUTOINCREMENT, "
                                          "type_id INTEGER NOT NULL,"
                                          "material_name TEXT NOT NULL,"
                                          "expense REAL NOT NULL,"
                                          "FOREIGN KEY (type_id) REFERENCES materialTypes (type_id));";

    QString _tableOrdersQuery = "CREATE TABLE orders ("
                                "order_id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                "material_id INTEGER NOT NULL,"
                                "supplier_id INTEGER NOT NULL,"
                                "date TEXT NOT NULL,"
                                "count REAL NOT NULL,"
                                "price REAL NOT NULL,"
                                "FOREIGN KEY(supplier_id) REFERENCES suppliers(supplier_id),"
                                "FOREIGN KEY(material_id) REFERENCES materials(material_id));";

    QString _tableSuppliersQuery = "CREATE TABLE suppliers ("
                                   "supplier_id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                   "surname TEXT NOT NULL,"
                                   "name TEXT NOT NULL,"
                                   "phone TEXT NOT NULL,"
                                   "city TEXT,"
                                   "street TEXT,"
                                   "house TEXT,"
                                   "site TEXT);";
};

#endif // DATABASE_H
