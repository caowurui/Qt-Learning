#ifndef CLIENTCONNECTION_H
#define CLIENTCONNECTION_H

#include <QTcpSocket>

/**
 * @brief TCP 连接管理器
 *
 * 封装 QTcpSocket，提供连接、断开、发送消息的接口。
 * 通过信号通知上层连接状态和数据接收。
 */
class ClientConnection : public QObject
{
    Q_OBJECT

public:
    explicit ClientConnection(QObject *parent = nullptr);

    void connectToServer(QString host, quint16 port);
    void disconnectFromServer();
    void sendMessage(QString text);

signals:
    void connected();
    void disconnected();
    void messageReceived(QString text);
    void errorOccurred(QString error);

private:
    QTcpSocket *socket;
};

#endif
