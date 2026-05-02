#include "SyntaxHighlighter.h"

SyntaxHighlighter::SyntaxHighlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    HighlightRule rule;

    // 1. 关键字高亮（蓝色）
    QTextCharFormat keywordFormat;
    keywordFormat.setForeground(QColor("#569CD6"));  // 蓝色
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
        rule.pattern = QRegularExpression("\\b" + keyword + "\\b");
        rule.format = keywordFormat;
        rules.append(rule);
    }

    // 2. 字符串高亮（橙色）
    QTextCharFormat stringFormat;
    stringFormat.setForeground(QColor("#CE9178"));

    rule.pattern = QRegularExpression("\"[^\"]*\"");
    rule.format = stringFormat;
    rules.append(rule);

    // 3. 单行注释（绿色）
    QTextCharFormat commentFormat;
    commentFormat.setForeground(QColor("#6A9955"));

    rule.pattern = QRegularExpression("//[^\n]*");
    rule.format = commentFormat;
    rules.append(rule);

    // 4. 数字（浅绿色）
    QTextCharFormat numberFormat;
    numberFormat.setForeground(QColor("#B5CEA8"));

    rule.pattern = QRegularExpression("\\b\\d+\\b");
    rule.format = numberFormat;
    rules.append(rule);
}

void SyntaxHighlighter::highlightBlock(const QString &text)
{
    for (const HighlightRule &rule : rules) {
        QRegularExpressionMatchIterator it = rule.pattern.globalMatch(text);
        while (it.hasNext()) {
            QRegularExpressionMatch match = it.next();
            setFormat(match.capturedStart(),    // 匹配到的起始位置
                      match.capturedLength(),   // 匹配到的长度
                      rule.format);             // 应用格式
        }
    }
}
