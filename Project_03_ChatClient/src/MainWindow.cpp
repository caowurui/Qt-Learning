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
#include <QInputDialog>
#include <QDateTime>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUI();

    nickname = "用户";
    updateNicknameDisplay();

    privateMode = false;
    privateTarget.clear();
    intentionalDisconnect = false;

    connection = new ClientConnection(this);

    // 断线重连定时器
    reconnectTimer = new QTimer(this);
    connect(reconnectTimer, &QTimer::timeout, this, [this]() {
        statusBar()->showMessage("正在尝试重新连接...", 0);
        createConnection();
    });

    // 信号连接
    connect(connectBtn, &QPushButton::clicked,
        this, &MainWindow::createConnection);
    connect(connection, &ClientConnection::connected,
        this, &MainWindow::connectOn);
    connect(connection, &ClientConnection::disconnected,
        this, &MainWindow::connectOff);
    connect(connection, &ClientConnection::messageReceived,
        this, &MainWindow::receiveMessage);
    connect(connection, &ClientConnection::errorOccurred,
        this, [this](QString error) {
        statusBar()->showMessage(error, 5000);
    });
    connect(disconnectBtn, &QPushButton::clicked, this, [this]() {
        intentionalDisconnect = true;
        connection->disconnectFromServer();
    });
    connect(sendBtn, &QPushButton::clicked,
        this, &MainWindow::sendMessage);
    connect(msgInput, &QLineEdit::returnPressed,
        sendBtn, &QPushButton::click);
    connect(changeNickBtn, &QPushButton::clicked,
        this, &MainWindow::changeNickname);
    connect(userList, &QListWidget::itemDoubleClicked,
        this, &MainWindow::setPrivateMode);
    connect(cancelBtn, &QPushButton::clicked,
        this, &MainWindow::cancelPrivate);
}

void MainWindow::setupUI()
{
    QWidget *central = new QWidget();
    QVBoxLayout *mainLayout = new QVBoxLayout(central);
    mainLayout->setContentsMargins(6, 6, 6, 6);
    mainLayout->setSpacing(6);

    // 顶部：连接栏
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

    nickLabel = new QLabel();
    updateNicknameDisplay();
    topLayout->addWidget(nickLabel);

    changeNickBtn = new QPushButton("更改昵称");
    topLayout->addWidget(changeNickBtn);

    topLayout->addStretch();
    topBar->setFixedHeight(35);
    mainLayout->addWidget(topBar);

    // 中部：用户列表 + 聊天区域
    splitter = new QSplitter(Qt::Horizontal);
    userList = new QListWidget();
    userList->setMaximumWidth(200);
    splitter->addWidget(userList);

    QWidget *rightPanel = new QWidget();
    QVBoxLayout *rightLayout = new QVBoxLayout(rightPanel);
    rightLayout->setContentsMargins(0, 0, 0, 0);
    rightLayout->setSpacing(6);

    msgDisplay = new QTextEdit();
    msgDisplay->setReadOnly(true);
    rightLayout->addWidget(msgDisplay);

    // 私聊提示标签 + 取消按钮
    QWidget *privateMessage = new QWidget();
    QHBoxLayout *privateLayout = new QHBoxLayout(privateMessage);
    privateLayout->setContentsMargins(0, 0, 0, 0);
    privateLabel = new QLabel();
    privateLabel->setVisible(false);
    cancelBtn = new QPushButton("x");
    cancelBtn->setVisible(false);
    privateLayout->addWidget(privateLabel);
    privateLayout->addWidget(cancelBtn);
    privateLayout->addStretch();
    rightLayout->addWidget(privateMessage);

    // 底部输入栏
    QWidget *inputBar = new QWidget();
    QHBoxLayout *inputLayout = new QHBoxLayout(inputBar);
    inputLayout->setContentsMargins(0, 0, 0, 0);

    msgInput = new QLineEdit();
    msgInput->setPlaceholderText("输入消息...");
    msgInput->setEnabled(false);
    inputLayout->addWidget(msgInput);

    sendBtn = new QPushButton("发送");
    sendBtn->setEnabled(false);
    inputLayout->addWidget(sendBtn);

    rightLayout->addWidget(inputBar);
    splitter->addWidget(rightPanel);
    splitter->setStretchFactor(0, 1);
    splitter->setStretchFactor(1, 3);
    mainLayout->addWidget(splitter);

    setCentralWidget(central);
    statusBar()->showMessage("未连接到服务器");
}

