#ifndef STREAMREADER_H
#define STREAMREADER_H

#include <QDataStream>
#include <QObject>
#include <QSharedPointer>
#include <QVector>
#include "ikeyvaluereader.h"

class StreamReader final : public QObject, public IKeyValueReader
{
    Q_OBJECT
    Q_INTERFACES(IKeyValueReader)
private:
    QSharedPointer<QDataStream> reader;
public:
    explicit StreamReader(QSharedPointer<QDataStream> reader, QObject *parent = 0);
    template<class T>
    T read(const QString & key) const;
    int readInt(const QString & key) override;
    double readDouble(const QString & key) override;
    QSharedPointer<QString> readString(const QString & key) override;
    QVector<QSharedPointer<IChatMsg>> readArray(const  QString & key, IChatMsg & replicator) override;
signals:

public slots:

};

#endif // STREAMREADER_H
