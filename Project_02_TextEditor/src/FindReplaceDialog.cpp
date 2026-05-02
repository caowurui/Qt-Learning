#include "FindReplaceDialog.h"
#include <QBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

FindReplaceDialog::FindReplaceDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("查找和替换");
    setFixedSize(400, 180);

    // 布局
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // 查找行
    QHBoxLayout *findLayout = new QHBoxLayout();
    findLayout->addWidget(new QLabel("查找(&N):"));
    findInput = new QLineEdit();
    findLayout->addWidget(findInput);
    mainLayout->addLayout(findLayout);

    // 替换行
    QHBoxLayout *replaceLayout = new QHBoxLayout();
    replaceLayout->addWidget(new QLabel("替换(&R):"));
    replaceInput = new QLineEdit();
    replaceLayout->addWidget(replaceInput);
    mainLayout->addLayout(replaceLayout);

    // 按钮行
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    findBtn = new QPushButton("查找下一个");
    replaceBtn = new QPushButton("替换");
    replaceAllBtn = new QPushButton("全部替换");
    buttonLayout->addWidget(findBtn);
    buttonLayout->addWidget(replaceBtn);
    buttonLayout->addWidget(replaceAllBtn);
    mainLayout->addLayout(buttonLayout);

    // 信号连接（连接按钮到自身的信号，实际逻辑由 MainWindow 处理）
    connect(findBtn, &QPushButton::clicked, this, [this]() {
        emit findNext(findInput->text());
    });
    connect(replaceBtn, &QPushButton::clicked, this, [this]() {
        emit replace(findInput->text(), replaceInput->text());
    });
    connect(replaceAllBtn, &QPushButton::clicked, this, [this]() {
        emit replaceAll(findInput->text(), replaceInput->text());
    });
}

QString FindReplaceDialog::findText() const
{
    return findInput->text();
}

QString FindReplaceDialog::replaceText() const
{
    return replaceInput->text();
}
