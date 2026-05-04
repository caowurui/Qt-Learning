#include "ChatServer.h"
#include <QTcpSocket>
#include <QDebug>

ChatServer::ChatServer(QObject *parent)
    : QObject(parent)
{
    server = new QTcpServer(this);

    connect(server, &QTcpServer::newConnection,
            this, &ChatServer::onNewConnection);
}

ChatServer::~ChatServer()
{
}

bool ChatServer::startServer(quint16 port)
{
    if (!server->listen(QHostAddress::Any, port)) {
        qCritical() << "监听失败:" << server->errorString();
        return false;
    }
    qDebug() << "服务器已启动，端口:" << port;

    return true;
}

void ChatServer::onNewConnection()
{
    // TODO: 接受新连接，保存 socket，连接信号
}

void ChatServer::onClientDisconnected()
{
    // TODO: 从列表中移除断开连接的客户端
}

void ChatServer::onReadyRead()
{
    // TODO: 读取客户端消息，广播给其他客户端
}
