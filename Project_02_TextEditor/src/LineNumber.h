#ifndef LINENUMBER_H
#define LINENUMBER_H

#include <QWidget>

class QTextEdit;

/**
 * @brief 行号显示组件
 *
 * 自定义 QWidget，在编辑器左侧绘制行号。
 * 通过 paintEvent 手动绘制，而非使用 Qt 现成组件。
 */
class LineNumberWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LineNumberWidget(QTextEdit *editor, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QTextEdit *editor;  // 关联的编辑器
};

#endif
