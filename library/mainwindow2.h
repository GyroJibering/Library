#ifndef MAINWINDOW2_H
#define MAINWINDOW2_H

#include <QMainWindow>
#include <QtSql/QSqlDatabase>
#include <QDebug>
#include <QApplication>
#include <QSqlQuery>
#include <QLineEdit>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTableWidget>  // 用于创建表格
#include <QTableWidgetItem>  // 用于操作表格中的单元格项
#include <QHeaderView>  // 用于设置表头
#include <QStringList>  // 用于处理字符串列表
#include <QCryptographicHash>
#include <QtWidgets>
namespace Ui {
class MainWindow2;
}

class MainWindow2 : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow2(QWidget *parent = nullptr);
    ~MainWindow2();


private slots:
    void onAddUser();
    void onDeleteUser();
    void onUpdateUserInfo();
    void onModifyBookInfo();
    void onBookReturn();
    void onAddNewBook();
    void onBookSale();
    void onViewBill();
    void logout();
    void handleItemChanged(QTableWidget *tableWidget, QTableWidgetItem *item);
    void handleBookItemChanged(QTableWidget *bookTableWidget, QTableWidgetItem *item);

private:
    Ui::MainWindow2 *ui;

};

#endif // MAINWINDOW2_H
