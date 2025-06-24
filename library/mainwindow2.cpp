#include "mainwindow2.h"
#include "mainwindow.h"
#include "ui_mainwindow2.h"
#include <QFormLayout>

MainWindow2::MainWindow2(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow2)
{
    ui->setupUi(this);
    // 设置窗口标题
    setWindowTitle("LibraVue");

    // 设置窗口图标
    setWindowIcon(QIcon(":/new/pic/logo.png"));
    this->setFixedSize(1165, 688);
    // 创建菜单栏
    QMenuBar *menuBar = new QMenuBar(this);
    setMenuBar(menuBar);
    menuBar->setStyleSheet("font-size: 16px; color: white; background-color: #6495ED;");
    // 创建 "Users" 菜单
    QMenu *usersMenu = menuBar->addMenu(tr("Users"));
    usersMenu->setStyleSheet("font-size: 14px; color: white; background-color: #4682B4;");


    // 添加 "增加用户" 动作，并连接到槽函数
    QAction *addUserAction = new QAction(tr("Add"), this);
    usersMenu->addAction(addUserAction);
    connect(addUserAction, &QAction::triggered, this, &MainWindow2::onAddUser);

    // 添加 "删除用户" 动作，并连接到槽函数
    QAction *deleteUserAction = new QAction(tr("Delete"), this);
    usersMenu->addAction(deleteUserAction);
    connect(deleteUserAction, &QAction::triggered, this, &MainWindow2::onDeleteUser);

    // 添加 "修改用户信息" 动作，并连接到槽函数
    QAction *updateUserInfoAction = new QAction(tr("Information"), this);
    usersMenu->addAction(updateUserInfoAction);
    connect(updateUserInfoAction, &QAction::triggered, this, &MainWindow2::onUpdateUserInfo);

    QAction *logout = new QAction(tr("Log out"), this);
    usersMenu->addAction(logout);
    connect(logout, &QAction::triggered, this, &MainWindow2::logout);
    // 创建 "Inventory Management" 菜单
    QMenu *inventoryMenu = menuBar->addMenu(tr("Inventory"));
    inventoryMenu->setStyleSheet("font-size: 14px; color: white; background-color: #4682B4;");

    // 添加 "Book Information Modification" 动作，并连接到槽函数
    QAction *modifyBookInfoAction = new QAction(tr("Information"), this);
    inventoryMenu->addAction(modifyBookInfoAction);
    connect(modifyBookInfoAction, &QAction::triggered, this, &MainWindow2::onModifyBookInfo);

    // 创建 "Book Purchase" 菜单
    QMenu *bookPurchaseMenu = menuBar->addMenu(tr("Book Purchase"));
    bookPurchaseMenu->setStyleSheet("font-size: 14px; color: white; background-color: #4682B4;");

    // 添加 "Add New Book" 动作，并连接到槽函数
    QAction *addNewBookAction = new QAction(tr("Add New Book"), this);
    bookPurchaseMenu->addAction(addNewBookAction);
    connect(addNewBookAction, &QAction::triggered, this, &MainWindow2::onAddNewBook);

    // 添加 "Book Return" 动作，并连接到槽函数
    QAction *bookReturnAction = new QAction(tr("Return and Purchase"), this);
    bookPurchaseMenu->addAction(bookReturnAction);
    connect(bookReturnAction, &QAction::triggered, this, &MainWindow2::onBookReturn);

    // 创建 "Book Sale" 菜单
    QMenu *bookSaleMenu = menuBar->addMenu(tr("Book Sale"));
    bookSaleMenu->setStyleSheet("font-size: 14px; color: white; background-color: #4682B4;");
    // 添加 "书籍出售" 动作
    QAction *bookSaleAction = new QAction(tr("Sale"), this);
    bookSaleMenu->addAction(bookSaleAction);

    // 添加 "查看账单" 动作
    QAction *viewBillAction = new QAction(tr("Bill"), this);
    bookSaleMenu->addAction(viewBillAction);

    // 连接菜单项的槽函数
    connect(bookSaleAction, &QAction::triggered, this, &MainWindow2::onBookSale);
    connect(viewBillAction, &QAction::triggered, this, &MainWindow2::onViewBill);


}

MainWindow2::~MainWindow2()
{
    delete ui;
}

//添加人员槽函数
void MainWindow2::onAddUser()
{
    if(!Privilege)
    {
        QDialog *NoAccess1 = new QDialog;
        QLabel *label = new QLabel("Sorry, you don't have \npermission.", NoAccess1);
        NoAccess1->setFixedSize(200,100);
        QVBoxLayout *layout = new QVBoxLayout(NoAccess1);
        layout->addWidget(label);
        NoAccess1->setLayout(layout);
        NoAccess1->setWindowTitle("access denied");
        NoAccess1->exec();
        return;
    }

    QDialog *addUserDialog = new QDialog(this);
    addUserDialog->setWindowTitle(tr("Add User"));
    addUserDialog->setFixedSize(300, 400);

    // 添加对话框中的组件，包括 id、name、gender、age 和 password
    QLabel *idLabel = new QLabel(tr("ID:"), addUserDialog);
    QLineEdit *idLineEdit = new QLineEdit(addUserDialog);

    QLabel *nameLabel = new QLabel(tr("Name:"), addUserDialog);
    QLineEdit *nameLineEdit = new QLineEdit(addUserDialog);

    QLabel *genderLabel = new QLabel(tr("Gender:"), addUserDialog);
    QComboBox *genderComboBox = new QComboBox(addUserDialog);
    genderComboBox->addItem(tr("男"));
    genderComboBox->addItem(tr("女"));

    QLabel *ageLabel = new QLabel(tr("Age:"), addUserDialog);
    QSpinBox *ageSpinBox = new QSpinBox(addUserDialog);
    ageSpinBox->setRange(1, 100);

    QLabel *passwordLabel = new QLabel(tr("Password:"), addUserDialog);
    QLineEdit *passwordLineEdit = new QLineEdit(addUserDialog);
    passwordLineEdit->setEchoMode(QLineEdit::Password);

    QPushButton *confirmButton = new QPushButton(tr("Confirm"), addUserDialog);
    QPushButton *cancelButton = new QPushButton(tr("Cancel"), addUserDialog);

    // 布局管理
    QVBoxLayout *layout = new QVBoxLayout(addUserDialog);
    layout->addWidget(idLabel);
    layout->addWidget(idLineEdit);
    layout->addWidget(nameLabel);
    layout->addWidget(nameLineEdit);
    layout->addWidget(genderLabel);
    layout->addWidget(genderComboBox);
    layout->addWidget(ageLabel);
    layout->addWidget(ageSpinBox);
    layout->addWidget(passwordLabel);
    layout->addWidget(passwordLineEdit);
    layout->addWidget(confirmButton);
    layout->addWidget(cancelButton);
    addUserDialog->setLayout(layout);

    // 连接按钮的槽函数
    connect(confirmButton, &QPushButton::clicked, addUserDialog, &QDialog::accept);
    connect(cancelButton, &QPushButton::clicked, addUserDialog, &QDialog::reject);

    // 显示对话框
    int result = addUserDialog->exec();

    // 根据对话框的返回值执行相应操作
    if (result == QDialog::Accepted) {
        // 用户点击了确认按钮
        QString id = idLineEdit->text();
        QString name = nameLineEdit->text();
        QString gender = genderComboBox->currentText();
        int age = ageSpinBox->value();
        QString password = passwordLineEdit->text();
        // 在这里执行添加用户的操作，可以将获取到的用户信息存入数据库或进行其他处理
        MainWindow mainWindow;
        mainWindow.createConnectionByName("Connect2");
        QSqlDatabase db = mainWindow.getConnectionByName("Connect2");
        QSqlQuery query(db);
        query.prepare("INSERT INTO librarian (id, name, gender, age, password) "
                      "VALUES (:id, :name, :gender, :age, :password)");
        query.bindValue(":id", id);
        query.bindValue(":name", name);
        query.bindValue(":gender", gender);
        query.bindValue(":age", age);
        QByteArray inputHash = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256);
        QString inputHashStr = QString(inputHash.toHex());
        query.bindValue(":password", inputHashStr);

        if (!query.exec()) {
            qWarning() << "Insert failed:" ;

        } else {
            qDebug() << "User inserted successfully!";
        }

    }
    else {
        // 用户点击了取消按钮或关闭按钮
        addUserDialog->close();
    }
}

