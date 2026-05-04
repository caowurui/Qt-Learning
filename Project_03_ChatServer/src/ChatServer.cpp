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
    QTcpSocket *client = server->nextPendingConnection();

    clients.append(client);

    connect(client, &QTcpSocket::readyRead,
        this, &ChatServer::onReadyRead);
    connect(client, &QTcpSocket::disconnected,
        this, [this, client](){
            clients.removeAll(client);
            client->deleteLater();
            qDebug() << "客户端断开连接";
        });

    qDebug() << "新客户端连接:" << client->peerAddress().toString()
                << "端口:" << client->peerPort();
}

void ChatServer::onReadyRead()
{
    // TODO: 读取客户端消息，广播给其他客户端
}
