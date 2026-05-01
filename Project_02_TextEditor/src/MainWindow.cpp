#include "MainWindow.h"
#include <QTextEdit>
#include <QMenu>
#include <QMenuBar>
#include <QApplication>
#include <QFileDialog>
#include <QMessageBox>
#include <QLabel>
#include <QStatusBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    textEdit = new QTextEdit(this);
    setCentralWidget(textEdit);

    createMenuBar();

    createStatusBar();
}

MainWindow::~MainWindow()
{
}

void MainWindow::createMenuBar()
{
    createFileMenu();
    createEditMenu();
}

void MainWindow::createFileMenu()
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

void MainWindow::createEditMenu()
{
    QMenu *editMenu = menuBar()->addMenu("编辑(&E)");

    QAction *undoAction = editMenu->addAction("撤销(&U)");
    undoAction->setShortcut(QKeySequence("Ctrl+Z"));
    connect(undoAction, &QAction::triggered, textEdit, &QTextEdit::undo);

    QAction *redoAction = editMenu->addAction("重做(&R)");
    redoAction->setShortcut(QKeySequence("Ctrl+Y"));
    connect(redoAction, &QAction::triggered, textEdit, &QTextEdit::redo);

    editMenu->addSeparator();

    QAction *cutAction = editMenu->addAction("剪切(&T)");
    cutAction->setShortcut(QKeySequence("Ctrl+X"));
    connect(cutAction, &QAction::triggered, textEdit, &QTextEdit::cut);

    QAction *copyAction = editMenu->addAction("复制(&C)");
    copyAction->setShortcut(QKeySequence("Ctrl+C"));
    connect(copyAction, &QAction::triggered, textEdit, &QTextEdit::copy);

    QAction *pasteAction = editMenu->addAction("粘贴(&V)");
    pasteAction->setShortcut(QKeySequence("Ctrl+V"));
    connect(pasteAction, &QAction::triggered, textEdit, &QTextEdit::paste);
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

void MainWindow::createStatusBar()
{
    cursorLabel = new QLabel("行数: 1, 列数: 1");
    statusBar()->addPermanentWidget(cursorLabel);
    connect(textEdit,&QTextEdit::cursorPositionChanged,
        this,&MainWindow::updateStatusBar);
}

void MainWindow::updateStatusBar()
{
    QTextCursor cursor = textEdit->textCursor();
    int line = cursor.blockNumber() + 1;
    int col = cursor.columnNumber() + 1;
    cursorLabel->setText(QString("行数: %1, 列数: %2").arg(line).arg(col));
}