//删除人员槽函数
void MainWindow2::onDeleteUser()
{
    if(!Privilege)
    {
        QDialog *NoAccess1 = new QDialog;
        QLabel *label = new QLabel("Sorry, you don't have \npermission.", NoAccess1);
        NoAccess1->setFixedSize(200,100);
        // 创建一个垂直布局管理器并将标签添加到其中
        QVBoxLayout *layout = new QVBoxLayout(NoAccess1);
        layout->addWidget(label);

        // 设置对话框的布局
        NoAccess1->setLayout(layout);

        // 设置对话框的标题
        NoAccess1->setWindowTitle("access denied");
        NoAccess1->exec();
        return;
    }
    // 创建一个删除用户的对话框
    QDialog *deleteUserDialog = new QDialog(this);
    deleteUserDialog->setWindowTitle(tr("Delete User"));
    deleteUserDialog->setFixedSize(300, 200);

    // 添加对话框中的组件，包括 id 和确认按钮
    QLabel *idLabel = new QLabel(tr("ID:"), deleteUserDialog);
    QLineEdit *idLineEdit = new QLineEdit(deleteUserDialog);

    QPushButton *confirmButton = new QPushButton(tr("Confirm"), deleteUserDialog);
    QPushButton *cancelButton = new QPushButton(tr("Cancel"), deleteUserDialog);

    // 布局管理
    QVBoxLayout *layout = new QVBoxLayout(deleteUserDialog);
    layout->addWidget(idLabel);
    layout->addWidget(idLineEdit);
    layout->addWidget(confirmButton);
    layout->addWidget(cancelButton);
    deleteUserDialog->setLayout(layout);

    // 连接按钮的槽函数
    connect(confirmButton, &QPushButton::clicked, deleteUserDialog, &QDialog::accept);
    connect(cancelButton, &QPushButton::clicked, deleteUserDialog, &QDialog::reject);

    // 显示对话框
    int result = deleteUserDialog->exec();

    // 根据对话框的返回值执行相应操作
    if (result == QDialog::Accepted) {
        // 用户点击了确认按钮
        QString id = idLineEdit->text();
        // 执行删除操作
        MainWindow mainWindow;
        mainWindow.createConnectionByName("Connect2");
        QSqlDatabase db = mainWindow.getConnectionByName("Connect2");
        QSqlQuery query(db);
        query.prepare("DELETE FROM librarian WHERE id = :id");
        query.bindValue(":id", id);

        // 执行 SQL 删除语句
        if (!query.exec()) {
            qWarning() << "Delete query failed:" ;
            return;
        }

        // 显示删除成功的消息或执行其他操作
        qDebug() << "Record with ID" << id << "has been deleted successfully!";

    }
    else {
        // 用户点击了取消按钮或关闭按钮
        deleteUserDialog->close();
    }
    //*********************************************************************************

}

