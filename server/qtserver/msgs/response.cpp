#include "response.h"

Response::Response(RequestType request, bool success, QObject *parent) :
    request(request), success(success), error(ErrorType::None), QObject(parent)
{
}

Response::Response(RequestType request, ErrorType error, const QString & errorText, QObject *parent) :
    request(request), success(false), error(error), errorText(errorText), QObject(parent)
{
}

void Response::read(IKeyValueReader & stream){
    Q_UNUSED(stream);
}

void Response::write(IKeyValueWriter & stream){
    stream.writeInt(KEY_REQUEST_TYPE, static_cast<int>(request));
    stream.writeInt(KEY_SUCCESS, success ? 1 : 0);
    if(error != ErrorType::None){
        stream.writeInt(QStringLiteral("error"), static_cast<int>(error));
        stream.writeString(QStringLiteral("error_text"), errorText);
    }
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
