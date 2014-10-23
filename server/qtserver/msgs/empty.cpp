#include "empty.h"

Empty::Empty(QObject *parent) :
    QObject(parent)
{
}

void Empty::read(IKeyValueReader & stream){
    Q_UNUSED(stream);
}

void Empty::write(IKeyValueWriter & stream){
    Q_UNUSED(stream);
}

QSharedPointer<IChatMsg> Empty::create(){
    return QSharedPointer<Empty>(new Empty());
}

QSharedPointer<IChatMsg> Empty::handle(const ServiceManager & manager){
    Q_UNUSED(manager);
    return QSharedPointer<Empty>();
}