//更新人员信息槽函数
void MainWindow2::onUpdateUserInfo()
{
    // 创建一个窗口来展示用户信息表格
    QDialog *userInfoDialog = new QDialog(this);
    userInfoDialog->setWindowTitle(tr("User Information"));
    userInfoDialog->setFixedSize(550, 300);

    // 创建一个表格来展示用户信息
    QTableWidget *userTableWidget = new QTableWidget(userInfoDialog);
    userTableWidget->setColumnCount(4); // 设置表格列数为4，对应id、name、gender、age

    QStringList headers;
    headers << tr("ID") << tr("Name") << tr("Gender") << tr("Age");
    userTableWidget->setHorizontalHeaderLabels(headers);

    // 从数据库中获取用户信息并添加到表格中
    MainWindow mainWindow;
    mainWindow.createConnectionByName("Connect2");
    QSqlDatabase db = mainWindow.getConnectionByName("Connect2");
    QSqlQuery query(db);
    QSqlQuery query1(db);

    if(Privilege)
    {
        query1.exec("SELECT COUNT(*) FROM librarian");
        if (query1.next()) {
            int rowCount = query1.value(0).toInt();
            userTableWidget->setRowCount(rowCount);
        } else {
            qDebug() << "Failed to retrieve row count from database.";
        }
    }
    else
        userTableWidget->setRowCount(1);
    if(Privilege)
    {
        query.exec("SELECT id, name, gender, age FROM librarian");
    }
    else
    {
        query.exec("SELECT id, name, gender, age FROM librarian"
                   "WHERE id = :username");
        query.bindValue(":username", userid);
    }
    //*************************************************************************
    query.exec("SELECT id, name, gender, age FROM librarian");
    int row = 0;
    while (query.next()) {                             // [3] 遍历查询结果
        // 从查询结果中获取用户信息
        QString id = query.value("id").toString();
        QString name = query.value("name").toString();
        QString gender = query.value("gender").toString();
        int age = query.value("age").toInt();
        //qDebug() << id << name << gender << age;
        QString ageString = QString::number(age);
        userTableWidget->setItem(row, 0, new QTableWidgetItem(id)); // id 列
        userTableWidget->setItem(row, 1, new QTableWidgetItem(name)); // name 列
        userTableWidget->setItem(row, 2, new QTableWidgetItem(gender)); // gender 列
        userTableWidget->setItem(row, 3, new QTableWidgetItem(ageString)); // age 列
        // 增加行索引，准备处理下一行数据
        ++row;
    }

    // 设置第一列不可更改
    for (int row = 0; row < userTableWidget->rowCount(); ++row) {
        QTableWidgetItem *item = userTableWidget->item(row, 0);
        if (item)
            item->setFlags(item->flags() & ~Qt::ItemIsEditable); // 移除编辑标志
    }

    // 连接表格的 itemChanged 信号到槽函数，实现实时更新数据库
    connect(userTableWidget, &QTableWidget::itemChanged, this, [=](QTableWidgetItem *item){
        handleItemChanged(userTableWidget, item);
    });

    userTableWidget->setShowGrid(false);
    // 布局管理
    QVBoxLayout *layout = new QVBoxLayout(userInfoDialog);
    layout->addWidget(userTableWidget);
    userInfoDialog->setLayout(layout);

    // 显示对话框
    userInfoDialog->exec();
}

//辅助函数
void MainWindow2::handleItemChanged(QTableWidget *userTableWidget, QTableWidgetItem *item)
{
    if (item) {
        // 获取行和列索引
        int row = item->row();
        int column = item->column();

        // 获取新值
        QString newValue = item->text();

        // 根据行、列索引和新值执行相应的操作
        // 比如更新数据库中的对应数据
        QString columnName;
        switch (column) {
        case 0:
            columnName = "id";
            break;
        case 1:
            columnName = "name";
            break;
        case 2:
            columnName = "gender";
            break;
        case 3:
            columnName = "age";
            break;
        default:
            break;
        }

        // 更新数据库中的数据
        MainWindow mainWindow;
        mainWindow.createConnectionByName("Connect2");
        QSqlDatabase db = mainWindow.getConnectionByName("Connect2");
        QSqlQuery query(db);
        query.prepare("UPDATE librarian SET " + columnName + " = :newValue WHERE id = :id");
        query.bindValue(":newValue", newValue);
        query.bindValue(":id", userTableWidget->item(row, 0)->text()); // 根据 id 更新相应的行
        qDebug()<<columnName<<" "<<newValue;
        if (!query.exec()) {
            qWarning() << "Update failed:" ;
        } else {
            qDebug() << "User information updated successfully!";
        }
    }
}

//更新书籍信息槽函数
void MainWindow2::onModifyBookInfo()
{
    // 创建一个窗口来展示图书信息管理界面
    QDialog *bookInfoDialog = new QDialog(this);
    bookInfoDialog->setWindowTitle(tr("Book Information Management"));
    bookInfoDialog->setFixedSize(800, 600);

    // 创建一个垂直布局管理器来放置表格和查询窗口
    QVBoxLayout *mainLayout = new QVBoxLayout(bookInfoDialog);

    // 创建一个水平布局管理器来放置查询组件
    QHBoxLayout *queryLayout = new QHBoxLayout;

    // 创建一个标签和文本框用于输入查询条件
    QLabel *queryLabel = new QLabel(tr("Query:"), bookInfoDialog);
    QLineEdit *queryLineEdit = new QLineEdit(bookInfoDialog);
    QPushButton *searchButton = new QPushButton(tr("Search"), bookInfoDialog);
    QPushButton *refreshButton = new QPushButton(tr("Refresh"), this);

    // 连接刷新按钮的点击事件
    connect(refreshButton, &QPushButton::clicked, [=]() {
        // 关闭书籍信息对话框（如果已经打开）
        if (bookInfoDialog && bookInfoDialog->isVisible()) {
            bookInfoDialog->close();
            delete bookInfoDialog;
        }
        // 重新打开书籍信息对话框
        onModifyBookInfo();
    });

    // 将查询组件添加到水平布局管理器中
    queryLayout->addWidget(queryLabel);
    queryLayout->addWidget(queryLineEdit);
    queryLayout->addWidget(searchButton);
    queryLayout->addWidget(refreshButton);

    // 创建一个表格来展示图书信息
    QTableWidget *bookTableWidget = new QTableWidget(bookInfoDialog);
    bookTableWidget->setColumnCount(7); // 设置表格列数为7，对应书籍编号、ISBN、标题、作者、出版商、价格、库存数量

    QStringList headers;
    headers << tr("ID") << tr("ISBN") << tr("Title") << tr("Author") << tr("Publisher") << tr("Price") << tr("Quantity");
    bookTableWidget->setHorizontalHeaderLabels(headers);

    // 设置表格的大小策略
    bookTableWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // 添加表格和查询组件到垂直布局管理器中
    mainLayout->addLayout(queryLayout);
    mainLayout->addWidget(bookTableWidget);

    MainWindow mainWindow;
    mainWindow.createConnectionByName("Connect2");
    QSqlDatabase db = mainWindow.getConnectionByName("Connect2");
    QSqlQuery query(db);
    QSqlQuery query1(db);
    query1.exec("SELECT COUNT(*) FROM inventory");
    if (query1.next()) {
        int rowCount = query1.value(0).toInt();
        bookTableWidget->setRowCount(rowCount);
    } else {
        qDebug() << "Failed to retrieve row count from database.";
    }
    query.exec("SELECT id, \"ISBN\", title, author, publisher, price, quantity FROM public.inventory ORDER BY id ASC");
    int row = 0;
    while (query.next()) {
        // 从查询结果中获取图书信息
        QString id = query.value("id").toString();
        QString ISBN = query.value("ISBN").toString();
        QString title = query.value("title").toString();
        QString author = query.value("author").toString();
        QString publisher = query.value("publisher").toString();
        QString price = query.value("price").toString();
        QString quantity = query.value("quantity").toString();

        bookTableWidget->setItem(row, 0, new QTableWidgetItem(id)); // 书籍编号
        bookTableWidget->setItem(row, 1, new QTableWidgetItem(ISBN)); // ISBN
        bookTableWidget->setItem(row, 2, new QTableWidgetItem(title)); // 标题
        bookTableWidget->setItem(row, 3, new QTableWidgetItem(author)); // 作者
        bookTableWidget->setItem(row, 4, new QTableWidgetItem(publisher)); // 出版商
        bookTableWidget->setItem(row, 5, new QTableWidgetItem(price)); // 价格
        bookTableWidget->setItem(row, 6, new QTableWidgetItem(quantity)); // 库存数量

        ++row;
    }

    // 设置第0列和第1列不可更改
    for (int row = 0; row < bookTableWidget->rowCount(); ++row) {
        for (int col = 0; col < bookTableWidget->columnCount(); ++col) {
            if (col == 0 || col == 1) { // 第0列和第1列
                QTableWidgetItem *item = bookTableWidget->item(row, col);
                if (item)
                    item->setFlags(item->flags() & ~Qt::ItemIsEditable); // 移除编辑标志
            }
        }
    }

    connect(bookTableWidget, &QTableWidget::itemChanged, this, [=](QTableWidgetItem *item) {
        handleBookItemChanged(bookTableWidget, item);
    });

    // 连接查询按钮的槽函数
    connect(searchButton, &QPushButton::clicked, [=]() {
        QString queryText = queryLineEdit->text();
        QString queryString = "SELECT * FROM public.inventory WHERE ";
        queryString += "id LIKE '%" + queryText + "%' OR ";
        queryString += "\"ISBN\" LIKE '%" + queryText + "%' OR ";
        queryString += "title LIKE '%" + queryText + "%' OR ";
        queryString += "author LIKE '%" + queryText + "%' OR ";
        queryString += "publisher LIKE '%" + queryText + "%'";

        // 执行查询操作
        QSqlQuery query(db);
        if (query.exec(queryString)) {
            // 清空表格内容
            bookTableWidget->clearContents();

            // 遍历查询结果，并更新表格内容
            int row = 0;
            while (query.next()) {
                for (int column = 0; column < bookTableWidget->columnCount(); ++column) {
                    QTableWidgetItem *item = new QTableWidgetItem(query.value(column).toString());
                    bookTableWidget->setItem(row, column, item);
                }
                ++row;
            }
        } else {
            qDebug() << "Query failed:";
        }
    });


    // 设置对话框的布局
    bookInfoDialog->setLayout(mainLayout);

    // 显示对话框
    bookInfoDialog->exec();
}

