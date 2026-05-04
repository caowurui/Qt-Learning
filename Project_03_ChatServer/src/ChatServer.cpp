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
        this, &ChatServer::onDisconnected);

    qDebug() << "新客户端连接:" << client->peerAddress().toString()
                << "端口:" << client->peerPort();
}

void ChatServer::onReadyRead()
{
    QTcpSocket *client = qobject_cast<QTcpSocket*>(sender());
    if(!client) return;

    QByteArray data = client->readAll();

    qDebug() << "收到消息：" << data;

    for(QTcpSocket *c: clients)
    {
        if(c!=client)
        {
            c->write(data);
        }
    }
}

void ChatServer::onDisconnected()
{
    QTcpSocket *client = qobject_cast<QTcpSocket*>(sender());
    if(client==nullptr) return;
    clients.removeAll(client);
    client->deleteLater();
    qDebug() << "客户端断开连接";
}
