#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QTextEdit;
class QLabel;
class FindReplaceDialog;
class SyntaxHighlighter;

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

// Variants
private:
    QTextEdit *textEdit;
    QLabel *cursorLabel;
    QString currentFile;
    FindReplaceDialog *findDialog;
    SyntaxHighlighter *highlighter;
};

#endif
