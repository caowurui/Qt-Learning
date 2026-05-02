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

void LineNumberWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    // painter.fillRect(event->rect(), QColor("#f0f0f0"));

    // 获取第一个可见行
    QTextCursor cursor = editor->cursorForPosition(QPoint(0, 0));
    QTextBlock block = cursor.block();

    int lineNumber = block.blockNumber() + 1;

    while (block.isValid() && block.isVisible()) {
        // 对每一行单独获取屏幕 y 坐标
        QTextCursor blockCursor(block);
        blockCursor.movePosition(QTextCursor::StartOfBlock);
        int yPos = editor->cursorRect(blockCursor).y();

        if (yPos > event->rect().bottom())
            break;

        painter.setPen(Qt::darkGray);
        painter.drawText(0, yPos, width(), editor->fontMetrics().height(),
                         Qt::AlignRight, QString::number(lineNumber));

        block = block.next();
        lineNumber++;
    }
}
