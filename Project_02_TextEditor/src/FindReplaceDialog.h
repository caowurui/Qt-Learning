#ifndef FINDREPLACEDIALOG_H
#define FINDREPLACEDIALOG_H

#include <QDialog>

class QLineEdit;
class QPushButton;

/**
 * @brief 查找/替换对话框
 *
 * 提供查找和替换的 UI 界面，
 * 通过信号将用户操作传递给 MainWindow 处理。
 */
class FindReplaceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FindReplaceDialog(QWidget *parent = nullptr);

    QString findText() const;
    QString replaceText() const;

signals:
    void findNext(const QString &text);
    void replace(const QString &findText, const QString &replaceText);
    void replaceAll(const QString &findText, const QString &replaceText);

private:
    QLineEdit *findInput;
    QLineEdit *replaceInput;
    QPushButton *findBtn;
    QPushButton *replaceBtn;
    QPushButton *replaceAllBtn;
};

#endif // FINDREPLACEDIALOG_H
