#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QList>

class QTcpSocket;

class ChatServer : public QObject
{
    Q_OBJECT

public:
    explicit ChatServer(QObject *parent = nullptr);
    ~ChatServer();

    bool startServer(quint16 port = 8888);

private slots:
    void onNewConnection();
    void onReadyRead();

private:
    QTcpServer *server;
    QList<QTcpSocket*> clients;
};

#endif
