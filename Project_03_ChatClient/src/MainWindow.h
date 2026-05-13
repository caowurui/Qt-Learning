#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ClientConnection.h"

class QLineEdit;
class QPushButton;
class QLabel;
class QTextEdit;
class QListWidget;
class QSplitter;
class QListWidgetItem;
class QTimer;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    void setupUI();
    void updateNicknameDisplay();

    // 顶部连接栏
    QLineEdit *hostInput;
    QLineEdit *portInput;
    QPushButton *connectBtn;
    QPushButton *disconnectBtn;
    QLabel *statusLabel;
    QLabel *nickLabel;
    QPushButton *changeNickBtn;

    // 中部
    QSplitter *splitter;
    QListWidget *userList;
    QTextEdit *msgDisplay;

    // 底部
    QLineEdit *msgInput;
    QPushButton *sendBtn;
    QLabel *privateLabel;
    QPushButton *cancelBtn;

public:
    void createConnection();
    void connectOn();
    void connectOff();

    void receiveMessage(const QString &raw);
    void sendMessage();
    void setPrivateMode(QListWidgetItem *item);
    void cancelPrivate();


    void changeNickname();

private:
    ClientConnection *connection;
    QTimer *reconnectTimer;
    QString nickname;

    bool privateMode;
    QString privateTarget;
    bool intentionalDisconnect;
};

#endif
