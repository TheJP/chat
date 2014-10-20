#include "response.h"

Response::Response(RequestType request, bool success, QObject *parent) :
    request(request), success(success), QObject(parent)
{
}

void Response::read(IKeyValueReader & stream){
    Q_UNUSED(stream);
}

void Response::write(IKeyValueWriter & stream){
    stream.writeInt(KEY_REQUEST_TYPE, static_cast<int>(request));
    stream.writeInt(KEY_SUCCESS, success ? 1 : 0);
}

//Invalid for this specific type
QSharedPointer<IChatMsg> Response::create(){
    return QSharedPointer<Response>();
}

//Invalid for this specific type
QSharedPointer<IChatMsg> Response::handle(const ServiceManager & manager){
    Q_UNUSED(manager);
    return QSharedPointer<Response>();
}
