#include "server.h"

Server::Server(quint16 port, QObject *parent) :
    port(port),
    QObject(parent),
    websocketServer(new QWebSocketServer(QStringLiteral("Chat Server"), QWebSocketServer::NonSecureMode, this)),
    clients()
{
}

Server::~Server(){
    websocketServer->close();
    qDeleteAll(clients.begin(), clients.end());
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
