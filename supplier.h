#ifndef SUPPLIER_H
#define SUPPLIER_H

#include <QDialog>
#include <vector>

namespace Ui {
class Supplier;
}

class Supplier : public QDialog
{
    Q_OBJECT

public:
    explicit Supplier(QWidget *parent = nullptr);
    ~Supplier();

signals:
    void getSupplier(std::vector<QString>&);

private slots:
    void on_btn_cancel_clicked();
    void on_btn_add_clicked();

private:
    Ui::Supplier *ui;
};

#endif // SUPPLIER_H