//辅助函数
void MainWindow2::handleBookItemChanged(QTableWidget *bookTableWidget, QTableWidgetItem *item)
{
    if (item) {
        // 获取行和列索引
        int row = item->row();
        int column = item->column();

        // 获取新值
        QString newValue = item->text();

        // 根据行、列索引和新值执行相应的操作
        // 比如更新数据库中的对应数据
        QString columnName;
        switch (column) {
        case 0:
            columnName = "id"; // 书籍编号
            break;
        case 1:
            return;
        case 2:
            columnName = "title"; // 标题
            break;
        case 3:
            columnName = "author"; // 作者
            break;
        case 4:
            columnName = "publisher"; // 出版商
            break;
        case 5:
            columnName = "price"; // 价格
            break;
        case 6:
            columnName = "quantity"; // 库存数量
            break;
        default:
            break;
        }

        // 更新数据库中的数据
        MainWindow mainWindow;
        mainWindow.createConnectionByName("Connect2");
        QSqlDatabase db = mainWindow.getConnectionByName("Connect2");
        QSqlQuery query(db);
        query.prepare("UPDATE inventory SET " + columnName + " = :newValue WHERE id = :id");
        query.bindValue(":newValue", newValue);
        query.bindValue(":id", bookTableWidget->item(row, 0)->text()); // 根据 id 更新相应的行

        if (!query.exec()) {
            qWarning() << "Update failed:" ;
        } else {
            qDebug() << "Book information updated successfully!";
        }
    }
}

