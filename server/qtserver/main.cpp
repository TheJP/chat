#include <iostream>
#include <QCoreApplication>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QIODevice>
#include "ikeyvaluereader.h"
#include "jsonreader.h"

#ifdef QT_DEBUG
    #include "test/testmain.h"
#endif

int main(int argc, char *argv[])
{
    QTextStream cout(stdout);

#ifdef QT_DEBUG
    TestMain tests;
    tests.execute();
    cout << endl << endl;
#endif

    QCoreApplication a(argc, argv);
    //** Read Config **//
    {
        //Open file
        QFile settingFile(QStringLiteral("../settings.json"));
        if(!settingFile.open(QIODevice::ReadOnly)){ qFatal("Could not open settings file 'settings.json'"); return 0; }
        QJsonDocument settingDoc(QJsonDocument::fromJson(settingFile.readAll()));
        JsonReader reader(QSharedPointer<QJsonObject>(new QJsonObject(settingDoc.object())));
        //Read config
        cout << *reader.readString(QStringLiteral("db")) << endl;
    }
    return a.exec();
}