void MainWindow::updateNicknameDisplay()
{
    nickLabel->setText("昵称: " + nickname);
}

void MainWindow::createConnection()
{
    bool ok;
    quint16 port = portInput->text().toUInt(&ok);
    if (!ok) {
        statusBar()->showMessage("端口号格式错误", 3000);
        return;
    }
    connection->connectToServer(hostInput->text(), port);
}

void MainWindow::connectOn()
{
    reconnectTimer->stop();
    statusLabel->setText("● 已连接");
    statusBar()->showMessage("已连接到服务器");
    connectBtn->setEnabled(false);
    disconnectBtn->setEnabled(true);
    changeNickBtn->setEnabled(false);
    msgInput->setEnabled(true);
    sendBtn->setEnabled(true);
    msgInput->setFocus();

    QJsonObject nickObj;
    nickObj["type"] = "NICK";
    nickObj["nickname"] = nickname;
    connection->sendMessage(QJsonDocument(nickObj).toJson(QJsonDocument::Compact));
}

void MainWindow::connectOff()
{
    statusLabel->setText("● 未连接");
    statusBar()->showMessage("已断开连接");
    connectBtn->setEnabled(true);
    disconnectBtn->setEnabled(false);
    changeNickBtn->setEnabled(true);
    msgInput->setEnabled(false);
    sendBtn->setEnabled(false);
    userList->clear();
    cancelPrivate();

    if (!intentionalDisconnect) {
        statusBar()->showMessage("连接断开，正在尝试重新连接...", 0);
        reconnectTimer->start(3000);
    }
    intentionalDisconnect = false;
}

void MainWindow::receiveMessage(const QString &raw)
{
    QJsonDocument doc = QJsonDocument::fromJson(raw.toUtf8());
    if (doc.isNull()) return;

    QJsonObject obj = doc.object();
    QString type = obj["type"].toString();

    if (type == "PUBLIC") {
        msgDisplay->append(QString("[%1] [%2]: %3")
            .arg(obj["time"].toString(), obj["sender"].toString(), obj["content"].toString()));
    } else if (type == "USERLIST") {
        userList->clear();
        for (const auto &u : obj["users"].toArray())
            userList->addItem(u.toString());
    } else if (type == "SYSTEM") {
        QString content = obj["content"].toString();
        if (content.contains("已被使用")) {
            msgDisplay->append("【" + content + "】");
            connection->disconnectFromServer();
        } else {
            msgDisplay->append("【" + content + "】");
        }
    } else if (type == "PRIVATE") {
        QString sender = obj["sender"].toString();
        QString time = obj["time"].toString();
        QString content = obj["content"].toString();
        QString receiver = obj["receiver"].toString();
        if (receiver == nickname)
            msgDisplay->append(QString("[%1] [%2 → 你]：%3").arg(time, sender, content));
        else
            msgDisplay->append(QString("[%1] [你 → %2]: %3").arg(time, receiver, content));
    }
}

void MainWindow::sendMessage()
{
    QString text = msgInput->text();
    if (text.isEmpty()) return;

    QJsonObject msg;
    msg["type"] = privateMode ? "PRIVATE" : "PUBLIC";
    if (privateMode) msg["target"] = privateTarget;
    msg["content"] = text;
    connection->sendMessage(QJsonDocument(msg).toJson(QJsonDocument::Compact));
    msgInput->clear();
    cancelPrivate();
}

void MainWindow::changeNickname()
{
    bool ok;
    QString newNick;
    do {
        newNick = QInputDialog::getText(this, "更改昵称",
                "请输入新昵称:", QLineEdit::Normal, nickname, &ok);
        if (!ok) return;
        newNick = newNick.trimmed();
    } while (newNick.isEmpty() || newNick == "未知" || newNick == "匿名");

    nickname = newNick;
    updateNicknameDisplay();
}

void MainWindow::setPrivateMode(QListWidgetItem *item)
{
    QString text = item->text();
    if (text == nickname || text.isEmpty()) return;

    privateTarget = text;
    privateMode = true;
    privateLabel->setText("私聊给:" + privateTarget);
    privateLabel->setVisible(true);
    cancelBtn->setVisible(true);
    msgInput->setFocus();
}

void MainWindow::cancelPrivate()
{
    privateLabel->setVisible(false);
    cancelBtn->setVisible(false);
    privateMode = false;
    privateTarget.clear();
}