//这个是退货与付款函数，本来写了两个函数，一个退货一个付款，集合到一个函数上
void MainWindow2::onBookReturn()
{
    // 创建一个窗口来展示图书信息管理界面
    QDialog *bookInfoDialog = new QDialog(this);
    bookInfoDialog->setWindowTitle(tr("Book Information Management"));
    bookInfoDialog->setFixedSize(950, 600);

    // 创建一个垂直布局管理器来放置表格和查询窗口
    QVBoxLayout *mainLayout = new QVBoxLayout(bookInfoDialog);

    // 创建一个水平布局管理器来放置查询组件
    QHBoxLayout *queryLayout = new QHBoxLayout;

    // 创建一个标签和文本框用于输入查询条件
    QLabel *queryLabel = new QLabel(tr("Query:"), bookInfoDialog);
    QLineEdit *queryLineEdit = new QLineEdit(bookInfoDialog);
    QPushButton *searchButton = new QPushButton(tr("Search"), bookInfoDialog);
    QPushButton *refreshButton = new QPushButton(tr("Refresh"), this);

    // 连接刷新按钮的点击事件
    connect(refreshButton, &QPushButton::clicked, this, [=]() {
        // 关闭书籍信息对话框（如果已经打开）
        if (bookInfoDialog && bookInfoDialog->isVisible()) {
            bookInfoDialog->close();
            delete bookInfoDialog;
        }
        // 重新打开书籍信息对话框
        onBookReturn();
    });

    // 将查询组件添加到水平布局管理器中
    queryLayout->addWidget(queryLabel);
    queryLayout->addWidget(queryLineEdit);
    queryLayout->addWidget(searchButton);
    queryLayout->addWidget(refreshButton);

    // 创建一个表格来展示图书信息
    QTableWidget *bookTableWidget = new QTableWidget(bookInfoDialog);
    bookTableWidget->setColumnCount(9); // 设置表格列数为6，对应ISBN、标题、作者、出版商、价格、数量

    QStringList headers;
    headers << tr("ISBN") << tr("Title") << tr("Author") << tr("Publisher") << tr("Price") << tr("Quantity")<<tr("State");
    bookTableWidget->setHorizontalHeaderLabels(headers);

    // 设置表格的大小策略
    bookTableWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // 添加表格和查询组件到垂直布局管理器中
    mainLayout->addLayout(queryLayout);
    mainLayout->addWidget(bookTableWidget);

    MainWindow mainWindow;
    mainWindow.createConnectionByName("Connect2");
    QSqlDatabase db = mainWindow.getConnectionByName("Connect2");
    QSqlQuery query(db);
    QSqlQuery query1(db);
    query1.exec("SELECT COUNT(*) FROM purchase");
    if (query1.next()) {
        int rowCount = query1.value(0).toInt();
        bookTableWidget->setRowCount(rowCount);
    } else {
        qDebug() << "Failed to retrieve row count from database.";
    }
    query.exec("SELECT \"ISBN\", title, author, publisher, price, quantitiy, state FROM public.purchase ORDER BY id ASC");
    int row = 0;
    while (query.next()) {
        // 从查询结果中获取图书信息

        QString ISBN = query.value("ISBN").toString();
        QString title = query.value("title").toString();
        QString author = query.value("author").toString();
        QString publisher = query.value("publisher").toString();
        QString price = query.value("price").toString();
        QString quantity = query.value("quantitiy").toString();
        QString state = query.value("state").toString();

        bookTableWidget->setItem(row, 0, new QTableWidgetItem(ISBN)); // ISBN
        bookTableWidget->setItem(row, 1, new QTableWidgetItem(title)); // 标题
        bookTableWidget->setItem(row, 2, new QTableWidgetItem(author)); // 作者
        bookTableWidget->setItem(row, 3, new QTableWidgetItem(publisher)); // 出版商
        bookTableWidget->setItem(row, 4, new QTableWidgetItem(price)); // 价格
        bookTableWidget->setItem(row, 5, new QTableWidgetItem(quantity)); // 库存数量
        bookTableWidget->setItem(row, 6, new QTableWidgetItem(state)); // 库存数量
        ++row;
    }

    for (int row = 0; row < bookTableWidget->rowCount(); ++row) {
        // 创建按钮
        QPushButton *button1 = new QPushButton("return");
        QPushButton *button2 = new QPushButton("purchase");

        // 获取第一列的值
        QTableWidgetItem *item = bookTableWidget->item(row, 6);
        QString firstColumnValue = item ? item->text() : "";
        qDebug()<<firstColumnValue;
        if(firstColumnValue != "unpaid\-for")
            continue;
        // 连接按钮点击事件
        connect(button1, &QPushButton::clicked, [=]() {
            // 根据第一列的值执行不同的操作
            // 例如，输出第一列的值
            qDebug() << "Button1 clicked for row " << row << ", First column value: " << firstColumnValue;
            QSqlQuery query2(db);
            query2.prepare("SELECT returnBook(:id)");
            query2.bindValue(":id", row+1);
            query2.exec();
        });

        connect(button2, &QPushButton::clicked, [=]() {
            // 根据第一列的值执行不同的操作
            // 例如，输出第一列的值
            qDebug() << "Button2 clicked for row " << row << ", First column value: " << firstColumnValue;
            QSqlQuery query2(db);
            query2.prepare("SELECT purchaseBook(:id)");
            query2.bindValue(":id", row+1);
            query2.exec();
        });
        // 添加按钮到表格的末尾
        bookTableWidget->setCellWidget(row, 7, button1);
        bookTableWidget->setCellWidget(row, 8, button2);
    }

    // 设置第0到第7列不可更改
    for (int row = 0; row < bookTableWidget->rowCount(); ++row) {
        for (int col = 0; col < 9; ++col) { // 0到9列
            QTableWidgetItem *item = bookTableWidget->item(row, col);
            if (item)
                item->setFlags(item->flags() & ~Qt::ItemIsEditable); // 移除编辑标志
        }
    }

    // 连接查询按钮的槽函数
    connect(searchButton, &QPushButton::clicked, this, [=]() {
        QString queryText = queryLineEdit->text();
        QString queryString = "SELECT * FROM public.purchase WHERE ";
        queryString += "\"ISBN\" LIKE '%" + queryText + "%' OR ";
        queryString += "title LIKE '%" + queryText + "%' OR ";
        queryString += "author LIKE '%" + queryText + "%' OR ";
        queryString += "publisher LIKE '%" + queryText + "%'";

        // 执行查询操作
        QSqlQuery query(db);
        if (query.exec(queryString)) {
            // 清空表格内容
            bookTableWidget->clearContents();

            // 遍历查询结果，并更新表格内容
            int row = 0;
            while (query.next()) {
                for (int column = 0; column < bookTableWidget->columnCount(); ++column) {
                    QTableWidgetItem *item = new QTableWidgetItem(query.value(column).toString());
                    bookTableWidget->setItem(row, column, item);
                }
                QPushButton *button1 = new QPushButton("return");
                QPushButton *button2 = new QPushButton("purchase");

                // 获取第一列的值
                QTableWidgetItem *item = bookTableWidget->item(row, 6);
                QString firstColumnValue = item ? item->text() : "";
                qDebug()<<firstColumnValue;
                if(firstColumnValue != "unpaid\-for")
                    continue;
                // 连接按钮点击事件
                connect(button1, &QPushButton::clicked, [=]() {
                    // 根据第一列的值执行不同的操作
                    // 例如，输出第一列的值
                    qDebug() << "Button1 clicked for row " << row << ", First column value: " << firstColumnValue;
                    QSqlQuery query2(db);
                    query2.prepare("SELECT returnBook(:id)");
                    query2.bindValue(":id", row+1);
                    query2.exec();
                });

                connect(button2, &QPushButton::clicked, [=]() {
                    // 根据第一列的值执行不同的操作
                    // 例如，输出第一列的值
                    qDebug() << "Button2 clicked for row " << row << ", First column value: " << firstColumnValue;
                    QSqlQuery query2(db);
                    query2.prepare("SELECT purchaseBook(:id)");
                    query2.bindValue(":id", row+1);
                    query2.exec();
                });
                // 添加按钮到表格的末尾
                bookTableWidget->setCellWidget(row, 7, button1);
                bookTableWidget->setCellWidget(row, 8, button2);
                ++row;
            }

        } else {
            qDebug() << "Query failed:";
        }
    });


    // 设置对话框的布局
    bookInfoDialog->setLayout(mainLayout);

    // 显示对话框
    bookInfoDialog->exec();
}

