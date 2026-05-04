#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    ~MainWindow();

private:
    void setupUI();

    // 顶部连接栏
    QLineEdit *hostInput;
    QLineEdit *portInput;
    QPushButton *connectBtn;
    QPushButton *disconnectBtn;
    QLabel *statusLabel;

    // 中部
    QSplitter *splitter;
    QListWidget *userList;
    QTextEdit *msgDisplay;

    // 底部输入
    QLineEdit *msgInput;
    QPushButton *sendBtn;
};

#endif
