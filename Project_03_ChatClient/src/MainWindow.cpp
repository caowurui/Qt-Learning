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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUI();

    bool ok;
    do {
        nickname = QInputDialog::getText(this, "昵称",
                "请输入你的昵称:\n(不能包含 | 符号)",
                QLineEdit::Normal, "用户", &ok);
        if (!ok) {
            nickname = "用户";
            break;
        }
        nickname = nickname.trimmed();
    } while (nickname.isEmpty() || nickname.contains('|') || nickname == "未知");

    updateNicknameDisplay();

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
        changeNickBtn->setEnabled(false);
        msgInput->setEnabled(true);
        sendBtn->setEnabled(true);
        msgInput->setFocus();
        connection->sendMessage("NICK|" + nickname);
    });
    connect(connection, &ClientConnection::disconnected,
        this, [this]() {
        qDebug() << "断开连接";
        statusLabel->setText("● 未连接");
        statusBar()->showMessage("已断开连接");
        connectBtn->setEnabled(true);
        disconnectBtn->setEnabled(false);
        changeNickBtn->setEnabled(true);
        msgInput->setEnabled(false);
        sendBtn->setEnabled(false);
    });
    connect(connection, &ClientConnection::messageReceived,
        this, [this](QString raw) {
        // 解析协议
        QStringList parts = raw.split('|');
        if (parts.isEmpty()) return;

        if (parts[0] == "PUBLIC" && parts.size() >= 3) {
            QString sender = parts[1];
            QString content = parts.mid(2).join('|');
            msgDisplay->append(QString("[%1]: %2").arg(sender, content));
        } else if (parts[0] == "SYSTEM" && parts.size() >= 2) {
            QString sysMsg = parts[1];
            if (sysMsg.contains("已被使用")) {
                msgDisplay->append("【" + sysMsg + "】");
                connection->disconnectFromServer();
            } else {
                msgDisplay->append("【" + sysMsg + "】");
            }
        } else {
            msgDisplay->append(raw);
        }
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
            msgDisplay->append(QString("[%1]: %2").arg(nickname, text));
            msgInput->clear();
        }
    });

    // Enter 键发送
    connect(msgInput, &QLineEdit::returnPressed,
        sendBtn, &QPushButton::click);

    // 更改昵称
    connect(changeNickBtn, &QPushButton::clicked, this, [this]() {
        bool ok;
        QString newNick = QInputDialog::getText(this, "更改昵称",
                "请输入新昵称:\n(连接状态下修改后需重新连接)",
                QLineEdit::Normal, nickname, &ok);
        if (ok && !newNick.trimmed().isEmpty()
            && !newNick.contains('|') && newNick.trimmed() != "未知") {
            nickname = newNick.trimmed();
            updateNicknameDisplay();
        }
    });
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

    nickLabel = new QLabel();
    updateNicknameDisplay();
    topLayout->addWidget(nickLabel);

    changeNickBtn = new QPushButton("更改昵称");
    topLayout->addWidget(changeNickBtn);

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
    msgInput->setEnabled(false);
    inputLayout->addWidget(msgInput);

    sendBtn = new QPushButton("发送");
    sendBtn->setEnabled(false);
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
    QString host = hostInput->text();
    connection->connectToServer(host, port);
}
