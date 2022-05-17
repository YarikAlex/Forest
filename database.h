#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
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

    void connectDataBase();
    bool insertData(const QString &table, const QString &name, const QString &expense);
    QStringList getType();
    QStringList chooseMaterials(const QString& text);

private:
    QSqlDatabase _database;
    std::vector<std::pair<QString, QString>> _typeList {{"moss", tr("Мхи")},
                                         {"stabPlants", tr("Стабилизированные")},
                                         {"artPlants", tr("Искуственные")},
                                         {"bases", tr("Основания")},
                                         {"decorations", tr("Украшения")}};

    bool createTable(const QString& table);
    bool openDataBase();
    bool restoreDatabase();
    void closeDataBase();
    QString findTypeTable(const QString &text);

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

    QString _tableMossDeliveryQuery = "CREATE TABLE mossDelivery ("
                                      "id_moss INTEGER,"
                                      "id_supp INTEGER,"
                                      "price DOUBLE NOT NULL,"
                                      "number INTEGER NOT NULL,"
                                      "CONSTRAINT new_pk PRIMARY KEY (id_moss, id_supp),"
                                      "FOREIGN KEY (id_moss) REFERENCES moss (id)"
                                      "FOREIGN KEY (id_supp) REFERENCES suppliers (id));";

    QString _tableStabilizedPlantsDeliveryQuery = "CREATE TABLE stabPlantsDelivery ("
                                                  "id_stab INTEGER,"
                                                  "id_supp INTEGER,"
                                                  "price DOUBLE NOT NULL,"
                                                  "number INTEGER NOT NULL,"
                                                  "CONSTRAINT new_pk PRIMARY KEY (id_stab, id_supp),"
                                                  "FOREIGN KEY (id_stab) REFERENCES stabPlants (id)"
                                                  "FOREIGN KEY (id_supp) REFERENCES suppliers (id));";

    QString _tableArtificialPlantsDeliveryQuery = "CREATE TABLE artPlantsDelivery ("
                                                  "id_art INTEGER,"
                                                  "id_supp INTEGER,"
                                                  "price DOUBLE NOT NULL,"
                                                  "number INTEGER NOT NULL,"
                                                  "CONSTRAINT new_pk PRIMARY KEY (id_art, id_supp),"
                                                  "FOREIGN KEY (id_art) REFERENCES artPlants (id)"
                                                  "FOREIGN KEY (id_supp) REFERENCES suppliers (id));";

    QString _tableBasesDeliveryQuery = "CREATE TABLE basesDelivery ("
                                       "id_base INTEGER,"
                                       "id_supp INTEGER,"
                                       "price DOUBLE NOT NULL,"
                                       "number INTEGER NOT NULL,"
                                       "CONSTRAINT new_pk PRIMARY KEY (id_base, id_supp),"
                                       "FOREIGN KEY (id_base) REFERENCES bases (id)"
                                       "FOREIGN KEY (id_supp) REFERENCES suppliers (id));";

    QString _tableDecorationsDeliveryQuery = "CREATE TABLE decorationsDelivery ("
                                             "id_decor INTEGER,"
                                             "id_supp INTEGER,"
                                             "price DOUBLE NOT NULL,"
                                             "number INTEGER NOT NULL,"
                                             "CONSTRAINT new_pk PRIMARY KEY (id_decor, id_supp),"
                                             "FOREIGN KEY (id_decor) REFERENCES decorations (id)"
                                             "FOREIGN KEY (id_supp) REFERENCES suppliers (id));";


};

#endif // DATABASE_H
