#include "MainWindow.h"
#include <QTextEdit>
#include <QMenu>
#include <QMenuBar>
#include <QApplication>

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

    // 退出
    QAction *exitAction = fileMenu->addAction("退出(&Q)");
    exitAction->setShortcut(QKeySequence("Ctrl+Q"));
    connect(exitAction,&QAction::triggered,qApp,&QApplication::quit);

}
