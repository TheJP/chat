#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QList>
#include <QByteArray>
#include <QWebSocket>
#include <QWebSocketServer>
#include <QSharedPointer>
#include <QJsonObject>
#include <QJsonDocument>
#include "jsonwriter.h"
#include "ichatmsg.h"
#include "services/servicemanager.h"
#include "notificationsender.h"
#include "protocol.h"
#include "iformat.h"

class Server : public QObject
{
    Q_OBJECT

private:
    quint16 port;
    QWebSocketServer * websocketServer;
    QList<QWebSocket *> clients;
    QSharedPointer<Protocol> protocol;
    QSharedPointer<IFormat> format;
    QSharedPointer<ServiceManager> manager;
public:
    explicit Server(const quint16 & port, const QSharedPointer<Protocol> & protocol, const QSharedPointer<IFormat> & format,
        const QSharedPointer<ServiceManager> & manager, QObject *parent = 0);
    ~Server();
    void start();
signals:
    void closed();
private slots:
    void onNewConnection();
    void onNewNotification(const IChatMsg & msg, const QList<int> & sessions);
    void processTextMessage(QString message);
    void processBinaryMessage(QByteArray message);
    void socketDisconnected();

};

#endif // SERVER_H
