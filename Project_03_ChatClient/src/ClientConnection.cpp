#include "ClientConnection.h"
#include <QDebug>

ClientConnection::ClientConnection(QObject *parent)
    : QObject(parent)
{
    socket = new QTcpSocket(this);

    connect(socket, &QTcpSocket::connected,
        this, [this](){
        emit connected();
    });
    connect(socket, &QTcpSocket::disconnected,
        this, [this](){
        emit disconnected();
    });
    connect(socket, &QTcpSocket::readyRead,
        this, [this](){
        QByteArray data = socket->readAll();
        emit messageReceived(QString::fromUtf8(data));
    });
    connect(socket, &QTcpSocket::errorOccurred,
        this, [this](QAbstractSocket::SocketError) {
        emit errorOccurred(socket->errorString());
    });
}

void ClientConnection::connectToServer(QString host, quint16 port)
{
    if (socket->state() != QAbstractSocket::UnconnectedState) {
        socket->disconnectFromHost();
    }
    socket->connectToHost(host, port);
}

void ClientConnection::disconnectFromServer()
{
    socket->disconnectFromHost();
}

void ClientConnection::sendMessage(QString text)
{
    if (socket->state() == QAbstractSocket::ConnectedState) {
        socket->write(text.toUtf8());
    } else {
        emit errorOccurred("消息发送失败：未连接到服务器");
    }
}
