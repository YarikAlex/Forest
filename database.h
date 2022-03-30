#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QFile>

class DataBase : public QObject
{
    Q_OBJECT
public:
    explicit DataBase(QObject *parent = nullptr);
    ~DataBase();

    void connectDataBase();
    bool insertData(const QString& table, const QString &data);

private:
    QSqlDatabase _database;

    bool createTable(const QString& table);
    bool openDataBase();
    bool restoreDatabase();
    void closeDataBase();

    QString _tableMossQuery = "CREATE TABLE moss ("
                              "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                              "name CHAR(50) NOT NULL,"
                              "expenses DOUBLE NOT NULL);";

    QString _tableStabilizedPlantsQuery = "CREATE TABLE stabPlants ("
                                          "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                                          "name CHAR(50) NOT NULL,"
                                          "expenses DOUBLE NOT NULL);";

    QString _tableArtificialPlantsQuery = "CREATE TABLE artPlants ("
                                          "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                          "name CHAR(50) NOT NULL,"
                                          "expenses DOUBLE NOT NULL);";

    QString _tableBasesQuery = "CREATE TABLE bases ("
                               "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                               "name CHAR(50) NOT NULL,"
                               "expenses DOUBLE NOT NULL);";

    QString _tableDecorationsQuery = "CREATE TABLE decorations ("
                                     "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                     "name CHAR(50) NOT NULL,"
                                     "expenses DOUBLE NOT NULL);";

    QString _tableSuppliersQuery = "CREATE TABLE suppliers ("
                                   "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                   "surname CHAR(30) NOT NULL,"
                                   "name CHAR(20) NOT NULL,"
                                   "phone CHAR(20) NOT NULL,"
                                   "city CHAR(20),"
                                   "street CHAR(20),"
                                   "house CHAR(20),"
                                   "site CHAR(50));";

    QString _tableMossDeliveryQuery;
    QString _tableStabilizedPlantsDeliveryQuery;
    QString _tableArtificialPlantsDeliveryQuery;
    QString _tableDecorationsDeliveryQuery;


};

#endif // DATABASE_H
