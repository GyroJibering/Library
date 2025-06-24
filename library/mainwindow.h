#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <mainwindow2.h>
#include <QtSql/QSqlDatabase>
#include <QDebug>
#include <QApplication>
#include <QSqlQuery>
#include <QLineEdit>
#include <global.h>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


public :
    void createConnectionByName(const QString &connectionName); //使用自定义 connectionName 创建连接
    QSqlDatabase getConnectionByName(const QString &connectionName);  // 使用自定义 connectionName 获取连接

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_login_clicked();

    void onReturnPressed(); // 声明 onReturnPressed 方法为槽函数，用于用户名

    void onPasswordReturn(); // 声明一个新的槽函数,用于密码框

private:
    Ui::MainWindow *ui;
    MainWindow2 *mainwindow_2;
};
#endif // MAINWINDOW_H