//添加新书函数，也就是用来采购
void MainWindow2::onAddNewBook()
{
    // 创建一个对话框
    QDialog *addBookDialog = new QDialog(this);
    addBookDialog->setWindowTitle(tr("Add New Book"));
    addBookDialog->setFixedSize(300, 150);

    // 创建两个选项按钮
    QPushButton *existingBookButton = new QPushButton(tr("Add Existing Book"), addBookDialog);
    QPushButton *newBookButton = new QPushButton(tr("Add New Book"), addBookDialog);

    // 连接选项按钮的点击事件
    connect(existingBookButton, &QPushButton::clicked, addBookDialog,[=]() {
        // 执行添加已有书籍的操作
        //addExistingBook();
        addBookDialog->close();
        QDialog *inputDialog = new QDialog(this);
        inputDialog->setWindowTitle("Existing Book");
        inputDialog->setFixedSize(300, 150);
        // 创建文本行和确认按钮
        QLineEdit *idLineEdit = new QLineEdit(inputDialog);
        QSpinBox *quantityLineEdit = new QSpinBox(inputDialog);
        QLineEdit *purchasePrice = new QLineEdit(inputDialog);
        QPushButton *confirmButton = new QPushButton("confirm", inputDialog);

        // 布局管理
        QFormLayout *layout = new QFormLayout(inputDialog);
        layout->addRow("Book ID:", idLineEdit);
        layout->addRow("prime cost:", purchasePrice);
        layout->addRow("Quantity:", quantityLineEdit);
        layout->addWidget(confirmButton);
        inputDialog->setLayout(layout);

        // 连接确认按钮的点击信号与槽函数
        connect(confirmButton, &QPushButton::clicked, this, [=]() {
            QString bookId = idLineEdit->text();
            int quantity = quantityLineEdit->text().toInt();
            QString price = purchasePrice->text();
            // 在这里执行确认按钮点击后的操作，比如处理输入的书籍编号和数量
            MainWindow mainWindow;
            mainWindow.createConnectionByName("Connect2");
            QSqlDatabase db = mainWindow.getConnectionByName("Connect2");
            QSqlQuery queryInventory(db);
            queryInventory.prepare("SELECT * FROM inventory WHERE id = :id");
            queryInventory.bindValue(":id", bookId);
            if (queryInventory.exec() && queryInventory.next()) {
                // 找到了书籍，获取书籍信息
                QString ISBN = queryInventory.value("ISBN").toString();
                QString title = queryInventory.value("title").toString();
                QString author = queryInventory.value("author").toString();
                QString publisher = queryInventory.value("publisher").toString();
                qDebug()<<ISBN<<title<<author<<publisher<<price<<quantity;
                // 将书籍信息添加到购买书籍表中
                QSqlQuery insertQuery(db);
                insertQuery.prepare("INSERT INTO purchase (\"ISBN\", title, author, publisher, price, quantitiy, state) "
                                    "VALUES (:ISBN, :title, :author, :publisher, CAST(:price AS MONEY), :quantity, 'unpaid-for')");
                insertQuery.bindValue(":ISBN", ISBN);
                insertQuery.bindValue(":title", title);
                insertQuery.bindValue(":author", author);
                insertQuery.bindValue(":publisher", publisher);
                insertQuery.bindValue(":price", price);
                insertQuery.bindValue(":quantity", quantity);
                if (insertQuery.exec()) {
                    QMessageBox::information(this, tr("Success"), tr("Book added successfully."));
                } else {
                    QMessageBox::warning(this, tr("Error"), tr("Failed to add book to purchase list."));
                }
            } else {
                // 未找到书籍
                QMessageBox::warning(this, tr("Error"), tr("Book not found in inventory."));
            }
            qDebug() << "Book ID: " << bookId;
            qDebug() << "Quantity: " << quantity;
            inputDialog->close(); // 关闭对话框
        });
        // 显示对话框
        inputDialog->exec();
    });
    connect(newBookButton, &QPushButton::clicked, addBookDialog,[=]() {
        // 执行添加新书的操作
        // 创建一个对话框
        addBookDialog->close();
        QDialog *newBookDialog = new QDialog(this);
        newBookDialog->setWindowTitle(tr("Add New Book"));

        // 创建输入框和标签
        QLabel *ISBNLabel = new QLabel(tr("ISBN:"), newBookDialog);
        QLineEdit *ISBNLineEdit = new QLineEdit(newBookDialog);

        QLabel *titleLabel = new QLabel(tr("Title:"), newBookDialog);
        QLineEdit *titleLineEdit = new QLineEdit(newBookDialog);

        QLabel *authorLabel = new QLabel(tr("Author:"), newBookDialog);
        QLineEdit *authorLineEdit = new QLineEdit(newBookDialog);

        QLabel *publisherLabel = new QLabel(tr("Publisher:"), newBookDialog);
        QLineEdit *publisherLineEdit = new QLineEdit(newBookDialog);

        QLabel *priceLabel = new QLabel(tr("Price:"), newBookDialog);
        QDoubleSpinBox *priceSpinBox = new QDoubleSpinBox(newBookDialog);

        QLabel *quantityLabel = new QLabel(tr("Quantity:"), newBookDialog);
        QSpinBox *quantitySpinBox = new QSpinBox(newBookDialog);

        // 创建确认按钮和取消按钮
        QPushButton *confirmButton = new QPushButton(tr("Confirm"), newBookDialog);
        QPushButton *cancelButton = new QPushButton(tr("Cancel"), newBookDialog);

        // 布局管理
        QFormLayout *layout = new QFormLayout(newBookDialog);
        layout->addRow(ISBNLabel, ISBNLineEdit);
        layout->addRow(titleLabel, titleLineEdit);
        layout->addRow(authorLabel, authorLineEdit);
        layout->addRow(publisherLabel, publisherLineEdit);
        layout->addRow(priceLabel, priceSpinBox);
        layout->addRow(quantityLabel, quantitySpinBox);
        layout->addRow(confirmButton, cancelButton);
        newBookDialog->setLayout(layout);

        // 连接按钮的槽函数
        connect(confirmButton, &QPushButton::clicked, this, [=]() {
            // 获取用户输入的书籍信息
            QString ISBN = ISBNLineEdit->text();
            QString title = titleLineEdit->text();
            QString author = authorLineEdit->text();
            QString publisher = publisherLineEdit->text();
            double price = priceSpinBox->value();
            int quantity = quantitySpinBox->value();

            // 执行添加新书的操作，可以在这里添加将书籍信息添加到数据库的代码
            // 将书籍信息添加到购买书籍表中
            MainWindow mainWindow;
            mainWindow.createConnectionByName("Connect2");
            QSqlDatabase db = mainWindow.getConnectionByName("Connect2");
            QSqlQuery insertQuery(db);
            insertQuery.prepare("INSERT INTO purchase (\"ISBN\", title, author, publisher, price, quantitiy, state) "
                                "VALUES (:ISBN, :title, :author, :publisher, CAST(:price AS MONEY), :quantity, 'unpaid-for')");
            insertQuery.bindValue(":ISBN", ISBN);
            insertQuery.bindValue(":title", title);
            insertQuery.bindValue(":author", author);
            insertQuery.bindValue(":publisher", publisher);
            insertQuery.bindValue(":price", price);
            insertQuery.bindValue(":quantity", quantity);
            if (insertQuery.exec()) {
                QMessageBox::information(this, tr("Success"), tr("Book added successfully."));
            } else {
                QMessageBox::warning(this, tr("Error"), tr("Failed to add book to purchase list."));
            }
            // 关闭对话框
            newBookDialog->close();
        });
        connect(cancelButton, &QPushButton::clicked, newBookDialog, &QDialog::close);

        // 显示对话框
        newBookDialog->exec();
    });

    // 创建垂直布局管理器，并将选项按钮添加到其中
    QVBoxLayout *layout = new QVBoxLayout(addBookDialog);
    layout->addWidget(existingBookButton);
    layout->addWidget(newBookButton);
    addBookDialog->setLayout(layout);

    // 显示对话框
    addBookDialog->exec();
}

