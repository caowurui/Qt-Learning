#include "MainWindow.h"
#include "FindReplaceDialog.h"
#include "SyntaxHighlighter.h"
#include "LineNumber.h"
#include <QTextEdit>
#include <QMenuBar>
#include <QApplication>
#include <QFileDialog>
#include <QMessageBox>
#include <QLabel>
#include <QStatusBar>
#include <QHBoxLayout>
#include <QScrollBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *container = new QWidget();
    QHBoxLayout *layout = new QHBoxLayout(container);
    textEdit = new QTextEdit();
    lineNumberWidget = new LineNumberWidget(textEdit);
    lineNumberWidget->setFixedWidth(35);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(lineNumberWidget);
    layout->addWidget(textEdit);
    setCentralWidget(container);

    findDialog = nullptr;

    createMenuBar();

    createStatusBar();

    highlighter = new SyntaxHighlighter(textEdit->document());

    // 编辑器滚动时刷新行号
    connect(textEdit->verticalScrollBar(), &QScrollBar::valueChanged,
            lineNumberWidget, [this]() { lineNumberWidget->update(); });

    // 文本内容变化时刷新行号
    connect(textEdit, &QTextEdit::textChanged,
            lineNumberWidget, [this]() { lineNumberWidget->update(); });
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

    editMenu->addSeparator();

    QAction *findAction = editMenu->addAction("查找(&F)...");
    findAction->setShortcut(QKeySequence("Ctrl+F"));
    connect(findAction, &QAction::triggered, this, &MainWindow::showFindDialog);

    QAction *replaceAction = editMenu->addAction("替换(&R)...");
    replaceAction->setShortcut(QKeySequence("Ctrl+H"));
    connect(replaceAction, &QAction::triggered, this, &MainWindow::showFindDialog);
}

void MainWindow::newFile()
{
    textEdit->clear();
    currentFile.clear();
    setWindowTitle("文本编辑器 - 未命名");
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
    setWindowTitle(QString("文本编辑器 - ")+fileName);

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

void MainWindow::showFindDialog()
{
    if (!findDialog) {
        findDialog = new FindReplaceDialog(this);
        connect(findDialog, &FindReplaceDialog::findNext,
                this, &MainWindow::findNext);
        connect(findDialog, &FindReplaceDialog::replace,
                this, &MainWindow::replace);
        connect(findDialog, &FindReplaceDialog::replaceAll,
                this, &MainWindow::replaceAll);
    }
    findDialog->show();
    findDialog->raise();
    findDialog->activateWindow();
}

void MainWindow::findNext(const QString &text)
{
    if (text.isEmpty())
        return;

    // 从当前光标向后查找
    bool found = textEdit->find(text);

    if (!found) {
        // 没找到，从文档开头重头查一遍
        QTextCursor cursor = textEdit->textCursor();
        cursor.movePosition(QTextCursor::Start);
        textEdit->setTextCursor(cursor);

        found = textEdit->find(text);
        if (!found) {
            statusBar()->showMessage("未找到: " + text, 3000);
        }
    }
}

void MainWindow::replace(const QString &findText, const QString &replaceText)
{
    if (findText.isEmpty())
        return;

    // 先查找
    QTextCursor cursor = textEdit->textCursor();
    cursor = textEdit->document()->find(findText, cursor);

    if (!cursor.isNull()) {
        // 找到则替换选中的文本
        cursor.insertText(replaceText);
    } else {
        statusBar()->showMessage("未找到: " + findText, 3000);
    }
}

void MainWindow::replaceAll(const QString &findText, const QString &replaceText)
{
    if (findText.isEmpty())
        return;

    // 从文档开头开始
    QTextCursor cursor(textEdit->document());
    cursor.movePosition(QTextCursor::Start);

    int count = 0;
    // 循环查找并替换
    while (true) {
        QTextCursor result = textEdit->document()->find(findText, cursor);
        if (result.isNull())
            break;

        result.insertText(replaceText);
        count++;

        // 更新光标位置，避免死循环
        cursor = result;
    }

    statusBar()->showMessage(QString("已替换 %1 处").arg(count), 3000);
}
