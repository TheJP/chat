#ifndef TESTMAIN_H
#define TESTMAIN_H

#include <QObject>
#include <QtTest/QtTest>
#include "jsonreadertest.h"
#include "jsonwritertest.h"

class TestMain : public QObject
{
    Q_OBJECT
public:
    explicit TestMain(QObject *parent = 0);
    void execute();
signals:

public slots:

};

#endif // TESTMAIN_H
