#ifndef LINENUMBER_H
#define LINENUMBER_H

#include <QWidget>

class QTextEdit;

class LineNumberWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LineNumberWidget(QTextEdit *editor,QWidget *parent = nullptr);

private:
    QTextEdit *editor;

protected:
    void paintEvent(QPaintEvent *event) override;

};

#endif