//售卖书籍槽函数
void MainWindow2::onBookSale()
{
    // 创建一个窗口来展示图书信息管理界面
    QDialog *bookInfoDialog = new QDialog(this);
    bookInfoDialog->setWindowTitle(tr("Book Information Management"));
    bookInfoDialog->setFixedSize(800, 600);

    // 创建一个垂直布局管理器来放置表格和查询窗口
    QVBoxLayout *mainLayout = new QVBoxLayout(bookInfoDialog);

    // 创建一个水平布局管理器来放置查询组件
    QHBoxLayout *queryLayout = new QHBoxLayout;

    // 创建一个标签和文本框用于输入查询条件
    QLabel *queryLabel = new QLabel(tr("Query:"), bookInfoDialog);
    QLineEdit *queryLineEdit = new QLineEdit(bookInfoDialog);
    QPushButton *searchButton = new QPushButton(tr("Search"), bookInfoDialog);
    QPushButton *refreshButton = new QPushButton(tr("Refresh"), this);

    // 连接刷新按钮的点击事件
    connect(refreshButton, &QPushButton::clicked, [=]() {
        // 关闭书籍信息对话框（如果已经打开）
        if (bookInfoDialog && bookInfoDialog->isVisible()) {
            bookInfoDialog->close();
            delete bookInfoDialog;
        }
        // 重新打开书籍信息对话框
        onBookSale();
    });

    // 将查询组件添加到水平布局管理器中
    queryLayout->addWidget(queryLabel);
    queryLayout->addWidget(queryLineEdit);
    queryLayout->addWidget(searchButton);
    queryLayout->addWidget(refreshButton);

    // 创建一个表格来展示图书信息
    QTableWidget *bookTableWidget = new QTableWidget(bookInfoDialog);
    bookTableWidget->setColumnCount(8); // 设置表格列数为7，对应书籍编号、ISBN、标题、作者、出版商、价格、库存数量
    bookInfoDialog->setFixedSize(950, 600);
    QStringList headers;
    headers << tr("ID") << tr("ISBN") << tr("Title") << tr("Author") << tr("Publisher") << tr("Price") << tr("Quantity")<< tr("Sale");
    bookTableWidget->setHorizontalHeaderLabels(headers);

    // 设置表格的大小策略
    bookTableWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // 添加表格和查询组件到垂直布局管理器中
    mainLayout->addLayout(queryLayout);
    mainLayout->addWidget(bookTableWidget);

    MainWindow mainWindow;
    mainWindow.createConnectionByName("Connect2");
    QSqlDatabase db = mainWindow.getConnectionByName("Connect2");
    QSqlQuery query(db);
    QSqlQuery query1(db);

    query1.exec("SELECT COUNT(*) FROM inventory");
    if (query1.next()) {
        int rowCount = query1.value(0).toInt();
        bookTableWidget->setRowCount(rowCount);
    } else {
        qDebug() << "Failed to retrieve row count from database.";
    }
    query.exec("SELECT id, \"ISBN\", title, author, publisher, price, quantity FROM public.inventory ORDER BY id ASC");
    int row = 0;
    while (query.next()) {
        // 从查询结果中获取图书信息
        QString id = query.value("id").toString();
        QString ISBN = query.value("ISBN").toString();
        QString title = query.value("title").toString();
        QString author = query.value("author").toString();
        QString publisher = query.value("publisher").toString();
        QString price = query.value("price").toString();
        QString quantity = query.value("quantity").toString();

        bookTableWidget->setItem(row, 0, new QTableWidgetItem(id)); // 书籍编号
        bookTableWidget->setItem(row, 1, new QTableWidgetItem(ISBN)); // ISBN
        bookTableWidget->setItem(row, 2, new QTableWidgetItem(title)); // 标题
        bookTableWidget->setItem(row, 3, new QTableWidgetItem(author)); // 作者
        bookTableWidget->setItem(row, 4, new QTableWidgetItem(publisher)); // 出版商
        bookTableWidget->setItem(row, 5, new QTableWidgetItem(price)); // 价格
        bookTableWidget->setItem(row, 6, new QTableWidgetItem(quantity)); // 库存数量

        ++row;
    }
    for (int row = 0; row < bookTableWidget->rowCount(); ++row) {
        QPushButton *button1 = new QPushButton("sale");
        connect(button1, &QPushButton::clicked, this, [=]() {
            QTableWidgetItem *item = bookTableWidget->item(row, 1);
            QString ColumnValue = item ? item->text() : "";
            QDialog *saleDialog = new QDialog(this);
            saleDialog->setWindowTitle("Quantity sold out");
            QVBoxLayout *layout = new QVBoxLayout(saleDialog);
            QLineEdit *quantityLineEdit = new QLineEdit(saleDialog);
            QPushButton *confirmButton = new QPushButton("Confirm", saleDialog);
            layout->addWidget(quantityLineEdit);
            layout->addWidget(confirmButton);

            // 连接确认按钮的点击信号到处理函数
            connect(confirmButton, &QPushButton::clicked, this, [=]() {
                bool ok;
                int quantity = quantityLineEdit->text().toInt(&ok);
                if (ok) {
                    // 在这里处理销售操作，使用 quantity 参数
                    qDebug() << "Sale confirmed with quantity:" << quantity<<ColumnValue;
                    QSqlQuery query2(db);
                    query2.prepare("SELECT sell_book(:quantity, :ColumnValue);");
                    query2.bindValue(":quantity",quantity);
                    query2.bindValue(":ColumnValue",ColumnValue);
                    query2.exec();
                    saleDialog->close();
                } else {
                    qDebug() << "Invalid quantity input!";
                }
            });

            // 显示对话框
            saleDialog->exec();


        });
        bookTableWidget->setCellWidget(row, 7, button1);
    }

    // 设置第0到第8列不可更改
    for (int row = 0; row < bookTableWidget->rowCount(); ++row) {
        for (int col = 0; col < 8; ++col) { // 0到8列
            QTableWidgetItem *item = bookTableWidget->item(row, col);
            if (item)
                item->setFlags(item->flags() & ~Qt::ItemIsEditable); // 移除编辑标志
        }
    }


    connect(bookTableWidget, &QTableWidget::itemChanged, this, [=](QTableWidgetItem *item) {
        handleBookItemChanged(bookTableWidget, item);
    });

    // 连接查询按钮的槽函数
    connect(searchButton, &QPushButton::clicked, [=]() {
        QString queryText = queryLineEdit->text();
        QString queryString = "SELECT * FROM public.inventory WHERE ";
        queryString += "id LIKE '%" + queryText + "%' OR ";
        queryString += "\"ISBN\" LIKE '%" + queryText + "%' OR ";
        queryString += "title LIKE '%" + queryText + "%' OR ";
        queryString += "author LIKE '%" + queryText + "%' OR ";
        queryString += "publisher LIKE '%" + queryText + "%'";

        // 执行查询操作
        QSqlQuery query(db);
        if (query.exec(queryString)) {
            // 清空表格内容
            bookTableWidget->clearContents();

            // 遍历查询结果，并更新表格内容
            int row = 0;
            while (query.next()) {
                for (int column = 0; column < bookTableWidget->columnCount(); ++column) {
                    QTableWidgetItem *item = new QTableWidgetItem(query.value(column).toString());
                    bookTableWidget->setItem(row, column, item);
                }
                ++row;
            }
        } else {
            qDebug() << "Query failed:";
        }
    });


    // 设置对话框的布局
    bookInfoDialog->setLayout(mainLayout);

    // 显示对话框
    bookInfoDialog->exec();
}

