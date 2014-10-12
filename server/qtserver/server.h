#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QList>
#include <QByteArray>
#include <QWebSocket>
#include <QWebSocketServer>

class Server : public QObject
{
    Q_OBJECT

private:
    quint16 port;
    QWebSocketServer *websocketServer;
    QList<QWebSocket *> clients;
public:
    explicit Server(quint16 port, QObject *parent = 0);
    ~Server();
    void start();
signals:
    void closed();
private slots:
    void onNewConnection();
    void processTextMessage(QString message);
    void processBinaryMessage(QByteArray message);
    void socketDisconnected();

};

#endif // SERVER_H
