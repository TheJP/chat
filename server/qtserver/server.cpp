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
    connect(&manager->getNotificationSender(), &NotificationSender::newNotification, this, &Server::onNewNotification);
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
        //Get reader for this message
        QSharedPointer<IKeyValueReader> reader = format->getReader(message.toUtf8());
        //Handle message
        int type = reader->readInt(KEY_MSG_TYPE);
        if(type != 0){
            QSharedPointer<IChatMsg> msg = protocol->createRequest(static_cast<RequestType>(type));
            msg->read(*reader);
            QSharedPointer<IChatMsg> result = msg->handle(*manager);
            //Send return message to client
            if(!result.isNull()){
                //Write to json
                QSharedPointer<QJsonObject> json(new QJsonObject());
                JsonWriter writer(json);
                writer.writeInt(KEY_MSG_TYPE, static_cast<int>(ResponseType::Response));
                result->write(writer);
                //Write to stream
                QJsonDocument document(*json);
                pClient->sendTextMessage(QString::fromUtf8(document.toJson()));
            }
        }
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
