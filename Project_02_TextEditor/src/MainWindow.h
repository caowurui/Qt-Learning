#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QTextEdit;
class QAction;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void createMenuBar();
    void createFileMenu();
    void createEditMenu();

private slots:
    void newFile();
    bool openFile();
    bool saveFile();


private:
    QTextEdit *textEdit;

    QString currentFile;
};

#endif
