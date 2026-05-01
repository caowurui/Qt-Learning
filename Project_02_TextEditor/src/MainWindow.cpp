#include "MainWindow.h"
#include <QTextEdit>
#include <QMenu>
#include <QMenuBar>
#include <QApplication>
#include <QFileDialog>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    textEdit = new QTextEdit(this);
    setCentralWidget(textEdit);

    createMenuBar();
}

MainWindow::~MainWindow()
{
}

void MainWindow::createMenuBar()
{
    QMenu *fileMenu = menuBar()->addMenu("文件(&F)");

    // 新建
    QAction *newAction = fileMenu->addAction("新建(&N)");
    newAction->setShortcut(QKeySequence("Ctrl+N"));
    connect(newAction,&QAction::triggered,this,&MainWindow::newFile);

    // 打开
    QAction *openAction = fileMenu->addAction("打开(&O)...");
    openAction->setShortcut(QKeySequence("Ctrl+O"));
    connect(openAction,&QAction::triggered,this,&MainWindow::openFile);

    fileMenu->addSeparator();

    // 保存
    QAction *saveAction = fileMenu->addAction("保存(&S)");
    saveAction->setShortcut(QKeySequence("Ctrl+S"));
    connect(saveAction,&QAction::triggered,this,&MainWindow::saveFile);

    fileMenu->addSeparator();

    // 退出
    QAction *exitAction = fileMenu->addAction("退出(&Q)");
    exitAction->setShortcut(QKeySequence("Ctrl+Q"));
    connect(exitAction,&QAction::triggered,qApp,&QApplication::quit);

}

void MainWindow::newFile()
{
    textEdit->clear();
    currentFile.clear();
    setWindowTitle("未命名");
}

bool MainWindow::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this,"打开文件");
    if (fileName.isEmpty())
        return false;

    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this,"错误","无法打开文件:"+file.errorString());
        return false;
    }

    QTextStream in(&file);
    textEdit->setText(in.readAll());
    file.close();

    currentFile = fileName;
    setWindowTitle(fileName);

    return true;
}

bool MainWindow::saveFile()
{
    if (currentFile.isEmpty()) {
        QString fileName = QFileDialog::getSaveFileName(this, "保存文件");
        if (fileName.isEmpty())
            return false;
        currentFile = fileName;
    }

    QFile file(currentFile);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "错误", "无法保存文件：" + file.errorString());
        return false;
    }

    QTextStream out(&file);
    out << textEdit->toPlainText();
    file.close();

    setWindowTitle(currentFile);
    return true;
}
