#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QList>
#include <QMap>

class QTcpSocket;

/**
 * @brief 聊天服务器
 *
 * 基于 TCP + JSON 协议的聊天服务器。
 * 支持多客户端连接、昵称管理、公共/私聊消息、用户列表同步。
 */
class ChatServer : public QObject
{
    Q_OBJECT

public:
    explicit ChatServer(QObject *parent = nullptr);
    ~ChatServer();

    bool startServer(quint16 port = 8888);

private slots:
    void onNewConnection();
    void onDisconnected();
    void onReadyRead();

private:
    QTcpServer *server;
    QList<QTcpSocket*> clients;             // 所有已连接的 socket
    QMap<QTcpSocket*, QString> clientNames; // socket → 昵称 映射
    void broadcastUserList();
};

#endif
