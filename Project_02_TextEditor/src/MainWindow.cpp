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

/**
 * @brief 构造函数
 *
 * 初始化标签页、创建第一个编辑器、设置菜单栏和状态栏。
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    tabs = new QTabWidget();
    tabs->setTabsClosable(true);
    connect(tabs, &QTabWidget::tabCloseRequested,
        this, &MainWindow::onTabCloseRequested);
    connect(tabs, &QTabWidget::currentChanged,
        this, &MainWindow::onCurrentTabChanged);
    setCentralWidget(tabs);

    findDialog = nullptr;

    // 创建第一个标签页
    QTextEdit *firstEditor;
    QWidget *firstPage = createEditorPage(firstEditor);
    tabs->addTab(firstPage, "未命名");

    editors[firstPage] = firstEditor;
    filePaths[firstPage] = QString();

    new SyntaxHighlighter(firstEditor->document());
    connectEditorSignals(firstEditor);

    createMenuBar();
    createStatusBar();
}

MainWindow::~MainWindow()
{
}

/**
 * @brief 创建一个新的编辑器页面
 * @param editor [out] 返回新创建的 QTextEdit 指针
 * @return 包含行号区域和编辑器的容器 QWidget
 *
 * 每个标签页由「行号组件 + 编辑器」组成，
 * 同时连接行号更新所需的信号。
 */
QWidget* MainWindow::createEditorPage(QTextEdit *&editor)
{
    editor = new QTextEdit();

    LineNumberWidget *lineNumber = new LineNumberWidget(editor);
    lineNumber->setFixedWidth(35);

    QWidget *page = new QWidget();
    QHBoxLayout *layout = new QHBoxLayout(page);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(lineNumber);
    layout->addWidget(editor);

    connect(editor->verticalScrollBar(), &QScrollBar::valueChanged,
            lineNumber, [lineNumber]() { lineNumber->update(); });
    connect(editor, &QTextEdit::textChanged,
            lineNumber, [lineNumber]() { lineNumber->update(); });

    return page;
}

/**
 * @brief 获取当前标签页的编辑器
 * @return 当前编辑器指针，如果没有标签页返回 nullptr
 */
QTextEdit* MainWindow::currentEditor()
{
    QWidget *page = tabs->currentWidget();
    if (!page) return nullptr;
    return editors.value(page, nullptr);
}

/**
 * @brief 为编辑器连接信号
 * @param editor 要连接的编辑器
 *
 * 编辑器的 cursorPositionChanged 信号驱动状态栏更新。
 */
void MainWindow::connectEditorSignals(QTextEdit *editor)
{
    connect(editor, &QTextEdit::cursorPositionChanged,
            this, &MainWindow::updateStatusBar);
}

/**
 * @brief 关闭标签页
 * @param index 要关闭的标签页索引
 */
void MainWindow::onTabCloseRequested(int index)
{
    QWidget *page = tabs->widget(index);
    tabs->removeTab(index);

    editors.remove(page);
    filePaths.remove(page);

    delete page;
}

/**
 * @brief 切换标签页时更新状态栏
 */
void MainWindow::onCurrentTabChanged(int index)
{
    Q_UNUSED(index);
    updateStatusBar();
}

void MainWindow::createMenuBar()
{
    createFileMenu();
    createEditMenu();
}

/**
 * @brief 创建文件菜单
 */
void MainWindow::createFileMenu()
{
    QMenu *fileMenu = menuBar()->addMenu("文件(&F)");

    QAction *newAction = fileMenu->addAction("新建(&N)");
    newAction->setShortcut(QKeySequence("Ctrl+N"));
    connect(newAction, &QAction::triggered, this, &MainWindow::newFile);

    QAction *openAction = fileMenu->addAction("打开(&O)...");
    openAction->setShortcut(QKeySequence("Ctrl+O"));
    connect(openAction, &QAction::triggered, this, &MainWindow::openFile);

    fileMenu->addSeparator();

    QAction *saveAction = fileMenu->addAction("保存(&S)");
    saveAction->setShortcut(QKeySequence("Ctrl+S"));
    connect(saveAction, &QAction::triggered, this, &MainWindow::saveFile);

    fileMenu->addSeparator();

    QAction *exitAction = fileMenu->addAction("退出(&Q)");
    exitAction->setShortcut(QKeySequence("Ctrl+Q"));
    connect(exitAction, &QAction::triggered, qApp, &QApplication::quit);
}

/**
 * @brief 创建编辑菜单
 */
void MainWindow::createEditMenu()
{
    QMenu *editMenu = menuBar()->addMenu("编辑(&E)");

    QAction *undoAction = editMenu->addAction("撤销(&U)");
    undoAction->setShortcut(QKeySequence("Ctrl+Z"));
    connect(undoAction, &QAction::triggered, this, [this]() {
        if (auto *e = currentEditor()) e->undo();
    });

    QAction *redoAction = editMenu->addAction("重做(&R)");
    redoAction->setShortcut(QKeySequence("Ctrl+Y"));
    connect(redoAction, &QAction::triggered, this, [this]() {
        if (auto *e = currentEditor()) e->redo();
    });

    editMenu->addSeparator();

    QAction *cutAction = editMenu->addAction("剪切(&T)");
    cutAction->setShortcut(QKeySequence("Ctrl+X"));
    connect(cutAction, &QAction::triggered, this, [this]() {
        if (auto *e = currentEditor()) e->cut();
    });

    QAction *copyAction = editMenu->addAction("复制(&C)");
    copyAction->setShortcut(QKeySequence("Ctrl+C"));
    connect(copyAction, &QAction::triggered, this, [this]() {
        if (auto *e = currentEditor()) e->copy();
    });

    QAction *pasteAction = editMenu->addAction("粘贴(&V)");
    pasteAction->setShortcut(QKeySequence("Ctrl+V"));
    connect(pasteAction, &QAction::triggered, this, [this]() {
        if (auto *e = currentEditor()) e->paste();
    });

    editMenu->addSeparator();

    QAction *findAction = editMenu->addAction("查找(&F)...");
    findAction->setShortcut(QKeySequence("Ctrl+F"));
    connect(findAction, &QAction::triggered, this, &MainWindow::showFindDialog);

    QAction *replaceAction = editMenu->addAction("替换(&R)...");
    replaceAction->setShortcut(QKeySequence("Ctrl+H"));
    connect(replaceAction, &QAction::triggered, this, &MainWindow::showFindDialog);
}

