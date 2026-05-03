#include "LineNumber.h"
#include <QTextEdit>
#include <QPainter>
#include <QPaintEvent>
#include <QTextBlock>

LineNumberWidget::LineNumberWidget(QTextEdit *editor, QWidget *parent)
    : QWidget(parent)
{
    this->editor = editor;
}

/**
 * @brief 绘制行号
 *
 * 遍历编辑器中的所有文本块（行），
 * 在左侧灰色背景上绘制对应的行号。
 */
void LineNumberWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    // 获取编辑器第一个可见行的光标位置
    QTextCursor cursor = editor->cursorForPosition(QPoint(0, 0));
    QTextBlock block = cursor.block();
    int lineNumber = block.blockNumber() + 1;

    // 逐行遍历直到超出重绘区域
    while (block.isValid() && block.isVisible()) {
        // 对每一行单独获取屏幕 y 坐标，确保对齐
        QTextCursor blockCursor(block);
        blockCursor.movePosition(QTextCursor::StartOfBlock);
        int yPos = editor->cursorRect(blockCursor).y();

        if (yPos > event->rect().bottom())
            break;

        // 绘制行号（灰色、右对齐）
        painter.setPen(Qt::darkGray);
        painter.drawText(0, yPos, width(), editor->fontMetrics().height(),
                         Qt::AlignRight, QString::number(lineNumber));

        block = block.next();
        lineNumber++;
    }
}
