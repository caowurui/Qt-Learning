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
    QString message = QString::fromUtf8(data).trimmed();

    qDebug() << "收到消息：" << message;

    // 如果是 NICK 协议，保存昵称
    if (message.startsWith("NICK|")) {
        QString nick = message.mid(5);

        // 禁止使用保留昵称
        if (nick == "未知") {
            client->write(("SYSTEM|昵称 " + nick + " 不允许使用").toUtf8());
            client->disconnectFromHost();
            return;
        }

        // 检查昵称是否已被使用
        if (clientNames.values().contains(nick)) {
            client->write(("SYSTEM|昵称 " + nick + " 已被使用，请重新连接").toUtf8());
            client->disconnectFromHost();
            qDebug() << "昵称重复:" << nick;
            return;
        }

        clientNames[client] = nick;
        qDebug() << "用户昵称:" << nick;

        // 广播用户上线通知
        QString notice = "SYSTEM|" + nick + " 加入了聊天室";
        for (auto *c : clients) {
            if (c != client)
                c->write(notice.toUtf8());
        }
        return;
    }

    // 否则作为公共消息广播，带上发送者昵称
    QString nick = clientNames.value(client, "匿名");
    QString broadcast = "PUBLIC|" + nick + "|" + message;
    for (auto *c : clients) {
        if (c != client)
            c->write(broadcast.toUtf8());
    }
}

void ChatServer::onDisconnected()
{
    QTcpSocket *client = qobject_cast<QTcpSocket*>(sender());
    if(client==nullptr) return;

    // 检查是否注册过昵称
    bool hadNick = clientNames.contains(client);
    QString nick = clientNames.take(client);

    clients.removeAll(client);
    client->deleteLater();

    if (hadNick) {
        // 广播用户离线
        QString notice = "SYSTEM|" + nick + " 离开了聊天室";
        for (auto *c : clients) {
            c->write(notice.toUtf8());
        }
        qDebug() << nick << "断开连接";
    }
}