//查看账单槽函数
void MainWindow2::onViewBill()
{
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("View Bill");
    dialog->setFixedSize(550, 400);
    QVBoxLayout *layout = new QVBoxLayout(dialog);

    // 添加起始时间选择框
    QLabel *startLabel = new QLabel("Start Time:");
    QDateTimeEdit *startDateTimeEdit = new QDateTimeEdit;
    startDateTimeEdit->setDisplayFormat("yyyy-MM-dd HH:mm:ss"); // 设置日期时间格式
    layout->addWidget(startLabel);
    layout->addWidget(startDateTimeEdit);

    // 添加结束时间选择框
    QLabel *endLabel = new QLabel("End Time:");
    QDateTimeEdit *endDateTimeEdit = new QDateTimeEdit;
    endDateTimeEdit->setDisplayFormat("yyyy-MM-dd HH:mm:ss"); // 设置日期时间格式
    layout->addWidget(endLabel);
    layout->addWidget(endDateTimeEdit);

    // 添加查询按钮
    QPushButton *queryButton = new QPushButton("Query");
    layout->addWidget(queryButton);

    // 创建表格
    QTableWidget *tableWidget = new QTableWidget;
    tableWidget->setColumnCount(3); // 时间、收入、备注
    tableWidget->setHorizontalHeaderLabels(QStringList() << "Time" << "Income" << "Remark");
    layout->addWidget(tableWidget);
    for (int row = 0; row < tableWidget->rowCount(); ++row) {
        tableWidget->setRowHeight(row, 40); // 设置行高为 40 像素
    }

    // 设置列宽
    tableWidget->setColumnWidth(0, 200);
    tableWidget->setColumnWidth(1, 100);
    tableWidget->setColumnWidth(2, 150);
    // 连接查询按钮的点击事件
    connect(queryButton, &QPushButton::clicked, this, [=]() {
        // 清空表格
        tableWidget->clearContents();
        tableWidget->setRowCount(0);

        // 获取起始时间和结束时间
        QString startTime = startDateTimeEdit->dateTime().toString("yyyy-MM-dd HH:mm:ss");
        QString endTime = endDateTimeEdit->dateTime().toString("yyyy-MM-dd HH:mm:ss");

        // 执行查询操作
        MainWindow mainWindow;
        mainWindow.createConnectionByName("Connect2");
        QSqlDatabase db = mainWindow.getConnectionByName("Connect2");
        QSqlQuery query(db);
        query.prepare("SELECT * FROM bill WHERE time BETWEEN :startTime AND :endTime");
        query.bindValue(":startTime", startTime);
        query.bindValue(":endTime", endTime);

        if (query.exec()) {
            // 显示查询结果
            int row = 0;
            while (query.next()) {
                QString time = query.value("time").toString();
                QString income = query.value("income").toString();
                QString remark = query.value("remark").toString();

                // 在表格中插入一行数据
                tableWidget->insertRow(row);
                tableWidget->setItem(row, 0, new QTableWidgetItem(time));
                tableWidget->setItem(row, 1, new QTableWidgetItem(income));
                tableWidget->setItem(row, 2, new QTableWidgetItem(remark));
                ++row;
            }
        } else {
            qDebug() << "Query failed:";
        }
    });

    // 显示对话框
    dialog->exec();
}

//退出登录槽函数
void MainWindow2::logout()
{
    this->close();
    MainWindow *mainWindow = new MainWindow();
    mainWindow->show();
}





