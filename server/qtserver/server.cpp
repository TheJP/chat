#include "server.h"

Server::Server(const quint16 & port, const QSharedPointer<Protocol> & protocol, const QSharedPointer<IFormat> & format,
               const QSharedPointer<ServiceManager> & manager, QObject *parent) :
    port(port),
    protocol(protocol),
    format(format),
    manager(manager),
    QObject(parent),
    websocketServer(new QWebSocketServer(QStringLiteral("Chat Server"), QWebSocketServer::NonSecureMode, this)),
    clients()
{
    connect(manager->getNotificationSender().data(), &NotificationSender::newNotification, this, &Server::onNewNotification);
}

Server::~Server(){
    websocketServer->close();
    qDeleteAll(clients.begin(), clients.end());
    delete websocketServer;
}

void Server::start(){
    if (websocketServer->listen(QHostAddress::Any, port)) {
        connect(websocketServer, &QWebSocketServer::newConnection, this, &Server::onNewConnection);
        connect(websocketServer, &QWebSocketServer::closed, this, &Server::closed);
    }
}

void Server::onNewConnection(){
    QWebSocket *pSocket = websocketServer->nextPendingConnection();

    connect(pSocket, &QWebSocket::textMessageReceived, this, &Server::processTextMessage);
    connect(pSocket, &QWebSocket::binaryMessageReceived, this, &Server::processBinaryMessage);
    connect(pSocket, &QWebSocket::disconnected, this, &Server::socketDisconnected);

    clients.append(pSocket);
}

void Server::onNewNotification(const IChatMsg & msg, const QList<int> & sessions){
    Q_UNUSED(msg);
    Q_UNUSED(sessions);
}

void Server::processTextMessage(QString message){
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    if (pClient) {
        QString answer(message.size());
        int i = message.size();
        for(auto & c : message){ answer[--i] = c; }
        pClient->sendTextMessage(answer);
    }
    websocketServer->close();
}

void Server::processBinaryMessage(QByteArray message){
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    if (pClient) {
        pClient->sendBinaryMessage(message);
    }
}

void Server::socketDisconnected(){
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    if (pClient) {
        clients.removeAll(pClient);
        pClient->deleteLater();
    }
}
