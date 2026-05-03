#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include <QTabWidget>

class QTextEdit;
class QLabel;
class FindReplaceDialog;
class SyntaxHighlighter;
class LineNumberWidget;

/**
 * @brief 文本编辑器主窗口
 *
 * 支持多标签页编辑、文件读写、查找替换、语法高亮、行号显示等功能。
 * 每个标签页拥有独立的编辑器实例，通过 QMap 维护标签页与编辑器的对应关系。
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // ---- 菜单栏 ----
private:
    void createMenuBar();
    void createFileMenu();
    void createEditMenu();

    // ---- 文件操作 ----
private slots:
    void newFile();
    bool openFile();
    bool saveFile();

    // ---- 状态栏 ----
private:
    void createStatusBar();
    void updateStatusBar();

    // ---- 查找/替换 ----
private:
    void showFindDialog();
private slots:
    void findNext(const QString &text);
    void replace(const QString &findText, const QString &replaceText);
    void replaceAll(const QString &findText, const QString &replaceText);

    // ---- 标签管理 ----
private:
    QWidget* createEditorPage(QTextEdit *&editor);
    QTextEdit* currentEditor();
    void connectEditorSignals(QTextEdit *editor);
private slots:
    void onTabCloseRequested(int index);
    void onCurrentTabChanged(int index);

    // ---- 成员变量 ----
private:
    QTabWidget *tabs;                          // 标签页容器
    QMap<QWidget*, QTextEdit*> editors;        // 页面 -> 编辑器
    QMap<QWidget*, QString> filePaths;         // 页面 -> 文件路径
    QLabel *cursorLabel;                       // 状态栏光标位置显示
    FindReplaceDialog *findDialog;             // 查找/替换对话框
};

#endif
