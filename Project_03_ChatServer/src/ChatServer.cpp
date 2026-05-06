#include "ChatServer.h"
#include <QTcpSocket>
#include <QDebug>
#include <QDateTime>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

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
    QString raw = QString::fromUtf8(data).trimmed();

    qDebug() << "收到消息：" << raw;

    // 如果是 JSON，解析
    if (raw.startsWith('{')) {
        QJsonDocument doc = QJsonDocument::fromJson(raw.toUtf8());
        if (doc.isNull()) return;

        QJsonObject obj = doc.object();
        QString type = obj["type"].toString();

        if (type == "NICK") {
            QString nick = obj["nickname"].toString();

            if (nick == "未知" || nick == "匿名") {
                QJsonObject err;
                err["type"] = "SYSTEM";
                err["content"] = "昵称 " + nick + " 不允许使用";
                client->write(QJsonDocument(err).toJson(QJsonDocument::Compact) + "\n");
                client->disconnectFromHost();
                return;
            }

            if (clientNames.values().contains(nick)) {
                QJsonObject err;
                err["type"] = "SYSTEM";
                err["content"] = "昵称 " + nick + " 已被使用，请重新连接";
                client->write(QJsonDocument(err).toJson(QJsonDocument::Compact) + "\n");
                client->disconnectFromHost();
                qDebug() << "昵称重复:" << nick;
                return;
            }

            clientNames[client] = nick;
            qDebug() << "用户昵称:" << nick;

            // 广播用户上线
            QJsonObject notice;
            notice["type"] = "SYSTEM";
            notice["content"] = nick + " 加入了聊天室";
            QByteArray noticeData = QJsonDocument(notice).toJson(QJsonDocument::Compact) + "\n";
            for (auto *c : clients) {
                if (c != client)
                    c->write(noticeData);
            }

            broadcastUserList();
            return;
        }

        else if (type == "PUBLIC") {
            QString messageContent = obj["content"].toString();

            if (messageContent.isEmpty()) return;

            // 广播消息
            QString nick = clientNames.value(client, "未知");
            if (nick == "未知") return;

            QString time = QDateTime::currentDateTime().toString("HH:mm");

            QJsonObject msg;
            msg["type"] = "PUBLIC";
            msg["sender"] = nick;
            msg["time"] = time;
            msg["content"] = messageContent;

            QByteArray broadcast = QJsonDocument(msg).toJson(QJsonDocument::Compact) + "\n";
            for (auto *c : clients) {
                c->write(broadcast);
            }
        }
    }
}

void ChatServer::onDisconnected()
{
    QTcpSocket *client = qobject_cast<QTcpSocket*>(sender());
    if(client==nullptr) return;

    bool hadNick = clientNames.contains(client);
    QString nick = clientNames.take(client);

    clients.removeAll(client);
    client->deleteLater();

    if (hadNick) {
        QJsonObject notice;
        notice["type"] = "SYSTEM";
        notice["content"] = nick + " 离开了聊天室";
        QByteArray data = QJsonDocument(notice).toJson(QJsonDocument::Compact) + "\n";
        for (auto *c : clients) {
            c->write(data);
        }

        broadcastUserList();
        qDebug() << nick << "断开连接";
    }
}

void ChatServer::broadcastUserList()
{
    QJsonArray userArray;
    for (const QString &name : clientNames.values()) {
        userArray.append(name);
    }

    QJsonObject msg;
    msg["type"] = "USERLIST";
    msg["users"] = userArray;

    QByteArray data = QJsonDocument(msg).toJson(QJsonDocument::Compact) + "\n";
    for (auto *c : clients) {
        c->write(data);
    }
}
