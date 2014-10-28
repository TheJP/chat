#ifndef STREAMWRITER_H
#define STREAMWRITER_H

#include <QDataStream>
#include <QObject>
#include <QSharedPointer>
#include "ikeyvaluewriter.h"

class StreamWriter final : public QObject, public IKeyValueWriter
{
    Q_OBJECT
    Q_INTERFACES(IKeyValueWriter)
private:
    QSharedPointer<QDataStream> writer;
public:
    explicit StreamWriter(QSharedPointer<QDataStream> writer, QObject *parent = 0);
    void write(const QString & key, int value) override;
    void write(const QString & key, double value) override;
    void write(const QString & key, const QString & value) override;
    void write(const QString & key, IStreamable & value) override;
    void writeArray(const QString &key, const QVector<IStreamable *> &values) override;
signals:

public slots:

};

#endif // STREAMWRITER_H
