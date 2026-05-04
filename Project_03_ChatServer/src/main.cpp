#include <QCoreApplication>
#include <QDebug>
#include "ChatServer.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    ChatServer server;
    if (!server.startServer()) {
        qCritical() << "服务器启动失败";
        return 1;
    }

    qDebug() << "服务器已启动，等待客户端连接...";
    return app.exec();
}
