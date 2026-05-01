#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QTextEdit;
// class QString;
class QLabel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

// Menu
private:
    void createMenuBar();
    void createFileMenu();
    void createEditMenu();

private slots:
    void newFile();
    bool openFile();
    bool saveFile();

private:
    void createStatusBar();
    void updateStatusBar();


private:
    QTextEdit *textEdit;

    QLabel *cursorLabel;

    QString currentFile;
};

#endif
