#ifndef CLIENTCONNECTION_H
#define CLIENTCONNECTION_H

#include <QTcpSocket>

class ClientConnection : public QObject
{
    Q_OBJECT
public:
    explicit ClientConnection(QObject *parent = nullptr);

public:
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
