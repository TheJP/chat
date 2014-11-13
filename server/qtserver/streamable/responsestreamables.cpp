#include "responsestreamables.h"

ResponseStreamables::ResponseStreamables(const StreamableVector & streamables, const QSharedPointer<QString> & type, RequestType request, bool success, QObject *parent) :
    streamables(streamables), type(type), Response(request, success, parent)
{
}

ResponseStreamables::~ResponseStreamables(){
    qDeleteAll(*streamables);
}

void ResponseStreamables::read(IKeyValueReader & stream){
    Response::read(stream);
}

void ResponseStreamables::write(IKeyValueWriter & stream){
    Response::write(stream);
    stream.writeArray(*type, *streamables);
}
