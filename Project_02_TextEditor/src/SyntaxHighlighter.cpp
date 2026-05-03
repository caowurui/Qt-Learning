#include "SyntaxHighlighter.h"

SyntaxHighlighter::SyntaxHighlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    HighlightRule rule;

    // ====== 1. 关键字（蓝色粗体） ======
    QTextCharFormat keywordFormat;
    keywordFormat.setForeground(QColor("#569CD6"));
    keywordFormat.setFontWeight(QFont::Bold);

    QStringList keywords = {
        "int", "float", "double", "char", "void",
        "if", "else", "for", "while", "do",
        "return", "break", "continue",
        "class", "struct", "enum", "namespace",
        "public", "private", "protected",
        "const", "static", "virtual", "override"
    };

    for (const QString &keyword : keywords) {
        // \b 表示单词边界，确保只匹配独立的单词
        rule.pattern = QRegularExpression("\\b" + keyword + "\\b");
        rule.format = keywordFormat;
        rules.append(rule);
    }

    // ====== 2. 字符串（橙色） ======
    QTextCharFormat stringFormat;
    stringFormat.setForeground(QColor("#CE9178"));

    rule.pattern = QRegularExpression("\"[^\"]*\"");  // 匹配 "..." 之间的内容
    rule.format = stringFormat;
    rules.append(rule);

    // ====== 3. 单行注释（绿色） ======
    QTextCharFormat commentFormat;
    commentFormat.setForeground(QColor("#6A9955"));

    rule.pattern = QRegularExpression("//[^\n]*");  // 匹配 // 到行尾
    rule.format = commentFormat;
    rules.append(rule);

    // ====== 4. 数字（浅绿色） ======
    QTextCharFormat numberFormat;
    numberFormat.setForeground(QColor("#B5CEA8"));

    rule.pattern = QRegularExpression("\\b\\d+\\b");  // 独立的数字
    rule.format = numberFormat;
    rules.append(rule);
}

/**
 * @brief 对一行文本应用语法高亮
 *
 * 遍历所有高亮规则，用正则匹配当前行文本，
 * 对匹配到的部分调用 setFormat 设置颜色和字体。
 */
void SyntaxHighlighter::highlightBlock(const QString &text)
{
    for (const HighlightRule &rule : rules) {
        QRegularExpressionMatchIterator it = rule.pattern.globalMatch(text);
        while (it.hasNext()) {
            QRegularExpressionMatch match = it.next();
            setFormat(match.capturedStart(),    // 匹配内容在行中的起始位置
                      match.capturedLength(),   // 匹配内容的长度
                      rule.format);             // 应用的颜色和字体格式
        }
    }
}
