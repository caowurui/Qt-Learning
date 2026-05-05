#include "MainWindow.h"
#include "ClientConnection.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QListWidget>
#include <QSplitter>
#include <QStatusBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUI();

    connection = new ClientConnection(this);

    connect(connectBtn, &QPushButton::clicked,
        this, &MainWindow::createConnection);
    connect(connection, &ClientConnection::connected,
        this, [this]() {
        qDebug() << "连接成功";
        statusLabel->setText("● 已连接");
        statusBar()->showMessage("已连接到服务器");
        connectBtn->setEnabled(false);
        disconnectBtn->setEnabled(true);
    });
    connect(connection, &ClientConnection::disconnected,
        this, [this]() {
        qDebug() << "断开连接";
        statusLabel->setText("● 未连接");
        statusBar()->showMessage("已断开连接");
        connectBtn->setEnabled(true);
        disconnectBtn->setEnabled(false);
    });
    connect(connection, &ClientConnection::messageReceived,
        this, [this](QString text) {
        msgDisplay->append(text);
    });

    // 错误处理
    connect(connection, &ClientConnection::errorOccurred,
        this, [this](QString error) {
        statusBar()->showMessage(error, 5000);
        qDebug() << "错误:" << error;
    });

    // 断开连接
    connect(disconnectBtn, &QPushButton::clicked,
        connection, &ClientConnection::disconnectFromServer);

    // 发送消息
    connect(sendBtn, &QPushButton::clicked,
        this, [this]() {
        QString text = msgInput->text();
        if (!text.isEmpty()) {
            connection->sendMessage(text);
            msgInput->clear();
        }
    });

    // Enter 键发送
    connect(msgInput, &QLineEdit::returnPressed,
        sendBtn, &QPushButton::click);
}

void MainWindow::setupUI()
{
    // ====== 中央容器 ======
    QWidget *central = new QWidget();
    QVBoxLayout *mainLayout = new QVBoxLayout(central);
    mainLayout->setContentsMargins(6, 6, 6, 6);
    mainLayout->setSpacing(6);

    // ====== 顶部：连接栏 ======
    QWidget *topBar = new QWidget();
    QHBoxLayout *topLayout = new QHBoxLayout(topBar);
    topLayout->setContentsMargins(0, 0, 0, 0);

    topLayout->addWidget(new QLabel("服务器:"));
    hostInput = new QLineEdit("127.0.0.1");
    topLayout->addWidget(hostInput);

    topLayout->addWidget(new QLabel("端口:"));
    portInput = new QLineEdit("8888");
    portInput->setFixedWidth(80);
    topLayout->addWidget(portInput);

    connectBtn = new QPushButton("连接");
    topLayout->addWidget(connectBtn);

    disconnectBtn = new QPushButton("断开");
    disconnectBtn->setEnabled(false);
    topLayout->addWidget(disconnectBtn);

    statusLabel = new QLabel("● 未连接");
    topLayout->addWidget(statusLabel);

    topLayout->addStretch();
    topBar->setFixedHeight(35);
    mainLayout->addWidget(topBar);

    // ====== 中部：用户列表 + 聊天区域 ======
    splitter = new QSplitter(Qt::Horizontal);

    // 左侧：用户列表
    userList = new QListWidget();
    userList->setMaximumWidth(200);
    splitter->addWidget(userList);

    // 右侧：消息显示 + 输入栏
    QWidget *rightPanel = new QWidget();
    QVBoxLayout *rightLayout = new QVBoxLayout(rightPanel);
    rightLayout->setContentsMargins(0, 0, 0, 0);
    rightLayout->setSpacing(6);

    msgDisplay = new QTextEdit();
    msgDisplay->setReadOnly(true);
    rightLayout->addWidget(msgDisplay);

    // 底部输入栏
    QWidget *inputBar = new QWidget();
    QHBoxLayout *inputLayout = new QHBoxLayout(inputBar);
    inputLayout->setContentsMargins(0, 0, 0, 0);

    msgInput = new QLineEdit();
    msgInput->setPlaceholderText("输入消息...");
    inputLayout->addWidget(msgInput);

    sendBtn = new QPushButton("发送");
    inputLayout->addWidget(sendBtn);

    rightLayout->addWidget(inputBar);
    splitter->addWidget(rightPanel);

    splitter->setStretchFactor(0, 1);   // 用户列表 1 份
    splitter->setStretchFactor(1, 3);   // 聊天区域 3 份
    mainLayout->addWidget(splitter);

    setCentralWidget(central);

    // ====== 状态栏 ======
    statusBar()->showMessage("未连接到服务器");
}

void MainWindow::createConnection()
{
    bool ok;
    quint16 port = portInput->text().toUInt(&ok);
    if (!ok) {
        statusBar()->showMessage("端口号格式错误", 3000);
        return;
    }
    QString host = hostInput->text();
    connection->connectToServer(host, port);
}
