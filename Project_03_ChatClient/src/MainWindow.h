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

    // 底部输入
    QLineEdit *msgInput;
    QPushButton *sendBtn;

public:
    void createConnection();

private:
    ClientConnection *connection;
    QString nickname;
};

#endif
