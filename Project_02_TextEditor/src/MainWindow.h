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

// Status Bar
private:
    void createStatusBar();
    void updateStatusBar();

// Find & Replace
private:
    void showFindDialog();

private slots:
    void findNext(const QString &text);
    void replace(const QString &findText, const QString &replaceText);
    void replaceAll(const QString &findText, const QString &replaceText);

// Tabs
private:
    QWidget* createEditorPage(QTextEdit *&editor);
    QTextEdit* currentEditor();

private slots:
    void onTabCloseRequested(int index);
    void onCurrentTabChanged(int index);
    void connectEditorSignals(QTextEdit *editor);

private:
    QTabWidget *tabs;
    QMap<QWidget*, QTextEdit*> editors;
    QMap<QWidget*, QString> filePaths;

    QLabel *cursorLabel;
    FindReplaceDialog *findDialog;
};

#endif