/**
 * @brief 新建空白标签页
 */
void MainWindow::newFile()
{
    QTextEdit *editor;
    QWidget *page = createEditorPage(editor);

    tabs->addTab(page, "未命名");
    tabs->setCurrentWidget(page);

    editors[page] = editor;
    filePaths[page] = QString();
    connectEditorSignals(editor);
    new SyntaxHighlighter(editor->document());
}

/**
 * @brief 打开文件
 *
 * 如果当前标签为空则复用，否则新建标签页。
 */
bool MainWindow::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, "打开文件");
    if (fileName.isEmpty())
        return false;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "错误", "无法打开文件:" + file.errorString());
        return false;
    }

    QTextStream in(&file);
    QString content = in.readAll();
    file.close();

    // 在当前标签页或新建标签页打开
    QTextEdit *editor = currentEditor();

    // 如果当前标签是空白的（从未编辑过），就复用；否则新建
    if (editor && editor->toPlainText().isEmpty() && filePaths[tabs->currentWidget()].isEmpty()) {
        // 复用当前标签
    } else {
        newFile();
        editor = currentEditor();
    }

    editor->setText(content);
    QWidget *page = tabs->currentWidget();
    filePaths[page] = fileName;

    QString shortName = fileName.section('/', -1).section('\\', -1);
    tabs->setTabText(tabs->currentIndex(), shortName);

    return true;
}

/**
 * @brief 保存文件
 *
 * 如果文件尚未命名则弹出另存为对话框。
 */
bool MainWindow::saveFile()
{
    QTextEdit *editor = currentEditor();
    if (!editor) return false;

    QWidget *page = tabs->currentWidget();
    QString path = filePaths[page];

    if (path.isEmpty()) {
        path = QFileDialog::getSaveFileName(this, "保存文件");
        if (path.isEmpty())
            return false;
        filePaths[page] = path;
    }

    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "错误", "无法保存文件：" + file.errorString());
        return false;
    }

    QTextStream out(&file);
    out << editor->toPlainText();
    file.close();

    QString shortName = path.section('/', -1).section('\\', -1);
    tabs->setTabText(tabs->currentIndex(), shortName);

    return true;
}

/**
 * @brief 创建状态栏（显示光标位置）
 */
void MainWindow::createStatusBar()
{
    cursorLabel = new QLabel("行数: 1, 列数: 1");
    statusBar()->addPermanentWidget(cursorLabel);
}

/**
 * @brief 更新状态栏的行号列号
 */
void MainWindow::updateStatusBar()
{
    QTextEdit *editor = currentEditor();
    if (!editor) return;

    QTextCursor cursor = editor->textCursor();
    int line = cursor.blockNumber() + 1;
    int col = cursor.columnNumber() + 1;
    cursorLabel->setText(QString("行数: %1, 列数: %2").arg(line).arg(col));
}

/**
 * @brief 显示查找/替换对话框
 *
 * 首次调用时创建对话框并连接信号，后续直接显示。
 */
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

/**
 * @brief 查找下一个匹配
 * @param text 要查找的文本
 *
 * 从当前光标向后查找，如果没找到则从文档开头重头查一遍。
 */
void MainWindow::findNext(const QString &text)
{
    QTextEdit *editor = currentEditor();
    if (!editor || text.isEmpty()) return;

    // 从当前光标向后查找
    bool found = editor->find(text);

    if (!found) {
        // 没找到，从文档开头重头查一遍
        QTextCursor cursor = editor->textCursor();
        cursor.movePosition(QTextCursor::Start);
        editor->setTextCursor(cursor);

        found = editor->find(text);
        if (!found) {
            statusBar()->showMessage("未找到: " + text, 3000);
        }
    }
}

/**
 * @brief 替换当前匹配
 */
void MainWindow::replace(const QString &findText, const QString &replaceText)
{
    QTextEdit *editor = currentEditor();
    if (!editor || findText.isEmpty()) return;

    // 先查找
    QTextCursor cursor = editor->textCursor();
    cursor = editor->document()->find(findText, cursor);

    if (!cursor.isNull()) {
        // 找到则替换选中的文本
        cursor.insertText(replaceText);
    } else {
        statusBar()->showMessage("未找到: " + findText, 3000);
    }
}

/**
 * @brief 替换所有匹配
 */
void MainWindow::replaceAll(const QString &findText, const QString &replaceText)
{
    QTextEdit *editor = currentEditor();
    if (!editor || findText.isEmpty()) return;

    // 从文档开头开始
    QTextCursor cursor(editor->document());
    cursor.movePosition(QTextCursor::Start);

    int count = 0;
    // 循环查找并替换
    while (true) {
        QTextCursor result = editor->document()->find(findText, cursor);
        if (result.isNull())
            break;

        result.insertText(replaceText);
        count++;

        // 更新光标位置，避免死循环
        cursor = result;
    }

    statusBar()->showMessage(QString("已替换 %1 处").arg(count), 3000);
}
