#ifndef FINDREPLACEDIALOG_H
#define FINDREPLACEDIALOG_H

#include <QDialog>

class QLineEdit;
class QPushButton;

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
