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
#include <QMultiHash>
#include <QHash>
#include "jsonwriter.h"
#include "ichatmsg.h"
#include "services/servicemanager.h"
#include "notificationsender.h"
#include "protocol.h"
#include "iformat.h"
#include "streamable/responsesession.h"

class Server : public QObject
{
    Q_OBJECT

private:
    quint16 port;
    QWebSocketServer * websocketServer;
    QList<QWebSocket *> clients;
    QMultiHash<quint32, QWebSocket *> sessions;
    QHash<QWebSocket *, quint32> userIds;
    QSharedPointer<Protocol> protocol;
    QSharedPointer<IFormat> format;
    QSharedPointer<ServiceManager> manager;
    void sendNotification(IChatMsg & msg, QWebSocket * socket);
public:
    explicit Server(const quint16 & port, const QSharedPointer<Protocol> & protocol, const QSharedPointer<IFormat> & format,
        const QSharedPointer<ServiceManager> & manager, QObject *parent = 0);
    ~Server();
    void start();
signals:
    void closed();
private slots:
    void onNewConnection();
    void onNewNotification(IChatMsg & msg, const QList<int> & sessions);
    void processTextMessage(QString message);
    void processBinaryMessage(QByteArray message);
    void socketDisconnected();

};

#endif // SERVER_H
