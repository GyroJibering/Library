#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QCryptographicHash>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 连接 lineEdit1 的 returnPressed() 信号到槽函数
    connect(ui->User, &QLineEdit::returnPressed, this, &MainWindow::onReturnPressed);

    connect(ui->password, &QLineEdit::returnPressed, this, &MainWindow::onPasswordReturn);

    mainwindow_2 = new MainWindow2;
    ui->User->hide();
    ui->password->hide();
    ui->Password->hide();
    ui->Username->hide();
    ui->login->hide();
    ui->error_prompt->hide();
    ui->password->setEchoMode(QLineEdit::Password);
    // 设置窗口标题
    setWindowTitle("LibraVue");

    // 设置窗口图标
    setWindowIcon(QIcon(":/new/pic/logo.png"));

    this->setFixedSize(500, 645);
    QString styleSheet =
        // 正常状态下按钮的样式
        "QPushButton {"
        "background-color: #6495ED;"       // 冷调蓝色背景
        "color: white;"                     // 文本颜色为白色
        "padding: 10px 20px;"               // 内边距
        "font: bold 14px;"                  // 字体设置
        "border-radius: 20px;"              // 圆角边框
        "border: 2px solid #6495ED;"        // 边框样式和颜色
        "}"
        // 鼠标悬停在按钮上的样式
        "QPushButton:hover {"
        "background-color: #87CEEB;"       // 悬停时的浅蓝色背景
        "}"
        // 按钮按下时的样式
        "QPushButton:pressed {"
        "background-color: #4682B4;"       // 按下时的深蓝色背景
        "}";
    // 应用样式表到所有 QPushButton 上
    ui->pushButton->setStyleSheet(styleSheet);
    ui->pushButton_2->setStyleSheet(styleSheet);
    ui->login->setStyleSheet(styleSheet);

    QString styleSheet2 =
        "QLineEdit {"
        "background-color: rgba(255, 255, 255, 0.5);"  // 设置背景颜色为半透明白色
        "border: 1px solid #000000;"                    // 设置边框
        "padding: 5px;"                                // 设置内边距
        "}"
        "QLineEdit:hover {"
        "background-color: rgba(255, 255, 255, 0.8);" // 鼠标悬停时设置背景颜色为完全不透明白色
        "}";
    ui->User->setStyleSheet(styleSheet2);
    ui->password->setStyleSheet(styleSheet2);
}





MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createConnectionByName(const QString &connectionName){

    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL", connectionName);
    // 数据库连接需要设置的信息
    db.setHostName("127.0.0.1"); // 数据库服务器IP，我用的是本地电脑
    db.setDatabaseName("library");// 数据库名
    db.setUserName("postgres");// 用户名
    db.setPassword("lumilion");// 密码
    db.setPort(5432);// 端口号
    // 连接数据库
    bool ok = db.open();

    if (ok)
    {
        qDebug() << "database connect is ok";
    }
    else
    {
        qDebug() << "database connect is fail";
    }
}

// 使用自定义 connectionName 获取连接
QSqlDatabase MainWindow::getConnectionByName(const QString &connectionName) {
    // 获取数据库连接
    return QSqlDatabase::database(connectionName);
}

void MainWindow::on_pushButton_2_clicked()
{
    close();
}


void MainWindow::on_pushButton_clicked()
{
    ui->pushButton->hide(); // 隐藏第一个按钮
    ui->pushButton_2->hide(); // 隐藏第二个按钮
    ui->User->show();
    ui->password->show();
    ui->Password->show();
    ui->Username->show();
    ui->login->show();
}


void MainWindow::on_login_clicked() {
    // 获取用户名和密码
    QString username = ui->User->text();
    userid = username;//此处获取userid，后面有用
    QString password = ui->password->text();
    Privilege = true;
    // 查询数据库中与用户名对应的密码的哈希值
    createConnectionByName("firstConnect");
    QSqlDatabase db = getConnectionByName("firstConnect");
    QSqlQuery query(db);
    query.prepare("SELECT password FROM superlibrarian WHERE id = :username ");
    query.bindValue(":username", username);
    if (!query.exec()) {
        qWarning() << "Query failed:";
        return;
    }
    // 检查是否存在对应的用户名
    if (!query.next()) {
        qWarning() << "Username not found";
        Privilege = false;
        ui->error_prompt->show();
        query.prepare("SELECT password FROM librarian WHERE id = :username ");
        query.bindValue(":username", username);
        if (!query.exec()) {
            qWarning() << "Query failed:";
            return;
        }
        // 检查是否存在对应的用户名
        if (!query.next()) {
            qWarning() << "Username not found";
            ui->error_prompt->show();
            return;
        }
    }


    //qDebug()<<"1"<<Privilege;
    // 获取数据库中存储的哈希值
    QString dbHash = query.value(0).toString();

    // 对输入的密码进行摘要算法哈希
    QByteArray inputHash = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256);
    QString inputHashStr = QString(inputHash.toHex());

    // 检查密码是否匹配
    if (dbHash == inputHashStr) {
        // 登录成功，跳转到 widget2 界面，并关闭当前窗口
        mainwindow_2->show();
        close();
    } else {

        qWarning() << "Incorrect password";
        ui->error_prompt->show();
    }
}

// 在槽函数中处理按下回车键的事件
void MainWindow::onReturnPressed() {
    // 将焦点设置到下一个文本输入行
    ui->password->setFocus();
}

void MainWindow::onPasswordReturn() {
    // 模拟点击登录按钮
    ui->login->click();
}
