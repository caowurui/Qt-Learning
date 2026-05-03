#include <QApplication>
#include "MainWindow.h"

/**
 * @brief 程序入口
 *
 * 创建 QApplication 和 MainWindow，启动事件循环。
 */
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow window;
    window.setWindowTitle("文本编辑器");
    window.resize(800, 600);
    window.show();

    return app.exec();
}
