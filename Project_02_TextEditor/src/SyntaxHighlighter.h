#ifndef SYNTAXHIGHLIGHTER_H
#define SYNTAXHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QRegularExpression>

/**
 * @brief 代码语法高亮器
 *
 * 继承 QSyntaxHighlighter，为 C++ 代码提供
 * 关键字、字符串、注释和数字的高亮着色。
 */
class SyntaxHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    explicit SyntaxHighlighter(QTextDocument *parent = nullptr);

protected:
    /**
     * @brief 对一行文本进行高亮着色
     * @param text 当前行的文本内容
     *
     * Qt 在需要重绘文本块时自动调用此方法。
     */
    void highlightBlock(const QString &text) override;

private:
    /** 一条高亮规则：正则匹配 + 对应的格式 */
    struct HighlightRule {
        QRegularExpression pattern;  // 匹配模式
        QTextCharFormat format;      // 匹配后应用的格式
    };

    QVector<HighlightRule> rules;   // 所有高亮规则
};

#endif
